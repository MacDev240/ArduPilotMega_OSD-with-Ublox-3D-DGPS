// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: t -*-

#include "GPS.h"
#include "WProgram.h"

void
GPS::update(void)
{
	bool	result;

	// call the GPS driver to process incoming data
	result = read();

	// if we did not get a message, and the idle timer has expired, re-init
	if (!result) {
		if ((millis() - _idleTimer) > _idleTimeout) {
			_status = NO_GPS;
			init();

			// reset the idle timer
			_idleTimer = millis();
		}
	} else {
		// we got a message, update our status correspondingly
		_status = fix ? GPS_OK : NO_FIX;

		valid_read = true;
		new_data = true;

		// reset the idle timer
		_idleTimer = millis();
	}
}

void 
GPS::setHIL(long time, float latitude, float longitude, float altitude,
            float ground_speed, float ground_course, float speed_3d, uint8_t num_sats)
{
}

// XXX this is probably the wrong way to do it, too
void
GPS::_error(const char *msg)
{
	Serial.println(msg);
}
