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
