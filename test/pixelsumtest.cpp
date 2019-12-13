
#include <gtest/gtest.h>

#include "../src/pixelsum.cpp"
#include "../src/readimage.cpp"


unsigned char* testData() 
{    
    unsigned char *dataBuffer; 
    int height = 2;
    int width = 2;    
    dataBuffer = (unsigned char*)calloc(height*width, sizeof(unsigned char)); 
    *(dataBuffer+(0*width)+0) = 1;
    *(dataBuffer+(0*width)+1) = 1;
    *(dataBuffer+(1*width)+0) = 2;
    *(dataBuffer+(1*width)+1) = 2;
    return dataBuffer;
}

unsigned char* testDataWithZero() 
{    
    unsigned char *dataBuffer; 
    int height = 2;
    int width = 2;    
    dataBuffer = (unsigned char*)calloc(height*width, sizeof(unsigned char)); 
    *(dataBuffer+(0*width)+0) = 1;
    *(dataBuffer+(0*width)+1) = 1;
    *(dataBuffer+(1*width)+0) = 0;
    *(dataBuffer+(1*width)+1) = 2;
    return dataBuffer;
}

TEST(PixelSumTest, PositiveNos) 
{     
    unsigned char *dataBuffer =testData();
    PixelSum *obj = new PixelSum(dataBuffer, 2, 2);
    ASSERT_EQ(1, obj->getPixelSum(0, 0, 0, 0));
    ASSERT_EQ(0, obj->getPixelSum(2, 2, 2, 2));
    ASSERT_EQ(6, obj->getPixelSum(0, 0, 1, 1));
    ASSERT_EQ(6, obj->getPixelSum(0, 0, 2, 2));
    ASSERT_EQ(2, obj->getPixelSum(1, 1, 2, 2));
    ASSERT_EQ(0, obj->getPixelSum(2, 2, 4, 4));
    ASSERT_EQ(6, obj->getPixelSum(1, 1, 0, 0));
    ASSERT_EQ(6, obj->getPixelSum(2, 2, 0, 0));
    ASSERT_EQ(2, obj->getPixelSum(2, 2, 1, 1));    
    ASSERT_EQ(0, obj->getPixelSum(1, 2, 1, 2));
    ASSERT_EQ(3, obj->getPixelSum(2, 0, 1, 1));
    ASSERT_EQ(4, obj->getPixelSum(2, 2, 0, 1));
    ASSERT_EQ(4, obj->getPixelSum(0, 2, 1, 1));
    ASSERT_EQ(0, obj->getPixelSum(2, 2, 2, 1));
    ASSERT_EQ(3, obj->getPixelSum(2, 0, 1, 1));
    ASSERT_EQ(3, obj->getPixelSum(2, 2, 1, 0));
    free(dataBuffer);
}

TEST(PixelSumTest1, NegativeNos) 
{     
    unsigned char *dataBuffer =testData();
    PixelSum *obj = new PixelSum(dataBuffer, 2, 2);   
    ASSERT_EQ(0, obj->getPixelSum(-1, -1, -1, -1));
    ASSERT_EQ(0, obj->getPixelSum(-2, -2, -2, -2));
    ASSERT_EQ(1, obj->getPixelSum(0, 0, -1, -1));
    ASSERT_EQ(1, obj->getPixelSum(0, 0, -2, -2));
    ASSERT_EQ(6, obj->getPixelSum(-1, -1, 2, 2));
    ASSERT_EQ(0, obj->getPixelSum(-2, -2, 4, -4));
    ASSERT_EQ(1, obj->getPixelSum(-1, -1, 0, 0));
    ASSERT_EQ(2, obj->getPixelSum(2, -2, 0, 0));
    ASSERT_EQ(4, obj->getPixelSum(-2, 2, 1, 1));    
    ASSERT_EQ(0, obj->getPixelSum(1, 2, -1, 2));
    ASSERT_EQ(2, obj->getPixelSum(-2, 0, 1, -1));
    ASSERT_EQ(3, obj->getPixelSum(-2, -2, 0, 1));
    ASSERT_EQ(0, obj->getPixelSum(0, -2, 1, -1));
    ASSERT_EQ(0, obj->getPixelSum(-2, -2, -2, 1));
    ASSERT_EQ(2, obj->getPixelSum(2, 0, -1, -1));
    ASSERT_EQ(6, obj->getPixelSum(2, 2, -1, 0));
    free(dataBuffer);
}

