#ifndef CG_COURSE_PROPERIES_H
#define CG_COURSE_PROPERIES_H

class RenderProperties
{
public:
    RenderProperties() = default;

    RenderProperties(int screen_width, int screen_height, int viewport_height, int focal_length, double ambient,
                     int max_depth) :
            s_width(screen_width), s_height(screen_height), v_height(viewport_height), f_len(focal_length),
            ambient(ambient), max_depth(max_depth)
    {};
public:
    int s_width, s_height, v_height, f_len, max_depth;
    double ambient;
};

class ObjectProperties
{
public:
    ObjectProperties() = default;

    ObjectProperties(double diffuse, double specular, double shine, double reflective, double refraction)
            : diffuse(diffuse), specular(specular), shine(shine), reflective(reflective), refraction(refraction)
    {};
public:
    double diffuse, specular, shine, reflective, refraction;
};

class LightProperties
{

};

#endif
