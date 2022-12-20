#ifndef CG_COURSE_MODEL_H
#define CG_COURSE_MODEL_H

#include <list>

#include "Matrix.h"
#include "GeometryPrimitives.h"
#include "Properies.h"
#include "Transformation.h"

#define ACC_EPS 1e-4

class IntersectionData;


class BaseModel
{
public:
    using ModelIter = std::list<shared_ptr<BaseModel>>::iterator;

    virtual ~BaseModel() = default;

    virtual void move(double dx, double dy, double dz) = 0;

    virtual void rotate(double dx, double dy, double dz) = 0;

    virtual void scale(double dx, double dy, double dz) = 0;

    virtual bool intersect(const Ray &ray, IntersectionData &data) = 0;

    virtual void setTexture(shared_ptr<BaseTexture> &texture) = 0;

    virtual void setColor(const Color &clr) = 0;

    virtual ObjectProperties &props() = 0;

    virtual Color clr(int x = 0, int y = 0) = 0;

    virtual bool hasTecture() = 0;

    virtual shared_ptr<BaseTexture> &txtr() = 0;
};

class Sphere : public BaseModel
{
public:
    Sphere() = default;

    Sphere(Point3d center, double r);

    Sphere(Point3d center, double r, Color color, ObjectProperties props);

    virtual ~Sphere() = default;

    virtual void move(double dx, double dy, double dz) override;

    virtual void rotate(double dx, double dy, double dz) override;

    virtual void scale(double dx, double dy, double dz) override;

    virtual bool intersect(const Ray &ray, IntersectionData &data) override;

    bool is_intersect(const Ray &ray);

    virtual void setTexture(shared_ptr<BaseTexture> &texture) override;

    virtual void setColor(const Color &clr) override;

    virtual ObjectProperties &props() override;

    virtual Color clr(int x = 0, int y = 0) override;

    Point3d &cntr();

    virtual bool hasTecture() override;

    virtual shared_ptr<BaseTexture> &txtr() override;

private:
    Point3d center;
    double radius;
    Color color;
    ObjectProperties properties;
    shared_ptr<BaseTexture> texture;
    TextureData tdata;
};

class Plane : public BaseModel
{
public:
    Plane() = default;

    Plane(Vec3d normal, double d, Color color, ObjectProperties props);

    virtual ~Plane() = default;

    virtual void move(double dx, double dy, double dz) override;

    virtual void rotate(double dx, double dy, double dz) override;

    virtual void scale(double dx, double dy, double dz) override;

    virtual bool intersect(const Ray &ray, IntersectionData &data) override;

    virtual void setTexture(shared_ptr<BaseTexture> &texture) override;

    virtual void setColor(const Color &clr) override;

    virtual ObjectProperties &props() override;

    virtual Color clr(int x = 0, int y = 0) override;

    virtual bool hasTecture() override;

    virtual shared_ptr<BaseTexture> &txtr() override;

private:
    double d;
    Vec3d normal;
    Vec4d tnormal;
    Point3d point;
    Color color;
    ObjectProperties properties;
    shared_ptr<BaseTexture> texture;
    TextureData tdata;
};

class PolygonalBoundedModel : public BaseModel
{
public:
    PolygonalBoundedModel() = default;

    PolygonalBoundedModel(const objl::Mesh &mesh, Color color, ObjectProperties props);

    virtual ~PolygonalBoundedModel() = default;

    virtual void move(double dx, double dy, double dz) override;

    virtual void rotate(double dx, double dy, double dz) override;

    virtual void scale(double dx, double dy, double dz) override;

    virtual bool intersect(const Ray &ray, IntersectionData &data) override;

    virtual void setTexture(shared_ptr<BaseTexture> &texture) override;

    virtual void setColor(const Color &clr) override;

    virtual ObjectProperties &props() override;

    virtual Color clr(int x = 0, int y = 0) override;

    virtual bool hasTecture() override;

    virtual shared_ptr<BaseTexture> &txtr() override;

private:
    vector<Polygon> polygons;
    Sphere bounding_sphere;

    Color color;
    ObjectProperties properties;
    shared_ptr<BaseTexture> texture;
    TextureData tdata;
};

class IntersectionData
{
public:
    IntersectionData() = default;

    IntersectionData &operator=(IntersectionData &&other) noexcept;

public:
    Point3d p;
    double t;
    Vec3d n;
    Color color;
    BaseModel::ModelIter iter;
};


#endif
