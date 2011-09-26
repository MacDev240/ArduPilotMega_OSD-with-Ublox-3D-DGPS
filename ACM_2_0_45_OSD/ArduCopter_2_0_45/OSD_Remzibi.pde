// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
// OSD_Remzibi //mjc
//#include <GPS.h> //mjc

#if OSD_PROTOCOL != OSD_DISABLED

#if OSD_PORT == 3
#define SendSer		Serial3.print
#define SendSerln	Serial3.println
#elif OSD_PORT == 2
#define SendSer		Serial2.print
#define SendSerln	Serial2.println
#elif OSD_PORT == 1
#define SendSer		Serial1.print
#define SendSerln	Serial1.println
#else
#define SendSer		Serial.print
#define SendSerln	Serial.println
#endif

static byte oldOSDSwitchPosition = 1;


static void read_osd_switch()
{
	byte osdSwitchPosition = readOSDSwitch();
	if (oldOSDSwitchPosition != osdSwitchPosition){ //switch change detected
		
		switch(osdSwitchPosition)
		{
			case 1: // OSD_Ch position "ON"
			    set_osd_mode(1);
			break;

			case 2: // OSD_Ch position "OFF"
			    set_osd_mode(0);
			break;
		}

		oldOSDSwitchPosition = osdSwitchPosition; //set to current position
	}
}

static byte readOSDSwitch(void){
  	int osdPulseWidth = APM_RC.InputCh(OSD_MODE_CHANNEL-1); //default init condition OSD Overlay ON mjc
//  Set OSD "ON" above  1100 allows OSD camera pan with mix from rudder mjc
	if (osdPulseWidth > 1100)  return 1; // Overlay ON above 1100, May optioally drop gear down, trigger event on mjc
//  Set OSD "OFF" below 1100 allows OSD camera pan with mix from rudder range 1200-1800 mjc
	if (osdPulseWidth <= 1100)  return 0; // Overlay OFF below 1100, May optioally bring gear up, trigger event off mjc
			return 0;
}


static void set_osd_mode(int mode){
		switch(mode)
		{
			case 1: // Overlay On
                        SendSerln("$CLS");
                        SendSerln("$L1");
                        //gcs.send_text_P(SEVERITY_LOW,PSTR("$CLS"));
                        //gcs.send_text_P(SEVERITY_LOW,PSTR("$L1"));
			break;

			case 0: // Overlay Off
			SendSerln("$L0");
                        SendSerln("$CLS");
                        //gcs.send_text_P(SEVERITY_LOW,PSTR("$L0"));
                        //gcs.send_text_P(SEVERITY_LOW,PSTR("$CLS"));
			break;
		}
}

