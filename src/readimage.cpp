#include <math.h>
#include "../include/readimage.h"


ReadImage::ReadImage(std::string fname)
{
    filename = fname;
    height = 0;
    width = 0;
    bpp = 0;    
    rdata = nullptr;
    gdata = nullptr;
    bdata = nullptr;
    readBMPImage();  
}

ReadImage::ReadImage(const ReadImage& obj)
{
    rdata = (unsigned char*)malloc(obj.height*obj.width*sizeof(unsigned char));
    gdata = (unsigned char*)malloc(obj.height*obj.width*sizeof(unsigned char));
    bdata = (unsigned char*)malloc(obj.height*obj.width*sizeof(unsigned char));
    memcpy(rdata, obj.rdata, obj.height*obj.width);
    memcpy(gdata, obj.rdata, obj.height*obj.width);
    memcpy(bdata, obj.rdata, obj.height*obj.width);
    memcpy((void**)& height, (void**)& obj.height, sizeof(int));
    memcpy((void**)& width, (void**)& obj.width, sizeof(int));
    memcpy((void**)& bpp, (void**)& obj.bpp, sizeof(int));
}

ReadImage& ReadImage::operator=(const ReadImage& obj)
{
    rdata = (unsigned char*)malloc(obj.height*obj.width*sizeof(unsigned char));
    gdata = (unsigned char*)malloc(obj.height*obj.width*sizeof(unsigned char));
    bdata = (unsigned char*)malloc(obj.height*obj.width*sizeof(unsigned char));  
    const int img_height = obj.height;
    const int img_width = obj.width;
    const int img_bpp = obj.bpp;
    memcpy(rdata, obj.rdata, img_height*img_width);
    memcpy(gdata, obj.rdata, img_height*img_width);
    memcpy(bdata, obj.rdata, img_height*img_width);
    return *this;
}

ReadImage::~ReadImage()
{
    free(rdata);
    free(gdata);
    free(bdata);
}
int ReadImage::readBMPImage(void)
{
	FILE *In;
	int i, j, spaces;
    int File_and_DIB_Header[54];
	In=fopen(filename.c_str(), "rb");
    if(In==NULL)
    {
	    return -1;
    }
	fseek(In,0,SEEK_SET);
    if ((i=(int)getc(In))!=66 || (i=(int)getc(In))!=77)  
    { 	
        exit(0); 
    }
	fseek(In,0,SEEK_SET);
    for (i=0;i<=53;i++)                     
    {   
        File_and_DIB_Header[i]=(int)getc(In);
    }
    for (i=0;i<=3;i++)
    {   
        width = width  + (int)(pow(256,i)*(double)File_and_DIB_Header[18+i]); 
    }  
    for (i=0;i<=3;i++)
    {   
        height = height + (int)(pow(256,i)*(double)File_and_DIB_Header[22+i]);
    }
    bpp = (unsigned int)File_and_DIB_Header[28];
    bpp = bpp + 256* (unsigned int)File_and_DIB_Header[29];
  
    if (bpp==24) 
    {		
        bdata = (unsigned char*)malloc(height*width*sizeof(unsigned char));
        gdata = (unsigned char*)malloc(height*width*sizeof(unsigned char));
        rdata = (unsigned char*)malloc(height*width*sizeof(unsigned char));

        spaces = (width * 3)%4;
		if(spaces != 0)
		{
			spaces = 4 - spaces;	
		}		
        fseek(In, 54, SEEK_SET);
        for(i=0;i<=height-1;i++)
        {
            for(j=0;j<=width-1;j++)
            {
                *(bdata + i * width + j)=(unsigned char)getc(In);
                *(gdata + i * width + j)=(unsigned char)getc(In);
                *(rdata + i * width + j)=(unsigned char)getc(In);
            }
            fseek(In, spaces, SEEK_CUR);
        }
    } 

    if (bpp==16) 
    {		
        gdata = (unsigned char*)malloc(height*width*sizeof(unsigned char));
        rdata = (unsigned char*)malloc(height*width*sizeof(unsigned char));

        spaces = (width * 2)%4;
		if(spaces != 0)
		{
			spaces = 4 - spaces;	
		}		
        fseek(In, 54, SEEK_SET);
        for(i=0;i<=height-1;i++)
        {
            for(j=0;j<=width-1;j++)
            {
                *(gdata + i * width + j)=(unsigned char)getc(In);
                *(rdata + i * width + j)=(unsigned char)getc(In);
            }
            fseek(In, spaces, SEEK_CUR);
        }
    } 
  
    if (bpp==8) 
    {
        rdata = (unsigned char*)malloc(height*width*sizeof(unsigned char));
        spaces = (width)%4;
		if(spaces != 0)
		{
			spaces = 4 - spaces;	
		}
        fseek(In,11,SEEK_SET);
        fseek(In, 53+(getc(In)*(int)pow(2,bpp)),SEEK_SET);
        for(i=0;i<=height-1;i++)
        {
            for(j=0;j<=width-1;j++)
            {
                *(rdata + i * width + j)=(unsigned char)getc(In);
            }
            fseek(In, spaces, SEEK_CUR);
        }
    }   
    fclose(In);
    return 1;
}
