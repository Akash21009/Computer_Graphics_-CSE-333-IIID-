#include "ray.h"

bool Ray::setParameter(const float par, const Object *obj)
{
	if(par < t && par > SMALLEST_DIST)
	{
		hit = true;
		t = par;
		object = obj;
		return true;
	}
	return false;
}