static void print_osd_data(void)  // send GPS data to Remzibi OSD
{
        double nMult=0;
        int nMeters=1; //Set this to 1 for meters, 0 for feet mjc

        if (nMeters==1) {
          nMult=1;
        } else {
          nMult=3.2808399;
        }

	SendSer("$A,");// Remzibi attitude/position message
	SendSer((float)current_loc.lat/10000000,5); //Latitude XXX.XXXXX
	SendSer(",");
	SendSer((float)current_loc.lng/10000000,5); //Longitude XXX.XXXXX
	SendSer(",");
	SendSer(int(g_gps->num_sats)); //Satellite Count (Locked only) XX  
	SendSer(",");
        SendSer(wp_distance*nMult/100,2); //Distance to Waypoint XXXXX.00
	SendSer(",");
	SendSer(current_loc.alt*nMult/100,2); //Altitude = XXXXX.00
	SendSer(",");
	SendSer(g_gps->ground_speed/100,DEC); //Ground Speed XXX
	SendSer(",");
 	SendSer(target_bearing/100,DEC); //Heading whole degrees XXX
       	SendSer(",");
//	SendSer(g_gps->date,DEC); //Date
	SendSer(",");
//	SendSer(g_gps->time,DEC); //Time
/* 
	SendSer(battery_voltage1,2); //Battery voltage = XX.00
	SendSer(",");
	SendSer(int(g_gps->h_dop)); //Horizontal _DOP
*/
        SendSerln();

//        SendSer("$M"); // Remzibi generic message header
//        SendSer("82"); // Hex Column (01h - 1Eh) for small fonts add 80h (81h - 9Eh) 
//        SendSer("0B"); // 0B = 1st row below AH Hex Row (01h - 0Dh for NTSC, 01h - 10h for PAL) 
//        SendSer("EA"); // E9 = any symbol Hex address of First Character mjc
//        SendSer("00"); // 00 = none Hex address of Last Character mjc
        
	SendSer("$M820BEA00");    // Remzibi message format     APM data Line 1

	switch (control_mode){
  
	      //case MANUAL:
			//SendSer("MANUAL   ");  //pad spaces to blank out any preivous text mjc
                        //break;
	      case STABILIZE:
			SendSer("STABILIZE");
                        break;
              case ACRO:
			SendSer("ACRO     ");
                        break;

              case ALT_HOLD:
			SendSer("ALT_HOLD  ");
                        break;
		//case FLY_BY_WIRE_A:
			//SendSer("FBW:A    ");
                        //break;
		//case FLY_BY_WIRE_B:
			//SendSer("FBW:B    ");
                        //break;
                //        
		case AUTO:
			SendSer("WP");
                        SendSer(int(g.waypoint_index));  // mjc 
                        SendSer(":");
                        SendSer(int(wp_distance*nMult));  // mjc
                        SendSer("  "); 
                        //SendSer("\t");
                        break;
                //        
                case GUIDED:
			SendSer("GUIDED   ");
                        break;
                case LOITER:
			SendSer("LOITER   ");
                        break;
		case RTL:
			SendSer("RTL:");
                        SendSer(int(wp_distance*nMult));  // mjc
                        SendSer(" ");  //pad spaces to blank out any preivous text mjc
                        break;
                case CIRCLE:
			SendSer("CIRCLE   ");
                        break;
		//case TAKEOFF:
			//SendSer("TAKEOFF   ");
                        //break;
		//case LAND:
			//SendSer("LAND      ");
                        //break;
                        
               }
                SendSer(" TX ");
		SendSer(battery_voltage1,2); //message type battery_votage1 = XX.00 mjv
		SendSer(" HDP "); //mjc
		//SendSer(g_gps->hdop,DEC); //message type positional P_DOP = XX.00 mjc for standard UBLOX
		SendSer(g_gps->h_dop,DEC); //message type horizontal H_DOP = XX.00 for UBLOX_DL mjc
		SendSer(" "); //pad space mjc
                SendSerln();

}

