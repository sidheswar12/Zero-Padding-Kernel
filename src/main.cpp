#include <thread>
#include <future>

#include "../include/pixelsum.h"
#include "../include/readimage.h"


int main( int argc, char** argv )
{
    if( argc != 6)
    {
     std::cout <<" Usage: Please provide all below arguments..." << std::endl;
     std::cout << "Image Name with full path" << std::endl;
     std::cout << "X0 Position (int)" << std::endl;
     std::cout << "Y0 Position (int)" << std::endl;
     std::cout << "X1 Position (int)" << std::endl;
     std::cout << "Y1 Position (int)" << std::endl;
     return -1;
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
    
    ReadImage *read = new ReadImage(argv[1]);   
    PixelSum *obj = new PixelSum(read->rdata, read->width, read->height);
    int x0 = atoi(argv[2]);
    int y0 = atoi(argv[3]);
    int x1 = atoi(argv[4]);
    int y1 = atoi(argv[5]);

    auto sum = std::async(std::launch::deferred, &PixelSum::getPixelSum, obj, x0, y0, x1, y1);
    auto avg = std::async(std::launch::deferred, &PixelSum::getPixelAverage, obj, x0, y0, x1, y1);
    auto nonZeroCount = std::async(std::launch::deferred, &PixelSum::getNonZeroCount, obj, x0, y0, x1, y1);
    auto nonZeroAvg = std::async(std::launch::deferred, &PixelSum::getNonZeroAverage, obj, x0, y0, x1, y1);

    unsigned int pixelSum = sum.get();
    double pixelAvg = avg.get();
    int nonzeroPixelCount = nonZeroCount.get();
    double nonzeroPixelAvg = nonZeroAvg.get();

    std::cout<<"PixelSum: "<<pixelSum<<std::endl;
    std::cout<<"PixelAvg: "<<pixelAvg<<std::endl;
    std::cout<<"NonzeroPixelCount: "<<nonzeroPixelCount<<std::endl;
    std::cout<<"NonzeroPixelAvg: "<<nonzeroPixelAvg<<std::endl;
    std::cout<<"Successfully Completed"<<std::endl;
    delete obj;
    delete read;    
    return 0;
}
