#include "imagebmp.h"

ImageBmp::ImageBmp()
{

}
int ImageBmp::loadImage(const char *file) {
    FILE *f = fopen(file, "rb");
    if (!f){
        return -3;
    }
    fread(&bmfh, sizeof(BitmapFileHeader), 1, f);
    fread(&bmih, sizeof(BitmapInfoHeader), 1, f);
    H = bmih.height;
    W = bmih.width;
    if (W == 0 || H == 0) {
        printf("Eror\n Unable to open blank image");
        return-2;
    }

    if (H > 10000 || W > 10000)
        return -2;
    size_t padding = 0;
    if ((W * 3) % 4)
        padding = 4 - (W * 3) % 4;
    image = new Rgb *[H];
    for (int i = 0; i < H; i++) {
        image[i] = new Rgb[W + 1];
    }
    fseek(f, long(bmfh.pixelArrOffset), SEEK_SET);
    for (int i = 0; i < H; i++) {
        int j;
        for (j = 0; j < W; j++) {
            fread(&image[i][j], sizeof(Rgb), 1, f);
        }
        if (padding)
            fread(&image[i][j], padding, 1, f);
    }
    fclose(f);
    return 0;
}



int ImageBmp::saveImage(const char *file) {

   FILE *f = fopen(file, "wb");
   if (!f){
       return -1;
   }
   fwrite(&bmfh, sizeof(bmfh), 1, f);
   fwrite(&bmih, sizeof(bmih), 1, f);
   if (W == 0 || H == 0) {
       return-2;
   }

   size_t padding = 0;
   if ((bmih.width * 3) % 4)
       padding = 4 - (bmih.width * 3) % 4;
   fseek(f, long(bmfh.pixelArrOffset), SEEK_SET);
   for (int i = 0; i < bmih.height; i++) {
       int j;
       for (j = 0; j < bmih.width; j++) {
           fwrite(&image[i][j], sizeof(Rgb), 1, f);
       }
       if (padding)
           fwrite(&image[i][j], padding, 1, f);
   }
   fclose(f);
   return 0;
}

QPixmap ImageBmp::getPixmap(){
    QImage *img = new QImage(bmih.width, bmih.height, QImage::Format_RGB16);
    QColor pixel;
    for(int i = 0; i < (int)bmih.height; i++){
        for(int j = 0; j < (int)bmih.width; j++){
            pixel.setRed(image[i][j].r);
            pixel.setGreen(image[i][j].g);
            pixel.setBlue(image[i][j].b);
            img->setPixel(j, bmih.height - i -1, pixel.rgb());
        }
    }
    return QPixmap::fromImage(*img);
}

void ImageBmp::draw_line(int x1, int y1, int x2, int y2, QColor color){
    int deltaX = abs(x2 - x1);
    int deltaY = abs(y2 - y1);
    int signX = x1 < x2 ? 1 : -1;
    int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    image[x2][y2].r = (unsigned char)color.red();
    image[x2][y2].g = (unsigned char)color.green();
    image[x2][y2].b = (unsigned char)color.blue();
    while(x1 != x2 || y1 != y2){
        image[x1][y1].r = (unsigned char)color.red();
        image[x1][y1].g = (unsigned char)color.green();
        image[x1][y1].b = (unsigned char)color.blue();
        int error2 = error * 2;
        if (error2 > -deltaY){
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX){
            error += deltaX;
            y1 += signY;
        }
    }
}

/*void ImageBmp::triangle(int y1, int x1, int y2, int x2, int x3, int y3, int width, bool Fill, QColor color, QColor FillColor)
{
    if(Fill){
        int xmin = std::min(x3, std::min(x1, x2));
        int xmax = std::max(x3, std::max(x1, x2));
        int ymin = std::min(y3, std::min(y1, y2));
        int ymax = std::max(y3, std::max(y1, y2));
        for(int i = ymin; i <= ymax; i++){
            for(int j = xmin; j <= xmax; j++){
                float a = (x1 - j) * (y2 - y1) - (x2 - x1) * (y1 - i);
                float b = (x2 - j) * (y3 - y2) - (x3 - x2) * (y2 - i);
                float c = (x3 - j) * (y1 - y3) - (x1 - x3) * (y3 - i);
                if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0)){
                    image[i][j].r = (unsigned char)FillColor.red();
                    image[i][j].g = (unsigned char)FillColor.green();
                    image[i][j].b = (unsigned char)FillColor.blue();
                }
            }
        }
    }

    drawLineSize(x1, y1, x2, y2, width, color);
    drawLineSize(x1, y1, x3, y3, width, color);
    drawLineSize(x2, y2, x3, y3, width, color);
}*/
void ImageBmp::draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int thik, QColor color){
    ImageBmp::drawLineSize(x1, y1, x2, y2, thik, color);
    ImageBmp::drawLineSize(x2, y2, x3, y3, thik, color);
    ImageBmp::drawLineSize(x1,y1,x3,y3,thik,color);
}

