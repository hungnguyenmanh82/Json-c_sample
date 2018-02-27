cmake_minimum_required(VERSION 2.8)
PROJECT(CmakeJsonC)
#sub folder “src” lại chứa CMakeLists.txt file
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(json-c)
ADD_SUBDIRECTORY(tests)
ADD_SUBDIRECTORY(samples)
