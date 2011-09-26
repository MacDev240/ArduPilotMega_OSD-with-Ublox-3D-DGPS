// Example config file. Take a look at confi.h. Any term define there can be overridden by defining it here.
//#define GPS_PROTOCOL  GPS_PROTOCOL_UBLOX
#define GPS_PROTOCOL  GPS_PROTOCOL_UBLOX_DL
//#define GPS_PROTOCOL  GPS_PROTOCOL_MTK
//#define GPS_PROTOCOL  GPS_PROTOCOL_MTK16
// uncomment GPS protocal to select mjc
// GPS is auto-selected by takes up extra 4k of memory mjc//

#define GCS_PROTOCOL  GCS_PROTOCOL_MAVLINK //LEGACY //STANDARD //XPLANE //MAVLINK

#define GCS_PORT	0  //mjc 0 bench testing to HK_GCS, or HIL no Xbee
#define SERIAL0_BAUD    57600 //38400 //57600 //115200

#define MAGNETOMETER    ENABLED
#define MAG_ORIENTATION	 AP_COMPASS_COMPONENTS_DOWN_PINS_FORWARD //default

#define CAMERA_STABILIZER   ENABLED //ENABLED //DISABLED

//#define LOITER_TEST 1
//
// Traditional Heli
#define AUTO_RESET_LOITER 1  //  for Tradional Heli use
//
//

#define BROKEN_SLIDER	0 // 1 = yes (use Yaw to enter CLI mode)

#define FRAME_CONFIG HELI_FRAME
	/*
	options:
	QUAD_FRAME
	TRI_FRAME
	HEXA_FRAME
	Y6_FRAME
	OCTA_FRAME
	HELI_FRAME
	*/

#define FRAME_ORIENTATION X_FRAME
	/*
	PLUS_FRAME
	X_FRAME
        V_FRAME
	*/

//
#define OSD_PROTOCOL        OSD_PROTOCOL_REMZIBI //DISABLED //REMZIBI //EAGLETREE_PRO (not ready yet mjc)
#define CALLSIGN            ENABLED //DISABLED  // ENABLE = send callsign
#define CALLSIGN_TEXT	    "MACDEV240 12345" //enter UPPER CASE only 14 chars max
#define OSD_PORT            3
#define OSD_MODE_CHANNEL    5 //  DX-7 & XP7202 Gear mjc
#define SERIAL3_BAUD        57600 //38400 //57600 //  drops sync at 115200
//

#define FLIGHT_MODE_CHANNEL   7 // ch 5-8 only

#define CHANNEL_6_TUNING CH6_NONE // DX-7 & XP7202 AUX2
	/*
	CH6_NONE
	CH6_STABLIZE_KP
	CH6_STABLIZE_KI
	CH6_RATE_KP
	CH6_RATE_KI
	CH6_THROTTLE_KP
	CH6_THROTTLE_KD
	CH6_YAW_KP
	CH6_YAW_KI
	CH6_YAW_RATE_KP
	CH6_YAW_RATE_KI
	CH6_TOP_BOTTOM_RATIO
	CH6_PMAX
	CH6_BARO_KP
	CH6_BARO_KD
	CH6_SONAR_KP
	CH6_SONAR_KD
	CH6_RELAY
	CH6_Y6_SCALING
	*/

// See the config.h and defines.h files for how to set this up!
//
// lets use SIMPLE mode for Roll and Pitch during Alt Hold
#define ALT_HOLD_RP 		ROLL_PITCH_SIMPLE

// lets use Manual throttle during Loiter
//#define LOITER_THR		THROTTLE_MANUAL
# define RTL_YAW 		YAW_HOLD

//#define ACRO_RATE_TRIGGER 2200
// if you want full ACRO mode, set value to 0
// if you want mostly stabilize with flips, set value to 4200

// roll
#define STABILIZE_ROLL_P 0.70
#define STABILIZE_ROLL_I 0.025
#define STABILIZE_ROLL_D 0.04
#define STABILIZE_ROLL_IMAX 7
// pitch
#define STABILIZE_PITCH_P 0.70
#define STABILIZE_PITCH_I 0.025
#define STABILIZE_PITCH_D 0.04
#define STABILIZE_PITCH_IMAX 7
// yaw stabilise
#define STABILIZE_YAW_P  0.7
#define STABILIZE_YAW_I  0.02
#define STABILIZE_YAW_D  0.0
// yaw rate  -- not used
#define RATE_YAW_P  0.135   
#define RATE_YAW_I  0.0
#define RATE_YAW_D  0.0
// throttle
#define THROTTLE_P 0.22
#define THROTTLE_I 0.001
#define THROTTLE_IMAX 300
// navigation
#define NAV_P  2.64
#define NAV_I  0.03
#define NAV_IMAX  10

// setup for 3 Standard Flight Modes on DX-7 & XP7202 Flaps disable for Turnigy9x or other pot control TX mjc
#define FLIGHT_MODE_1         ALT_HOLD
#define FLIGHT_MODE_2         ALT_HOLD
#define FLIGHT_MODE_3         AUTO
#define FLIGHT_MODE_4         AUTO
#define FLIGHT_MODE_5         STABILIZE
#define FLIGHT_MODE_6         STABILIZE

// Experimental!!
// Yaw is controled by targeting home. you will not have Yaw override.
// flying too close to home may induce spins.
#define SIMPLE_LOOK_AT_HOME 0
#define DYNAMIC_DRIFT 0 	// careful!!! 0 = off, 1 = on

// Dataflash logging control //saves more room 
#define LOG_ATTITUDE_FAST		DISABLED
#define LOG_ATTITUDE_MED 	ENABLED
#define LOG_GPS 		ENABLED
#define LOG_PM 				DISABLED
#define LOG_CTUN			DISABLED
#define LOG_NTUN			DISABLED
#define LOG_MODE			DISABLED
#define LOG_RAW				DISABLED
#define LOG_CUR				DISABLED
#define LOG_CMD			ENABLED

// Defaults for tradional heli mjc
#define WP_RADIUS_DEFAULT	5
#define LOITER_RADIUS_DEFAULT	20
#define USE_CURRENT_ALT		TRUE
#define ALT_HOLD_HOME		18
//