//      Send addional messages if needed to line 2 //mjc
static void print_osd_message(void)
{
  
  osd_message_type = control_mode; // TM aasci only, Debug only, Payload, Alarms, User IDs, COA Info, Keys, AUDIO pcm) Testing line 2 mjc
    #if osd_message == enabled
    
	//SendSer("$M"); // Remzibi generic message
	//SendSer("82"); // Hex Column (01h - 1Eh) for small fonts add 80h (81h - 9Eh) 
	//SendSer("0C"); // 0B =2nd row below AH Hex Row (01h - 0Dh for NTSC, 01h - 10h for PAL) 
	//SendSer("E9"); // E9 = i antenna symbol Hex address of First Character mjc
	//SendSer("00"); // 00 = none Hex address of Last Character mjc

	SendSer("$M820CE900"); //Remzibi  APM data Line 2

	switch (osd_message_type){ // based on Mode 
  	  case 0: // STABILIZE mode message 
  		//
		SendSer("P ");
		//SendSer(cam_yaw, DEC); // raw camera pan angle, limited to 180° or 360° mjc
		//SendSer(track_pan_deg/100, DEC); //pan angle tracker view from center (home is default) // limited to 180° or 360° mjc
		SendSer(((dcm.yaw_sensor/100) %180),DEC); // sim pan angle, remove after test mjc
		//SendSer(((dcm.roll_sensor/100) %180),DEC); // sim pan angle, remove after test mjc

		SendSer(" T ");
		//SendSer(tilt_degrees/100, DEC); //auto tracker angle pilot & HD view
		SendSer(-(dcm.pitch_sensor/100),DEC); // imu tilt angle, +-90°
		//SendSer(cam_pitch, DEC); // raw camera tilt angle, +-45° or +-90°

		SendSer(" R ");
		//SendSer(-(track_theta/100), DEC); //tilt angle pilot view
		//SendSer(cam_roll, DEC); // raw camera roll angle, +-45° or +-90°
		SendSer(((dcm.roll_sensor/100) %180),DEC); // sim pan angle, remove after test mjc
		//SendSer(-(dcm.pitch_sensor/100),DEC); // sim tilt angle, remove after test mjc
		//SendSer(camera_id); //camera to control/view
  		//
		//SendSer("P 000"); // remove after display test mjc
		//SendSer(" T -00"); // mjc remove after display test 
		//SendSer(" Zm 1.0"); // zoom power factor 1.0 = none 1.0 to 5.0 only positive
		//SendSer(" VDP "); 
		//SendSer(g_gps->v_dop); //message type horizontal _DOP = XX.00 mjc
		//SendSer(" PDP "); 
		//SendSer(g_gps->p_dop); //message type position _DOP = XX.00 mjc
		SendSer("    "); //pad 1 space mjc

		//message type blank line 
		//SendSer("                          "); //message type blank line 
//
	        break;
	  case 1: // STABILIZE
		SendSer("1 "); //message mode 1 
	        break;
	  case 2: // Fail Safe ON
		SendSer("FS-ON RTL "); //message mode 2
	        break;
	  case 3: // ALT_HOLD
		//SendSer("ALT "); //message mode 3 SendSer(current_loc.alt,DEC);
		//SendSer(current_loc.alt,DEC);
		SendSer("HOLD ");
		SendSer(current_loc.alt/10, DEC);
		SendSer(" NXT-WP ");
		SendSer(next_WP.alt/10,DEC);
		SendSer("  "); //pad 6 spaces mjc

	        break;
	  case 4: // TAKE-OFF ??
		//SendSer("4 AUTO "); //message mode 4
		// AUTO - follow waypoints
		//SendSer("AUTO P ");
		//SendSer(track_pan_deg/100, DEC); //pan angle auto tracker view from center (home is default) // limited to 180° or 360° mjc
		//SendSer(cam_yaw, DEC); //pan angle tracker view
		//SendSer(" TL ");
		//SendSer(-(cam_pitch),DEC); // raw camera tilt angle, reversed for bottom mount gymbal
		//SendSer(" T ");
		//SendSer(track_theta/100, DEC); //roll angle caamera auto tracker
		//SendSer(cam_roll, DEC); //raw camera tilt angle

		//SendSer("SEE MESSAGES FROM CGS PORT 0"); //message type 10 Payload
		//SendSer(" DIF "); 
		//SendSer(g_gps->dgps_fix,DEC); //message nav fix_type mjc
		//SendSer(" HDP "); 
		//SendSer(g_gps->h_dop,DEC); //message Vertical_DOP = XX.00 mjc
		SendSer("VDP "); 
		SendSer(g_gps->v_dop); //message type Horizontal_DOP = XX.00 mjc
		SendSer(" PDP "); 
		SendSer(g_gps->p_dop); //message type Position_DOP = XX.00 mjc
		//SendSer(" "); //pad 1 space mjc

	        break;
	  case 5: // Fly-By-Wire-A
		SendSer("5 "); //message mode 5 
	        break;
	  case 6:
		SendSer("6 "); //message mode 6
	        break;
	  case 7:
		SendSer("7 "); //message type 7
	        break;
	  case 8:
		SendSer("8 "); //message type 8 
	        break;
	  case 9:
		SendSer("9 "); //message type 9 
	        break;
/*
	  case 10: // AUTO - follow waypoints
		//SendSer("AUTO P ");
		//SendSer(track_pan_deg/100, DEC); //pan angle auto tracker view from center (home is default) // limited to 180° or 360° mjc
		//SendSer(cam_yaw, DEC); //pan angle tracker view
		//SendSer(" TL ");
		//SendSer(-(cam_pitch),DEC); // raw camera tilt angle, reversed for bottom mount gymbal
		//SendSer(" T ");
		//SendSer(track_theta/100, DEC); //roll angle caamera auto tracker
		//SendSer(cam_roll, DEC); //raw camera tilt angle

		//SendSer("SEE MESSAGES FROM CGS PORT 0"); //message type 10 Payload
		SendSer(" DIF "); 
		SendSer(g_gps->dgps_fix,DEC); //message nav fix_type mjc
		SendSer(" HDP "); 
		SendSer(g_gps->h_dop,DEC); //message Vertical_DOP = XX.00 mjc
		SendSer(" VDP "); 
		SendSer(g_gps->v_dop); //message type Horizontal_DOP = XX.00 mjc
		SendSer(" PDP "); 
		SendSer(g_gps->p_dop); //message type Position_DOP = XX.00 mjc
		SendSer(" "); //pad 1 space mjc
*/
 	       }
         SendSerln(); // end Send osd_message
         
    #endif
}
//

