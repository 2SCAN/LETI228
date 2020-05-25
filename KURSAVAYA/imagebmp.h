#ifndef IMAGEBMP_H
#define IMAGEBMP_H

#include <cstdio>
#include <cstdlib>
#include <QColor>
#include "mygraphicsview.h"

#pragma pack (push, 1)
typedef struct
{
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixelArrOffset;
} BitmapFileHeader;

typedef struct
{
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    unsigned int xPixelsPerMeter;
    unsigned int yPixelsPerMeter;
    unsigned int colorsInColorTable;
    unsigned int importantColorCount;
} BitmapInfoHeader;

typedef struct
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
} Rgb;

typedef struct
{
    int x;
    int y;
    int square;
} Sq;

#pragma pack(pop)

class ImageBmp
{
public:
    ImageBmp();
    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;
    int H;
    int W;
    Rgb** image;
    Rgb** collage_;
    QPixmap getPixmap();
    int loadImage(const char *file);

    int saveImage(const char *file);

    void draw_line(int y1, int x1, int y2, int x2, QColor color);

    void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int thik, QColor color);
    int draw_flood_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int thik, QColor floodcolor, QColor edgecolor);

    void drawLineSize(int x1, int y1, int x2, int y2, int size, QColor color);

    void deleteImage();

    void collage(int n, int m);

    int recolor_rectangle(QColor my_color, QColor new_color);

    bool isColor(int x, int y, QColor color);

};

#endif // IMAGEBMP_H
