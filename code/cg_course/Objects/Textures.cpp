#include "Textures.h"

QImageTexture::QImageTexture(const string &path)
{
    img = QImage(path.c_str());
}

void QImageTexture::setData(const string &path)
{
    img = QImage(path.c_str());
}

Color QImageTexture::pixelColor(int x, int y)
{
    QColor clr = img.pixelColor(x, y);
    return clr;
}

TextureData QImageTexture::getData()
{
    return {double(img.width()), double(img.height()), true};
}
