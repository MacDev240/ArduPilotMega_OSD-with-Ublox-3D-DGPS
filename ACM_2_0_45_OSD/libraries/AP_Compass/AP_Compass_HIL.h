#ifndef AP_Compass_HIL_H
#define AP_Compass_HIL_H

#include "Compass.h"

class AP_Compass_HIL : public Compass
{
  public:
	AP_Compass_HIL(AP_Var::Key key = AP_Var::k_key_none) : Compass(key) { product_id = AP_COMPASS_TYPE_HIL; }

	void 			read();
    void 	    	setHIL(float Mag_X, float Mag_Y, float Mag_Z);
};

#endif
