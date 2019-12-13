#include "../include/pixelsum.h"

PixelSum::PixelSum (const unsigned char* buffer, int xWidth, int yHeight)
{
    imageData = (unsigned char*)malloc(yHeight*xWidth*sizeof(unsigned char)); 
    memcpy(imageData, buffer, xWidth*yHeight*sizeof(unsigned char));    
    memcpy((void**)& height, (void**)& yHeight, sizeof(int));
    memcpy((void**)& width, (void**)& xWidth, sizeof(int));
}

PixelSum::PixelSum(const PixelSum &obj)
{   
    imageData = (unsigned char*)malloc(obj.height*obj.width*sizeof(unsigned char));
    memcpy(imageData, obj.imageData, obj.height*obj.width*sizeof(unsigned char));
    memcpy((void**)& height, (void**)& obj.height, sizeof(int));
    memcpy((void**)& width, (void**)& obj.width, sizeof(int));
}

PixelSum& PixelSum::operator=(const PixelSum& obj)
{
    imageData = (unsigned char*)malloc(obj.height*obj.width*sizeof(unsigned char));  
    const int img_height = obj.height;
    const int img_width = obj.width;
    memcpy(imageData, obj.imageData, img_height*img_width*sizeof(unsigned char));
    return *this;
}

PixelSum::~PixelSum()
{
    free(imageData);
}

unsigned int PixelSum::getPixelSum(int x0, int y0, int x1, int y1)const
{
    unsigned int pixelSum=0;  
    if(x0 > x1)
        std::swap(x0, x1);
    if(y0 > y1)
        std::swap(y0, y1);
    for (int l=y0;l<=y1;l++)
    {   
        if(l<0||l>height-1)
            continue;        
        for (int r=x0;r<=x1;r++)
        {
            if(r<0||r>width-1)
                continue;
            pixelSum = pixelSum + (int)*(imageData+l*width+r);                      
        }
    }
    return pixelSum;
}

double PixelSum::getPixelAverage(int x0, int y0, int x1, int y1)const
{
    double pixelAvg = 0.0;
    int pixelCount = 0;
    unsigned int pixelSum = 0;
    if(x0 > x1)
        std::swap(x0, x1);
    if(y0 > y1)
        std::swap(y0, y1);
    int i = 0;
    int j = 0;
    for (int l=y0;l<=y1;l++)
    {   
        i++;
        if(l<0||l>height-1)       
            continue;
        j = 0;
        for (int r=x0;r<=x1;r++)
        {
            j++;
            if(r<0||r>width-1)
                continue;
            pixelSum = pixelSum + (int)*(imageData+l*width+r);                      
        }
    }
    pixelCount = i*j;
    if(pixelCount!=0)
        pixelAvg = (double)pixelSum/pixelCount;
    return pixelAvg;
}

int PixelSum::getNonZeroCount(int x0, int y0, int x1, int y1)const
{
    int nonzeroPixcelCount = 0;
    if(x0 > x1)
        std::swap(x0, x1);
    if(y0 > y1)
        std::swap(y0, y1);
    for (int l=y0;l<=y1;l++)
    {   
        if(l<0||l>height-1)
            continue;
        for (int r=x0;r<=x1;r++)
        {
            if(r<0||r>width-1)
                continue;
            if(*(imageData+l*width+r)>0)					
                nonzeroPixcelCount += 1;            
        }
    }
    return nonzeroPixcelCount;
}

double PixelSum::getNonZeroAverage(int x0, int y0, int x1, int y1)const
{
    double nonZeroPixelAvg = 0.0;
    unsigned int pixelSum = 0;
    int nonzeroPixcelCount = 0;
    if(x0 > x1)
        std::swap(x0, x1);
    if(y0 > y1)
        std::swap(y0, y1);
    for (int l=y0;l<=y1;l++)
    {   
        if(l<0||l>height-1)
            continue;
        for (int r=x0;r<=x1;r++)
        {
            if(r<0||r>width-1)
                continue;
            if(*(imageData+l*width+r)>0)
            {				
                nonzeroPixcelCount += 1;
                pixelSum = pixelSum + (int)*(imageData+l*width+r);
            }         
        }
    }
    if(nonzeroPixcelCount!=0)
        nonZeroPixelAvg = (double)pixelSum/nonzeroPixcelCount;
        
    return nonZeroPixelAvg;
}