TEST(getPixelAverageTest, PositiveNos) 
{     
    unsigned char *dataBuffer =testData();
    PixelSum *obj = new PixelSum(dataBuffer, 2, 2);
    EXPECT_DOUBLE_EQ(1.0, obj->getPixelAverage(0, 0, 0, 0));
    EXPECT_DOUBLE_EQ(0.0, obj->getPixelAverage(2, 2, 2, 2));
    EXPECT_DOUBLE_EQ(1.5, obj->getPixelAverage(0, 0, 1, 1));
    ASSERT_FLOAT_EQ(0.6666667, obj->getPixelAverage(0, 0, 2, 2));
    EXPECT_DOUBLE_EQ(0.5, obj->getPixelAverage(1, 1, 2, 2));
    EXPECT_DOUBLE_EQ(0.0, obj->getPixelAverage(2, 2, 4, 4));
    EXPECT_DOUBLE_EQ(1.5, obj->getPixelAverage(1, 1, 0, 0));
    ASSERT_FLOAT_EQ(0.6666669, obj->getPixelAverage(2, 2, 0, 0));
    EXPECT_DOUBLE_EQ(0.5, obj->getPixelAverage(2, 2, 1, 1));    
    EXPECT_DOUBLE_EQ(0.0, obj->getPixelAverage(1, 2, 1, 2));
    EXPECT_DOUBLE_EQ(0.75, obj->getPixelAverage(2, 0, 1, 1));
    ASSERT_FLOAT_EQ(0.6666667, obj->getPixelAverage(2, 2, 0, 1));
    ASSERT_FLOAT_EQ(0.0, obj->getPixelAverage(2, 2, 2, 1));
    ASSERT_FLOAT_EQ(0.5, obj->getPixelAverage(2, 2, 1, 0));
    free(dataBuffer);
}

TEST(getPixelAverageTest1, NegativeNos) 
{     
    unsigned char *dataBuffer =testData();
    PixelSum *obj = new PixelSum(dataBuffer, 2, 2);   
    ASSERT_EQ(0.0, obj->getPixelAverage(-1, -1, -1, -1));
    ASSERT_EQ(0.0, obj->getPixelAverage(-2, -2, -2, -2));
    ASSERT_EQ(0.25, obj->getPixelAverage(0, 0, -1, -1));
    ASSERT_EQ(0.375, obj->getPixelAverage(-1, -1, 2, 2));
    ASSERT_EQ(0, obj->getPixelAverage(-2, -2, 4, -4));
    ASSERT_EQ(0.25, obj->getPixelAverage(-1, -1, 0, 0));
    ASSERT_EQ(0.5, obj->getPixelAverage(-2, 2, 1, 1));    
    ASSERT_EQ(0.0, obj->getPixelAverage(1, 2, -1, 2));
    ASSERT_EQ(0.25, obj->getPixelAverage(-2, 0, 1, -1));
    ASSERT_EQ(0.25, obj->getPixelAverage(-2, -2, 0, 1));
    ASSERT_EQ(0.0, obj->getPixelAverage(0, -2, 1, -1));
    ASSERT_EQ(0.0, obj->getPixelAverage(-2, -2, -2, 1));
    ASSERT_EQ(0.25, obj->getPixelAverage(2, 0, -1, -1));
    ASSERT_EQ(0.5, obj->getPixelAverage(2, 2, -1, 0));
    free(dataBuffer);
}

TEST(getNonZeroCountTest, PositiveNos) 
{     
    unsigned char *dataBuffer =testDataWithZero();
    PixelSum *obj = new PixelSum(dataBuffer, 2, 2);
    ASSERT_EQ(1, obj->getNonZeroCount(0, 0, 0, 0));
    ASSERT_EQ(0, obj->getNonZeroCount(2, 2, 2, 2));
    ASSERT_EQ(3, obj->getNonZeroCount(0, 0, 1, 1));
    ASSERT_EQ(3, obj->getNonZeroCount(0, 0, 2, 2));
    ASSERT_EQ(1, obj->getNonZeroCount(1, 1, 2, 2));
    ASSERT_EQ(0, obj->getNonZeroCount(2, 2, 4, 4));
    ASSERT_EQ(3, obj->getNonZeroCount(1, 1, 0, 0));
    ASSERT_EQ(3, obj->getNonZeroCount(2, 2, 0, 0));
    ASSERT_EQ(1, obj->getNonZeroCount(2, 2, 1, 1));    
    ASSERT_EQ(0, obj->getNonZeroCount(1, 2, 1, 2));
    ASSERT_EQ(2, obj->getNonZeroCount(2, 0, 1, 1));
    ASSERT_EQ(1, obj->getNonZeroCount(2, 2, 0, 1));
    ASSERT_EQ(1, obj->getNonZeroCount(0, 2, 1, 1));
    ASSERT_EQ(0, obj->getNonZeroCount(2, 2, 2, 1));
    ASSERT_EQ(2, obj->getNonZeroCount(2, 0, 1, 1));
    ASSERT_EQ(2, obj->getNonZeroCount(2, 2, 1, 0));
    free(dataBuffer);
}

