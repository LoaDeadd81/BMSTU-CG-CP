#ifndef CG_COURSE_PROPERIES_H
#define CG_COURSE_PROPERIES_H

class CameraProperties
{
public:
    CameraProperties() = default;

    CameraProperties(int screen_width, int screen_height, int viewport_height, int focal_length) :
            s_width(screen_width), s_height(screen_height), v_height(viewport_height), f_len(focal_length)
    {};
public:
    int s_width, s_height, v_height, f_len;
};

class ObjectProperties
{

};

class LightProperties
{

};

#endif
