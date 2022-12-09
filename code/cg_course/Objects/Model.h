#ifndef CG_COURSE_MODEL_H
#define CG_COURSE_MODEL_H

#include "Matrix.h"
#include "GeometryPrimitives.h"
#include "Properies.h"

#define ACC_EPS 1e-4

class IntersectionData;

class BaseModel
{
public:
    using ModelIter = std::vector<shared_ptr<BaseModel>>::iterator;

    virtual ~BaseModel() = default;

    virtual void transform(const Matix4x3d &transform_matrix) = 0;

    virtual bool intersect(const Ray &ray, IntersectionData &data) = 0;

    virtual void setTexture(const string &path) = 0;

    virtual void setColor(const Color &&clr) = 0;

    virtual ObjectProperties &props() = 0;
};

class Sphere : public BaseModel
{
public:
    Sphere() = default;

    Sphere(Point3d center, double r);

    Sphere(Point3d center, double r, Color color, ObjectProperties props);

    virtual ~Sphere() = default;

    virtual void transform(const Matix4x3d &transform_matrix) override;

    virtual bool intersect(const Ray &ray, IntersectionData &data) override;

    bool is_intersect(const Ray &ray);

    virtual void setTexture(const string &path) override;

    virtual void setColor(const Color &&clr) override;

    virtual ObjectProperties &props() override;

private:
    Point3d center;
    double radius;
    Color color;
    ObjectProperties properties;
};

class Plane : public BaseModel
{
public:
    Plane() = default;

    Plane(Vec3d normal, double d, Color color, ObjectProperties props);

    virtual ~Plane() = default;

    virtual void transform(const Matix4x3d &transform_matrix) override;

    virtual bool intersect(const Ray &ray, IntersectionData &data) override;

    virtual void setTexture(const string &path) override;

    virtual void setColor(const Color &&clr) override;

    virtual ObjectProperties &props() override;

private:
    double a, b, c, d;
    Vec3d normal;
    Point3d point;
    Color color;
    ObjectProperties properties;
};

class PolygonalBoundedModel : public BaseModel
{
public:
    PolygonalBoundedModel() = default;

    PolygonalBoundedModel(const objl::Mesh &mesh, Color color, ObjectProperties props);

    virtual ~PolygonalBoundedModel() = default;

    virtual void transform(const Matix4x3d &transform_matrix) override;

    virtual bool intersect(const Ray &ray, IntersectionData &data) override;

    virtual void setTexture(const string &path) override;

    virtual void setColor(const Color &&clr) override;

    virtual ObjectProperties &props() override;

private:
    vector<Polygon> polygons;
    Sphere bounding_sphere;

    Color color;
    ObjectProperties properties;
};

class IntersectionData
{
public:
    IntersectionData() = default;
    //todo add fields and constructors
public:
    Point3d p;
    double t;
    Vec3d n;
    Color color;
    BaseModel::ModelIter iter;
};


#endif