void ImageBmp::drawLineSize(int x1, int y1, int x2, int y2, int size, QColor color){
    if (abs(y2-y1) > abs(x2-x1)){
        if (x1-size/2 < 0 || x2-size/2 < 0 || x1+size/2 >= bmih.width || x2+size/2 >= bmih.width)
        x1 = x1 -size/2;
        x2 = x2-size/2;
        for (int i = 0; i < size; i++)
            draw_line(x1+i, y1, x2+i, y2, color);
    }else{
        if (y1-size/2 < 0 || y2-size/2 < 0 || y1+size/2 >= bmih.height || y2+size/2 >= bmih.height)
        y1 = y1 -size/2;
        y2 = y2-size/2;
        for (int i = 0; i < size; i++)
            draw_line(x1, y1+i, x2, y2+i, color);
    }
}

void ImageBmp::deleteImage()
{
    for(int i = 0; i < H; i++){
        delete[] image[i];
    }
    delete[] image;
}

void ImageBmp::collage(int n, int m)
{
    int cHeight = n * H;
    int cWidth = m * W;

    collage_ = new Rgb *[cHeight];
    for(int i = 0; i < cHeight; i++){
        collage_[i] = new Rgb[cWidth + 1];
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            for(int y = 0; y < H; y++){
                for(int x = 0; x < W; x++){
                    collage_[i*H + y][j*W + x] = image[y][x];
                }
            }
        }
    }
    deleteImage();
    image = collage_;
    bmih.height = cHeight;
    bmih.width = cWidth;
    H = cHeight;
    W = cWidth;
}
int ImageBmp::recolor_rectangle(QColor my_color, QColor new_color)
{
    int x=0, y=0, z, y1, x1, max_size = -1, flag=1;
    int mx = 0, my = 0, nx = 0, ny = 0;
    for (y = 0; y < H; y++){
        for (x = 0; x < W; x++){
            if (isColor(x, y, my_color)){
                flag = 0;
                if ((H - y) * (W - x) > max_size){
                    for (z = x; z < W; z++){
                        if (isColor(z, y, my_color) == 0){
                            break;
                        }
                    }
                    z -= (x+1);
                    if(z > 0){
                        for (y1 = y+1; y1 < H; y1++){
                            if(max_size < (y1-y) * z){
                                max_size = (y1-y) * z;
                                mx = x; my = y; nx = x + z; ny = y1;
                            }
                            if (z <=0){
                                break;
                            }
                            for (x1 = x; (x1 < W) && (x1 < x + z);x1++){
                                if (isColor(x1, y1, my_color) == 0 ){
                                    z = x1 - x - 1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(flag || max_size == -1){
        return -1;
    }else{
        for (int y = 0; y < H; y++){
            for (int x = 0; x < W; x++){
                if(x > mx && x < nx && y > my && y < ny){
                    if(x > 0 && y > 0 && x < W, y < H){
                        image[y][x].r = (unsigned char)new_color.red();
                        image[y][x].g = (unsigned char)new_color.green();
                        image[y][x].b = (unsigned char)new_color.blue();
                    }
                }
            }
        }
    }
    return 0;
}

bool ImageBmp::isColor(int x, int y, QColor color)
{
    Rgb pointColor;
    pointColor.r = 0;
    pointColor.g = 0;
    pointColor.b = 0;
    if(x>0 && y > 0 && x < W, y < H){
        pointColor.r = image[y][x].r;
        pointColor.g = image[y][x].g;
        pointColor.b = image[y][x].b;
        return (pointColor.r == color.red() && pointColor.g == color.green() && pointColor.b == color.blue());
    }
    return false;
}
