#include "Light.h"

Light::Light(Vec3d origin, double I) : origin(origin), I(I)
{

}

void Light::transform(const Matix4x3d &transform_matrix)
{
    //todo
}
