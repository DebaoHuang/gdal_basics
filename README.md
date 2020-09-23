# Weekly Report

updated 09/23/2020

* Replace <io.h> with <boost/filesystem.hpp>, write a more universal approach
* Make getfilename() as a function
* Make more outputs



09/08/2020

- Install OpenCV, GDAL via VCPKG
  - set vcpkg as system variable *path*
  - install x64 version
- Learn how to use CMAKE
  - write CMakeLists.txt
  - use command line to compile the main.cpp via CMAKE
  - build the project
- Write a program computing mean and standard deviation for all input images
  - use <gdal_priv.h> to read the *.tif file and get its information like Xsize, Ysize, number of bands
  - use GetStatistics function to get the mean and standard deviation for all pixels in a band
  - use <io.h> to read the filename of certain type in batches using struct _finddata_t, function _findfirst and _findnext
  - print the results to a *.txt file
- Write a program fitting a best line/plane from a specific point set
  - get a library of generic RANSAC from GitHub
  - compile and run the program