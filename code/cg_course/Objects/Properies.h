#ifndef CG_COURSE_PROPERIES_H
#define CG_COURSE_PROPERIES_H

class RenderProperties
{
public:
    RenderProperties() = default;

    RenderProperties(int screen_width, int screen_height, int viewport_height, double focal_length, double ambient,
                     int max_depth, double mi_world) :
            s_width(screen_width), s_height(screen_height), v_height(viewport_height), f_len(focal_length),
            ambient(ambient), max_depth(max_depth), mi_world(mi_world)
    {};
public:
    int s_width, s_height, v_height, max_depth;
    double ambient, mi_world, f_len;
};

class ObjectProperties
{
public:
    ObjectProperties() = default;

    ObjectProperties(double diffuse, double specular, double shine, double reflective, double refraction, double mi)
            : diffuse(diffuse), specular(specular), shine(shine), reflective(reflective), refraction(refraction), mi(mi)
    {};
public:
    double diffuse, specular, shine, reflective, refraction, mi;
};

class LightProperties
{

};

#endif
