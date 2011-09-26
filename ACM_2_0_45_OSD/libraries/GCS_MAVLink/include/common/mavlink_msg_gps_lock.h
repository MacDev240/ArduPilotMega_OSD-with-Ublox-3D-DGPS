// MESSAGE GPS_LOCK PACKING //mjc 9-12-2011

#define MAVLINK_MSG_ID_GPS_LOCK 15  // 0e (Andrew T. please reserve this Mesage ID x_0e for UBLOX_DL) mjc

typedef struct __mavlink_gps_lock_t 
{
	uint64_t usec;     ///< Timestamp (microseconds since UNIX epoch or microseconds since system boot)
	uint8_t fix_type;  ///< 0-1: NO fix, 2: 2D fix, 3: 3D fix, 4: 3D/DGPS fix, 5: Time only fix. Some applications will not use the value of this field unless it is at least two, so always correctly fill in the fix.
	uint8_t num_sats;  ///< Satellites used for fix
	uint8_t dgps_fix;  ///< DGPS fix 1= ON  0= Waiting/OFF
	uint16_t h_dop;    ///< GPS HDOP Horizontal Dilution of precision
	uint16_t v_dop;    ///< GPS VDOP Vertical Dilution of precision	
	uint16_t p_dop;    ///< GPS PDOP Posvition Dilution of precision
	
} mavlink_gps_lock_t;

#define MAVLINK_MSG_ID_GPS_LOCK_LEN 26
#define MAVLINK_MSG_ID_15_LEN 26



#define MAVLINK_MESSAGE_INFO_GPS_LOCK { \
	"GPS_LOCK", \
	9, \
	{  { "usec", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_gps_lock_t, usec) }, \
		{ "fix_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 8, offsetof(mavlink_gps_lock_t, fix_type) }, \
		{ "num_sats", NULL, MAVLINK_TYPE_UINT8_T, 0, 9, offsetof(mavlink_gps_lock_t, num_sats) }, \
		{ "dgps_fix", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_gps_lock_t, dgps_fix) }, \
		{ "h_dop", NULL, MAVLINK_TYPE_UINT16_T, 0, 14, offsetof(mavlink_gps_lock_t, H_DOP) }, \
		{ "v_dop", NULL, MAVLINK_TYPE_UINT16_T, 0, 18, offsetof(mavlink_gps_lock_t, V_DOP) }, \
		{ "p_dop", NULL, MAVLINK_TYPE_UINT16_T, 0, 22, offsetof(mavlink_gps_lock_t, P_DOP) }, \
	} \
}


/**
 * @brief Pack a gps_lock message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param usec Timestamp (microseconds since UNIX epoch or microseconds since system boot)
 * @param fix_type 0-1: no fix, 2: 2D fix, 3: 3D fix, 4: 3D/DGPS fix, 5: Time only fix.
 * @param num_sats Satellites used for lock
 * @param dgps_fix Differential GPS fix  1= ON  0= Waiting/OFF
 * @param h_dop GPS HDOP
 * @param v_dop GPS VDOP
 * @param p_dop GPS PDOP
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_gps_lock_pack(uint8_t system_id, uint8_t component_id,mavlink_message_t* msg,
												 uint64_t usec, uint8_t fix_type, uint8_t num_sats, uint8_t dgps_fix, uint16_t h_dop, uint16_t v_dop, uint16_t p_dop)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[26];
	_mav_put_uint64_t(buf, 0, usec);
	_mav_put_uint8_t(buf, 8, fix_type);
	_mav_put_uint8_t(buf, 9, num_sats);
	_mav_put_uint8_t(buf, 10, dgps_fix);
	_mav_put_uint16_t(buf, 14, h_dop);
	_mav_put_uint16_t(buf, 18, v_dop);
	_mav_put_uint16_t(buf, 22, p_dop);	
		memcpy(_MAV_PAYLOAD(msg), buf, 26);
#else
	mavlink_gps_raw_t packet;
	packet.usec = usec;
	packet.fix_type = fix_type;
	packet.num_sats = num_sats;
	packet.dgps_fix = dgps_fix;
	packet.h_dop = h_dop;
	packet.v_dop = v_dop;
	packet.p_dop = p_dop;	
		memcpy(_MAV_PAYLOAD(msg), &packet, 26);
#endif
	
	msg->msgid = MAVLINK_MSG_ID_GPS_LOCK;
	return mavlink_finalize_message(msg, system_id, component_id, 26);
}

 /**
 * @brief Pack a gps_lock message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
  * @param chan The MAVLink channel this message was sent over
  * @param msg The MAVLink message to compress the data into
  * @param usec Timestamp (microseconds since UNIX epoch or microseconds since system boot)
  * @param fix_type 0-1: no fix, 2: 2D fix, 3: 3D fix, 4: 3D/DGPS fix, 5: Time only fix.
  * @param Satellites used for lock
  * @param DGPS fix 1= ON  0= Waiting/OFF
  * @param h_dop GPS HDOP
  * @param v_dop GPS VDOP
  * @param p_dop GPS PDOP 
  */
static inline uint16_t mavlink_msg_gps_lock_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
												 mavlink_message_t* msg,
												 	uint64_t usec, uint8_t fix_type, uint8_t num_sats, uint8_t dgps_fix, uint16_t h_dop, uint16_t v_dop, uint16_t p_dop)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[26];
	_mav_put_uint64_t(buf, 0, usec);
	_mav_put_uint8_t(buf, 8, fix_type);
	_mav_put_uint8_t(buf, 9, num_sats);
	_mav_put_uint8_t(buf, 10, dgps_fix);
	_mav_put_uint16_t(buf, 14, h_dop);
	_mav_put_uint16_t(buf, 18, v_dop);
	_mav_put_uint16_t(buf, 22, p_dop);
	
		memcpy(_MAV_PAYLOAD(msg), buf, 26);
