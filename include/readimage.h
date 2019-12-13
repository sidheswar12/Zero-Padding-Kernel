
# ifndef READ_IMAGE_H
# define READ_IMAGE_H

#include <iostream>
#include <string>
#include <cstring>

class ReadImage
{
public:
    int height;
    int width;
    int bpp;
    unsigned char* rdata;
    unsigned char* gdata;
    unsigned char* bdata;
    ReadImage(std::string fname);
    ReadImage(const ReadImage&);
    ReadImage& operator=(const ReadImage&);
    ~ReadImage();
    int readBMPImage(void);    
private:
    std::string filename;
};

#endif //READ_IMAGE_H