TEST(getNonZeroCountTest1, NegativeNos) 
{     
    unsigned char *dataBuffer =testDataWithZero();
    PixelSum *obj = new PixelSum(dataBuffer, 2, 2);
    ASSERT_EQ(0, obj->getNonZeroCount(-1, -1, -1, -1));
    ASSERT_EQ(0, obj->getNonZeroCount(-2, -2, -2, -2));
    ASSERT_EQ(1, obj->getNonZeroCount(0, 0, -1, -1));
    ASSERT_EQ(1, obj->getNonZeroCount(0, 0, -2, -2));
    ASSERT_EQ(3, obj->getNonZeroCount(-1, -1, 2, 2));
    ASSERT_EQ(0, obj->getNonZeroCount(-2, -2, 4, -4));
    ASSERT_EQ(1, obj->getNonZeroCount(-1, -1, 0, 0));
    ASSERT_EQ(2, obj->getNonZeroCount(2, -2, 0, 0));
    ASSERT_EQ(1, obj->getNonZeroCount(-2, 2, 1, 1));    
    ASSERT_EQ(0, obj->getNonZeroCount(1, 2, -1, 2));
    ASSERT_EQ(2, obj->getNonZeroCount(-2, 0, 1, -1));
    ASSERT_EQ(1, obj->getNonZeroCount(-2, -2, 0, 1));
    ASSERT_EQ(0, obj->getNonZeroCount(0, -2, 1, -1));
    ASSERT_EQ(0, obj->getNonZeroCount(-2, -2, -2, 1));
    ASSERT_EQ(2, obj->getNonZeroCount(2, 0, -1, -1));
    ASSERT_EQ(3, obj->getNonZeroCount(2, 2, -1, 0));
    free(dataBuffer);
}

TEST(getNonZeroAverageTest, PositiveNos) 
{     
    unsigned char *dataBuffer =testDataWithZero();
    PixelSum *obj = new PixelSum(dataBuffer, 2, 2);
    ASSERT_EQ(1.0, obj->getNonZeroAverage(0, 0, 0, 0));
    ASSERT_EQ(1.0, obj->getNonZeroAverage(0, 0, 0, 0));
    ASSERT_EQ(0.0, obj->getNonZeroAverage(2, 2, 2, 2));
    ASSERT_EQ(2.0, obj->getNonZeroAverage(1, 1, 2, 2));
    ASSERT_EQ(0.0, obj->getNonZeroAverage(2, 2, 4, 4));
    ASSERT_EQ(2.0, obj->getNonZeroAverage(2, 2, 1, 1));    
    ASSERT_EQ(0.0, obj->getNonZeroAverage(1, 2, 1, 2));
    ASSERT_EQ(1.5, obj->getNonZeroAverage(2, 0, 1, 1));
    ASSERT_EQ(2.0, obj->getNonZeroAverage(2, 2, 0, 1));
    ASSERT_EQ(2.0, obj->getNonZeroAverage(0, 2, 1, 1));
    ASSERT_EQ(0.0, obj->getNonZeroAverage(2, 2, 2, 1));
    ASSERT_EQ(1.5, obj->getNonZeroAverage(2, 0, 1, 1));
    ASSERT_EQ(1.5, obj->getNonZeroAverage(2, 2, 1, 0));
    free(dataBuffer);
}

TEST(getNonZeroAverageTest1, NegativeNos) 
{     
    unsigned char *dataBuffer =testDataWithZero();
    PixelSum *obj = new PixelSum(dataBuffer, 2, 2);
    ASSERT_EQ(0.0, obj->getNonZeroAverage(-1, -1, -1, -1));
    ASSERT_EQ(0.0, obj->getNonZeroAverage(-2, -2, -2, -2));
    ASSERT_EQ(1.0, obj->getNonZeroAverage(0, 0, -1, -1));
    ASSERT_EQ(1.0, obj->getNonZeroAverage(0, 0, -2, -2));
    ASSERT_EQ(0.0, obj->getNonZeroAverage(-2, -2, 4, -4));
    ASSERT_EQ(1.0, obj->getNonZeroAverage(-1, -1, 0, 0));
    ASSERT_EQ(1.0, obj->getNonZeroAverage(2, -2, 0, 0));
    ASSERT_EQ(2.0, obj->getNonZeroAverage(-2, 2, 1, 1));    
    ASSERT_EQ(0.0, obj->getNonZeroAverage(1, 2, -1, 2));
    ASSERT_EQ(1.0, obj->getNonZeroAverage(-2, 0, 1, -1));
    ASSERT_EQ(1.0, obj->getNonZeroAverage(-2, -2, 0, 1));
    ASSERT_EQ(0.0, obj->getNonZeroAverage(0, -2, 1, -1));
    ASSERT_EQ(0.0, obj->getNonZeroAverage(-2, -2, -2, 1));
    ASSERT_EQ(1.0, obj->getNonZeroAverage(2, 0, -1, -1));
    free(dataBuffer);
}

TEST(readBMPImageTest, Valid) 
{    
    std::string filename = "test.bmp";
    ReadImage *obj = new ReadImage(filename);
    ASSERT_EQ(1, obj->readBMPImage());
}

TEST(readBMPImageTest1, Invalid) 
{    
    std::string filename = "";
    ReadImage *obj = new ReadImage(filename);
    ASSERT_EQ(-1, obj->readBMPImage());
}
 
int main(int argc, char **argv) 
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}