#else
	mavlink_gps_raw_t packet;
	packet.usec = usec;
	packet.fix_type = fix_type;
	packet.num_sats = num_sats;
	packet.dgps_fix = dgps_fix;
	packet.h_dop = h_dop;
	packet.v_dop = v_dop;
	packet.p_dop = p_dop;
	
		memcpy(_MAV_PAYLOAD(msg), &packet, 26);
#endif
	
	msg->msgid = MAVLINK_MSG_ID_GPS_LOCK;
	return mavlink_finalize_message_chan(msg, system_id, component_id, chan, 26);
}

/**
 * @brief Encode a gps_lock struct into a message
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param gps_lock C-struct to read the message contents from
 */

static inline uint16_t mavlink_msg_gps_lock_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_gps_lock_t* gps_lock)
{
	return mavlink_msg_gps_lock_pack(system_id, component_id, msg, gps_lock->usec, gps_lock->fix_type, gps_lock->num_sats, gps_lock->dgps_fix, gps_lock->h_dop, gps_lock->v_dop, gps_lock->p_dop);
}
/**
 * @brief Send a gps_lock message
 * @param chan MAVLink channel to send the message
 *
 * @param usec Timestamp (microseconds since UNIX epoch or microseconds since system boot)
 * @param fix_type 0-1: no fix, 2: 2D fix, 3: 3D fix, 4: 3D/DGPS fix, 5: Time only fix.
 * @param Satellites used for lock
 * @param DGPS fix 1= ON  0= Waiting/OFF
 * @param h_dop GPS HDOP
 * @param v_dop GPS VDOP
 * @param p_dop GPS PDOP 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_gps_lock_send(mavlink_channel_t chan,
											 uint64_t usec, uint8_t fix_type, uint8_t num_sats, uint8_t dgps_fix, uint16_t h_dop, uint16_t v_dop, uint16_t p_dop)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
	char buf[26];
	_mav_put_uint64_t(buf, 0, usec);
	_mav_put_uint8_t(buf, 8, fix_type);
	_mav_put_uint8_t(buf, 9, num_sats);
	_mav_put_uint8_t(buf, 10, dgps_fix);
	_mav_put_uint16_t(buf, 14, h_dop);
	_mav_put_uint16_t(buf, 18, v_dop);
	_mav_put_uint16_t(buf, 22, p_dop);
	
	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS_LOCK, buf, 26);
#else
	mavlink_gps_raw_t packet;
	packet.usec = usec;
	packet.fix_type = fix_type;
	packet.num_sats = num_sats;
	packet.dgps_fix = dgps_fix;
	packet.h_dop = h_dop;
	packet.v_dop = v_dop;
	packet.p_dop = p_dop;
	
	_mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_GPS_LOCK, (const char *)&packet, 26);
#endif
}

#endif

// MESSAGE GPS_LOCK UNPACKING

/**
 * @brief Get field usec from gps_lock message
 *
 * @return Timestamp (microseconds since UNIX epoch or microseconds since system boot)
 */
static inline uint64_t mavlink_msg_gps_lock_get_usec(const mavlink_message_t* msg)
{	
	return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field fix_type from gps_lock message
 *
 * @return 0-1: no fix, 2: 2D fix, 3: 3D fix, 4: 3D/DGPS fix, 5: Time only fix.
 */
static inline uint8_t mavlink_msg_gps_lock_get_fix_type(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  8);
}

/**
 * @brief Get field num_sats from gps_lock message
 *
 * @return Satellites used for lock
 */
static inline uint8_t mavlink_msg_gps_lock_get_num_sats(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  9);
}

/**
 * @brief Get field dgps_fix from gps_lock message
 *
 * @return DGPS fix 1= ON  0= Waiting/OFF
 */
static inline uint8_t mavlink_msg_gps_lock_get_dgps_fix(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint8_t(msg,  10);
}

/**
 * @brief Get field h_dop from gps_lock message
 *
 * @return GPS H_DOP
 */
static inline uint16_t mavlink_msg_gps_lock_get_h_dop(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  14);
}

/**
 * @brief Get field v_dop from gps_lock message
 *
 * @return GPS V_DOP
 */
static inline uint16_t mavlink_msg_gps_lock_get_v_dop(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  18);
}

/**
 * @brief Get field p_dop from gps_lock message
 *
 * @return GPS P_DOP
 */
static inline uint16_t mavlink_msg_gps_lock_get_p_dop(const mavlink_message_t* msg)
{
	return _MAV_RETURN_uint16_t(msg,  22);
}
/**
 * @brief Decode a gps_lock message into a struct
 *
 * @param msg The message to decode
 * @param gps_lock C-struct to decode the message contents into
 */
static inline void mavlink_msg_gps_lock_decode(const mavlink_message_t* msg, mavlink_gps_lock_t* gps_lock)
{
#if MAVLINK_NEED_BYTE_SWAP
	gps_lock->usec = mavlink_msg_gps_lock_get_usec(msg);
	gps_lock->fix_type = mavlink_msg_gps_lock_get_fix_type(msg);
	gps_lock->num_sats = mavlink_msg_gps_lock_get_num_sats(msg);
	gps_lock->dgps_fix = mavlink_msg_gps_lock_get_dgps_fix(msg);
	gps_lock->h_dop = mavlink_msg_gps_lock_get_h_dop(msg);
	gps_lock->v_dop = mavlink_msg_gps_lock_get_v_dop(msg);
	gps_lock->p_dop = mavlink_msg_gps_lock_get_p_dop(msg);
#else
	memcpy(gps_lock, _MAV_PAYLOAD(msg), 26);
#endif
}
