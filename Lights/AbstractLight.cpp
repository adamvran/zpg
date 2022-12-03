#include "AbstractLight.h"

AbstractLight::AbstractLight()
{
	this->strength = 1;
	this->shiness = 64;
    this->type = static_cast<LightType>(NULL);
}
