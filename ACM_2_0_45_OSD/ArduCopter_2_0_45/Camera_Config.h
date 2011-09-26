// ----- Camera variables -------
// ------------------------------
struct Location GPS_mark;			// GPS location to monitor
//struct Location last_pic_wp;			// Special project DO NOT UNCOMMENT
int 	picture_time = 0;			// waypoint trigger variable
int 	ptv = 0;				// video toggle switch mjc??
int 	thr_pic = 0;				// timer variable for throttle_pic
int 	pos;					// pos mjc??

float	cur_pitch;				// current pitch of plane from DCM
float	cur_roll;				// current roll of plane from DCM
float	cur_yaw;				// current yaw of plane from DCM
long	cam_yaw;				// current yaw of plane in degrees *100
long	cam_pitch;				// current pitch of plane in degrees *100
long	cam_roll;				// current roll of plane in degrees *100
long	track_bearing;				// deg * 100 : 0 to 360 location of the plane to the target
long	old_track_bearing;			// deg * 100 : 0 to 360 location of the plane to the target
long 	track_distance;				// distance in metres
long	track_altitude;				// distance in metres - I assume
long	track_theta;				// deg * 100 : 0 to 180 location of the plane to the target
long	track_pan_left;				// Pan servo left limit
long	track_pan_right;			// Pan servo right limit
long	track_pan_deg;				// Pan servo angle in relation to center
long	track_oor_l;				// intermediate variable
long	track_oor_r;				// intermediate variable

long	track_tilt_left;			// Tilt servo left limit
long	track_tilt_right;			// Tilt servo right limit
long	track_tilt_deg;				// Tilt servo angle in relation to center
long	track_oot_l;				// Out of range left servo limit
long	track_oot_r;				// Out of range right servo limit


//
// ----- Camera defintions ------
// ------------------------------
//#define OPEN_SERVO		7		// w-5 Retraction servo channel - my camera retracts yours might not.
//
#define CAM_SERVO		8		// w-8 Camera servo channel
#define CAM_ANGLE		15		// Set angle in degrees
#define CAM_CLICK		45		// This is the position of the servo arm when it actually clicks
//
#define PAN_SERVO		5		// w-6 Pan servo channel  Camera_roll_CH
#define PAN_REV			1		// output is normal = 1 output is reversed = -1
#define PAN_CENTER		0		// Camera center bearing with relation to airframe forward motion - deg * 100
#define PAN_RANGE		360		// Pan Servo sweep in degrees,  // Pan Servo sweep - deg * 100 //180 //360 mjc
#define PAN_RATIO		10.31		// match this to the swing of your pan servo
//
#define TILT_SERVO		6		// w-7 Tilt servo channel Camera_pitch_CH
#define TILT_REV		1		// output is normal = 1 output is reversed = -1
#define TILT_CENTER		0		// Camera center bearing with relation to airframe forward motion - deg
#define TILT_RANGE		180		// Tilt Servo sweep in degrees
#define TILT_RATIO		10.31		// match this to the swing of your tilt servo