static void print_osd_ahrs(void) // Remzibi Artificial Horizon message
{
	SendSer("$I,");// Remzibi artificial horizon message header 
	SendSer((dcm.roll_sensor/100),DEC);  // to reverse Roll use *-1
  
   
        SendSer(",");
	SendSer((dcm.pitch_sensor/100),DEC); // to reverse Pitch use *-1
	SendSer(",");
        SendSerln();
} 

static void print_callsign_on(void)
{
    	//SendSer("$M");
    	//SendSer("82"); // Hex Column (01h - 1Eh) for small fonts add 80h (81h - 9Eh) 
    	//SendSer("0C"); // Hex Row (01h - 0Dh for NTSC, 01h - 10h for PAL) 
    	//SendSer("00"); // Hex address of First Character
    	//SendSer("00"); // Hex address of Last Character
    
    	SendSer("$M950C0000"); // Reads:  Small font, Col 21, Row 12 (line 2 APM data) Blank , Blank.
    	SendSer(CALLSIGN_TEXT); // call_sign
//  	#define call_sign == MACDEV240;  Len(call_sign) =9 characters == call_sign_length(9)
//  	SendSer("8..............9...MACDEV240."); // 30 characters in line, so col_start(21) = line_lenght(29) - call_sign_length(9)
//      SendSer("123456789ABCDEF_123456789ABCDE"); // Note: measure Columns (Col) here So, col_start = 95h
//      SendSer("123456789_123456789_123456789_"); //
    	SendSerln();
}

static void print_callsign_off(void)
{
    	//SendSer("$M");
    	//SendSer("82"); // Hex Column (01h - 1Eh) for small fonts add 80h (81h - 9Eh) 
    	//SendSer("0C"); // Hex Row (01h - 0Dh for NTSC, 01h - 10h for PAL) 
    	//SendSer("00"); // Hex address of First Character
    	//SendSer("00"); // Hex address of Last Character
    
    	SendSer("$M950C0000"); // Reads:  Small font, Col 18, Row 12 (line 2 APM data) Blank , Blank.
    	SendSer("              "); // call_sign_lenght (9) 
//      SendSer("123456789_123456789_123456789"); //
    	SendSerln();
}

static void osd_init_home(void)
{
        SendSer("$SH");
        SendSerln();
        SendSer("$CLS");
        SendSerln(); 
}

static void osd_clear(void)
{
        SendSer("$CLS");
        SendSerln(); 
}
#endif
