
# ifndef PIXEL_SUM_H
# define PIXEL_SUM_H

#include <iostream>
#include <cstring>

class PixelSum
{
public:
    PixelSum (const unsigned char* buffer, int xWidth, int yHeight);    
    PixelSum(const PixelSum&);
    PixelSum& operator=(const PixelSum&);
    ~PixelSum();
    unsigned int getPixelSum(int x0, int y0, int x1, int y1) const;
    double getPixelAverage(int x0, int y0, int x1, int y1) const;
    int getNonZeroCount(int x0, int y0, int x1, int y1) const;
    double getNonZeroAverage(int x0, int y0, int x1, int y1) const;
private:
    unsigned char* imageData;
    int width;
    int height;
};

#endif //PIXEL_SUM_H