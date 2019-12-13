# Compilation Steps:
$ make all

# Execute binary:
$ cd build
$ ./build/pixsum src/lena.bmp 100 200 50 300


# Google Test Setup:
$ sudo apt-get install libgtest-dev
$ sudo apt-get install cmake
$ cd /usr/src/gtest
$ sudo cmake CMakeLists.txt
$ sudo make
$ sudo cp *.a /usr/lib

# Compile Test code:
$ cd test
$ cmake CMakeLists.txt
$ make

# Run Test:
$ ./pixelsumtest


# Questions Answers:
### a) Typical buffers in our use cases are extremely sparse matrices, i.e., the vast majority of the pixels are zero. How would you exploit this to optimize the implementation?

#### Answers:
Triplet Representation can be optimized the implementation:

In this representation, we consider only non-zero values along with their row and column index values. The 0th row stores total rows, total columns and total non-zero values in the matrix.
i.e. consider a matrix of given size 3x4 containing 3 number of non-zero values. This matrix can be represented as shown below-
                        Row     Col    Value
                        --------------------
                        3       4       3
                        --------------------
| 0 0 2 0 |             0       2       2
| 4 0 0 0 |=========>   1       0       4
| 0 0 7 0 |             2       2       7                     

Above example matrix, there are only 3 non-zero elements (2, 4, 7) and matrix size is 3x3. 

The first row in the right side table is filled with values 3, 4, 3 are indicates that it is a sparse matrix with 3 rows, 4 columns 3 non-zero values. Second row is filled with 0, 2, 2 which indicates the value in the matrix at 0th row, 3rd column is 4. Similary remaining non-zero values also follows the similar pattern. The triplet repsentation will reduced 3 iterations for every mathematical operation applied to be matrix. bigger bigger image contained more zero elements will reduced more iterations for example image size 100x100 contained 50 non-zero elements then iteration will be on 3x50 which is much less than original size of the image.

The Triplet Representation concept can be feed in linked list as well. 

### b) What changes to the code and the API need to be made if buffer dimensions can be >= 4096 x 4096? Also, what would happen if instead of 8 bits per pixel we have 16 bits per pixel?

#### Answers:
To Answers this questions, in API level no need to changes anything as the class readImage can handle any size of image while reading with 8/16/24 pixel depth. Only need to call pixels sum, average, non-zero pixel count and non-zero average calculation functions call twice if 16 bits per pixel and call 3 time if 24 bits per pixel.

### c) What would change if we needed to find the maximum value inside the search window (instead of the sum or average)? You don't need to code this, but it would be interesting to know how you would approach this problem in general, and what is your initial estimate of its O-complexity.

#### Answers:
If requirement said to find maximum value inside search window, in getPixelSum(), then:
1. Need to replace pixelSum=pixelSum + (int)*(imageData+l*width+r)statement from getPixelSum() with if condition to check maximum value from imageData and assigned maximum value to variable.                                      OR
Override getPixelSum() in derive class and implement to find maximum value.

To find maximum value inside search window in getPixelAverage(), then:
1. Need to replace pixelSum=pixelSum + (int)*(imageData+l*width+r)statement from getPixelSum()with if condition to check maximum value from imageData buffer and assigned maximum value to variable.
2. Remove  pixelAvg=(double)pixelSum/pixelCount section including if condition from getPixelAverage(). 
                                    OR
Override getPixelAverage() in derive class and implement to find maximum value.

Complexicity will be O(n) where box containing n-elements.

### d) How would multi-threading change your implementation? What kinds of performance benefits would you expect?

#### Answers:
To answers your first question, multi-threading implemented in code. 

To answer your 2nd question, in current multi-threading implementation all four functions running in parallel. So result will be approximately 1/4 of the total execution time of all four functions.

### e) Outline shortly how the class would be implemented on a GPU (choose any relevant technology, e.g. CUDA, OpenCL). No need to code anything, just a brief overview is sufficient.

#### Answers:
In order to parallelize the any operations using CUDA, an image is divided into blocks by a grid depending on the situation and calculation mechanism. The implementations of CUDA, MPs in a GPU are assigned to the blocks and threads executed by CUDA cores are assigned to the pixels in each block automatically. Therefore, what we have to do is writing the program for the threads to perform the specified operations. CUDA C/C++ that is an extension of C/C++ for parallel computing. To do that there are highlivel steps to be followed as mentioned below-
1. Transferring an data from a host to a device.
2. Setting the execution configuration.
3. Calling the kernel function for the specific operations.
4. Transferring the result from the device to the host.

Transferring variables between a host and a device is executed by the function cudaMemcpy() of CUDA API. The function cudaMalloc() can be used to allocate a memory space on a device, while new is used for a host. The sample class implementation shown in "include/pixelsumcuda.h" file.
