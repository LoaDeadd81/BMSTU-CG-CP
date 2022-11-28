#ifndef CG_COURSE_MODEL_H
#define CG_COURSE_MODEL_H

#include "Matrix.h"
#include "GeometryPrimitives.h"

class BaseModel
{
public:
    virtual ~BaseModel() = default;

    virtual void transform(const Matix4x3d &transform_matrix) = 0;

    virtual bool intersect(const Ray &ray, IntersectionData &data) = 0;

    virtual void setTexture(const string &path) = 0;

    virtual void setColor(const Color &&clr) = 0;
//    virtual void set
};

class Sphere : public BaseModel
{
public:
    Sphere() = default;

    Sphere(Point3d center, double r, Color color = {255, 255, 255});

    virtual ~Sphere() = default;

    virtual void transform(const Matix4x3d &transform_matrix) override;

    virtual bool intersect(const Ray &ray, IntersectionData &data) override;

    virtual void setTexture(const string &path) override;

    virtual void setColor(const Color &&clr) override;

private:
    Point3d center;
    double radius;
    Color color;
};

#endif
