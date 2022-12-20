#ifndef CG_COURSE_TEXTURES_H
#define CG_COURSE_TEXTURES_H

#include <string>
#include <QImage>

#include "Vec.h"

class TextureData
{
public:
    TextureData() = default;

    TextureData(double width, double height, bool need_interpolation)
            : width(width), height(height), need_interpolation(need_interpolation)
    {};

    double width, height;
    bool need_interpolation = false;
};

class BaseTexture
{
public:
    virtual ~BaseTexture() = default;

    virtual void setData(const std::string &path) = 0;

    virtual Color pixelColor(int x, int y) = 0;

    virtual TextureData getData() = 0;
};

class QImageTexture : public BaseTexture
{
public:
    QImageTexture() = default;

    QImageTexture(const std::string &path);

    virtual ~QImageTexture() override = default;

    virtual void setData(const std::string &path) override;

    virtual Color pixelColor(int x, int y) override;

    virtual TextureData getData() override;

public:
    QImage img;
};

#endif
