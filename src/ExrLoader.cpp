/*
 * ExrLoader.cpp
 *
 *  Created on: Sep 19, 2017
 *      Author: alban
 */

#include "ExrLoader.h"

#include <OpenEXR/ImfRgbaFile.h>
#include <OpenEXR/ImfArray.h>
#include <OpenEXR/ImfHeader.h>
#include <OpenEXR/ImfChromaticitiesAttribute.h>

#include <cmath>

double to_sRGB(double rgb_color) {
    const double a = 0.055;
    if (rgb_color < 0.0031308)
        return 12.92 * rgb_color;
    else
        return (1.0 + a) * std::pow(rgb_color, 1.0/2.4) - a;
}

unsigned char* load_exr(void* buffer, int size, const char *filename,
                 int *width, int *height) {
    MyStream stream(buffer, size, "test");
    Imf::Array2D<Imf::Rgba> pixels;

    Imf::RgbaInputFile f(stream);
    Imath::Box2i dw1 = f.dataWindow();
    int w = dw1.max.x - dw1.min.x + 1;
    int h = dw1.max.y - dw1.min.y + 1;
    *width = w;
    *height = h;

    pixels.resizeErase(h, w);
    f.setFrameBuffer(&pixels[0][0] - dw1.min.x - dw1.min.y * w, 1, w);
    f.readPixels(dw1.min.y, dw1.max.y);

    unsigned char* img = new unsigned char[3 * w * h];

    // Check if there is specific chromaticities tied to the color representation in this part.
    const Imf::ChromaticitiesAttribute *c
        = f.header().findTypedAttribute<Imf::ChromaticitiesAttribute>(
            "chromaticities");
            
    Imf::Chromaticities chromaticities;

    if (c != nullptr) {
        chromaticities = c->value();
    }

    // Handle custom chromaticities
    Imath::M44f RGB_XYZ = Imf::RGBtoXYZ(chromaticities, 1.f);
    Imath::M44f XYZ_RGB = Imf::XYZtoRGB(Imf::Chromaticities(), 1.f);

    Imath::M44f conversionMatrix = RGB_XYZ * XYZ_RGB;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            Imath::V3f rgb(pixels[y][x].r, pixels[y][x].g, pixels[y][x].b);
            rgb *= conversionMatrix;

            img[3*(y*w + x) + 0] = (unsigned char)(255.0*std::min(1.0, std::max(0.0, to_sRGB(rgb.x))));
            img[3*(y*w + x) + 1] = (unsigned char)(255.0*std::min(1.0, std::max(0.0, to_sRGB(rgb.y))));
            img[3*(y*w + x) + 2] = (unsigned char)(255.0*std::min(1.0, std::max(0.0, to_sRGB(rgb.z))));
        }
    }

    return img;
}
