// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

static void init_commands()
{
	// zero is home, but we always load the next command (1), in the code.
    g.waypoint_index.set_and_save(0);

    // This are registers for the current may and must commands
    // setting to zero will allow them to be written to by new commands
	command_must_index	= NO_COMMAND;
	command_may_index	= NO_COMMAND;

	// clear the command queue
	clear_command_queue();
}

// forces the loading of a new command
// queue is emptied after a new command is processed
static void clear_command_queue(){
	next_command.id 	= NO_COMMAND;
}

static void init_auto()
{
	//if (g.waypoint_index == g.waypoint_total) {
	//	Serial.println("ia_f");
	//	do_RTL();
	//}

	// initialize commands
	// -------------------
	init_commands();
}

// Getters
// -------
static struct Location get_command_with_index(int i)
{
	struct Location temp;

	// Find out proper location in memory by using the start_byte position + the index
	// --------------------------------------------------------------------------------
	if (i > g.waypoint_total) {
		Serial.println("XCD");

		// we do not have a valid command to load
		// return a WP with a "Blank" id
		temp.id = CMD_BLANK;

		// no reason to carry on
		return temp;

	}else{
		//Serial.println("LD");
		// we can load a command, we don't process it yet
		// read WP position
		long mem = (WP_START_BYTE) + (i * WP_SIZE);

		temp.id = eeprom_read_byte((uint8_t*)mem);

		mem++;
		temp.options = eeprom_read_byte((uint8_t*)mem);

		mem++;
		temp.p1 = eeprom_read_byte((uint8_t*)mem);

		mem++;
		temp.alt = (long)eeprom_read_dword((uint32_t*)mem);	// alt is stored in CM! Alt is stored relative!

		mem += 4;
		temp.lat = (long)eeprom_read_dword((uint32_t*)mem); // lat is stored in decimal * 10,000,000

		mem += 4;
		temp.lng = (long)eeprom_read_dword((uint32_t*)mem); // lon is stored in decimal * 10,000,000
	}

	// Add on home altitude if we are a nav command (or other command with altitude) and stored alt is relative
	if((temp.id < MAV_CMD_NAV_LAST || temp.id == MAV_CMD_CONDITION_CHANGE_ALT) && temp.options & WP_OPTION_ALT_RELATIVE){
		//temp.alt += home.alt;
	}
	//Serial.println("ADD ALT");

	if(temp.options & WP_OPTION_RELATIVE){
		// If were relative, just offset from home
		temp.lat	+=	home.lat;
		temp.lng	+=	home.lng;
	}

	return temp;
}

// Setters
// -------
static void set_command_with_index(struct Location temp, int i)
{
	i = constrain(i, 0, g.waypoint_total.get());
	uint32_t mem = WP_START_BYTE + (i * WP_SIZE);

	eeprom_write_byte((uint8_t *)	mem, temp.id);

	mem++;
	eeprom_write_byte((uint8_t *)	mem, temp.options);

	mem++;
	eeprom_write_byte((uint8_t *)	mem, temp.p1);

	mem++;
	eeprom_write_dword((uint32_t *)	mem, temp.alt);	// Alt is stored in CM!

	mem += 4;
	eeprom_write_dword((uint32_t *)	mem, temp.lat);	// Lat is stored in decimal degrees * 10^7

	mem += 4;
	eeprom_write_dword((uint32_t *)	mem, temp.lng); // Long is stored in decimal degrees * 10^7
}

static void increment_WP_index()
{
    if (g.waypoint_index < g.waypoint_total) {
        g.waypoint_index.set_and_save(g.waypoint_index + 1);
		//SendDebug("MSG <increment_WP_index> WP index is incremented to ");
	}

    SendDebugln(g.waypoint_index,DEC);
}

/*
static void decrement_WP_index()
{
    if (g.waypoint_index > 0) {
        g.waypoint_index.set_and_save(g.waypoint_index - 1);
    }
}*/

static long read_alt_to_hold()
{
	if(g.RTL_altitude < 0)
		return current_loc.alt;
	else
		return g.RTL_altitude;// + home.alt;
}


//********************************************************************************
// This function sets the waypoint and modes for Return to Launch
// It's not currently used
//********************************************************************************

static Location get_LOITER_home_wp()
{
	//so we know where we are navigating from
	next_WP = current_loc;

	// read home position
	struct Location temp 	= get_command_with_index(0);	// 0 = home
	temp.id 				= MAV_CMD_NAV_LOITER_UNLIM;
	temp.alt 				= read_alt_to_hold();
	return temp;
}

/*
This function sets the next waypoint command
It precalculates all the necessary stuff.
*/

static void set_next_WP(struct Location *wp)
{
	//SendDebug("MSG <set_next_wp> wp_index: ");
	//SendDebugln(g.waypoint_index, DEC);
	gcs.send_message(MSG_COMMAND_LIST, g.waypoint_index);

	// copy the current WP into the OldWP slot
	// ---------------------------------------
	prev_WP = next_WP;

	// Load the next_WP slot
	// ---------------------
	next_WP = *wp;

	// used to control and limit the rate of climb - not used right now!
	// -----------------------------------------------------------------
	target_altitude = current_loc.alt;

	// this is used to offset the shrinking longitude as we go towards the poles
	float rads 			= (abs(next_WP.lat)/t7) * 0.0174532925;
	scaleLongDown 		= cos(rads);
	scaleLongUp 		= 1.0f/cos(rads);

	// this is handy for the groundstation
	wp_totalDistance 	= get_distance(&current_loc, &next_WP);
	wp_distance 		= wp_totalDistance;
	target_bearing 		= get_bearing(&current_loc, &next_WP);
	nav_bearing 		= target_bearing;

	// to check if we have missed the WP
	// ----------------------------
	saved_target_bearing = target_bearing;

	// set a new crosstrack bearing
	// ----------------------------
	crosstrack_bearing 	= target_bearing;	// Used for track following

	gcs.print_current_waypoints();
}


// run this at setup on the ground
// -------------------------------
static void init_home()
{
	// block until we get a good fix
	// -----------------------------
	while (!g_gps->new_data || !g_gps->fix) {
		g_gps->update();
	}

	home.id 	= MAV_CMD_NAV_WAYPOINT;
	home.lng 	= g_gps->longitude;				// Lon * 10**7
	home.lat 	= g_gps->latitude;				// Lat * 10**7
	//home.alt 	= max(g_gps->altitude, 0);		// we sometimes get negatives from GPS, not valid
	home.alt 	= 0;							// this is a test
	home_is_set = true;

	// to point yaw towards home until we set it with Mavlink
	target_WP 	= home;

	//Serial.printf_P(PSTR("gps alt: %ld\n"), home.alt);

	// Save Home to EEPROM
	// -------------------
	// no need to save this to EPROM
	set_command_with_index(home, 0);
	print_wp(&home, 0);

	// Save prev loc this makes the calcs look better before commands are loaded
	prev_WP = home;
	// this is dangerous since we can get GPS lock at any time.
	//next_WP = home;
}



