#ifndef CUDA_CLASS_H
#define CUDA_CLASS_H


class PixelSumCuda
{
public:
    PixelSumCuda (const unsigned char* buffer, int xWidth, int yHeight);    
    PixelSumCuda(const PixelSumCuda&);
    PixelSumCuda& operator=(const PixelSumCuda&);
    ~PixelSumCuda();
    unsigned int getPixelSum(int x0, int y0, int x1, int y1) const;
    double getPixelAverage(int x0, int y0, int x1, int y1) const;
    int getNonZeroCount(int x0, int y0, int x1, int y1) const;
    double getNonZeroAverage(int x0, int y0, int x1, int y1) const;    
private:
    unsigned char* imageData;
    int width;
    int height;
};


PixelSumCuda::PixelSumCuda (unsigned char* buffer, int xWidth, int yHeight)
{ 
    cudaMalloc((void**)&imageData, xWidth*yHeight*sizeof(unsigned char));
    cudaMalloc((void**)&height, sizeof(int));
    cudaMalloc((void**)&width, sizeof(int));

    cudaMemcpy(height, &yHeight, sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(width, &xWidth, sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(imageData, buffer, width*height*sizeof(unsigned char), cudaMemcpyHostToDevice);
}

PixelSumCuda::PixelSumCuda(const PixelSumCuda &obj)
{   
    cudaMalloc((void**)imageData, obj.height*obj.width*sizeof(unsigned char));
    cudaMalloc((void**)&height, sizeof(int));
    cudaMalloc((void**)&width, sizeof(int));
    height = obj.height();
    width = obj.width();
    
    cudaMemcpy(imageData, obj.imageData, obj.height*obj.width*sizeof(unsigned char), cudaMemcpyHostToDevice);
    cudaMemcpy(height, &obj.height, sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(width, &obj.width, sizeof(int), cudaMemcpyHostToDevice);
}

PixelSum& PixelSum::operator=(const PixelSum& obj)
{
    cudaMalloc((void**)&imageData , sizeof(obj.height*obj.width*sizeof(unsigned char)); 
    cudaMalloc((void**)&height, sizeof(int));
    cudaMalloc((void**)&width, sizeof(int));

    const int img_height = obj.height;
    const int img_width = obj.width;
    cudaMemcpy(imageData, obj.imageData, img_height*img_width*sizeof(unsigned char), cudaMemcpyHostToDevice);
    cudaMemcpy(height, &img_height, sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(width, &img_width, sizeof(int), cudaMemcpyHostToDevice);
   
    return *this;
}


PixelSumCuda::~PixelSumCuda()
{
    cudaFree(height);
    cudaFree(width);
    cudaFree(imageData);
}


#endif //CUDA_CLASS_H