cmake_minimum_required(VERSION 3.9)

project(jkscLog VERSION 0.1)

# JKSCLOG_CPP_LIB -> Build jkscLog C++ Library with jkscLog.cpp file
option(JKSCLOG_CPP_LIB "Build C++ Library" OFF)

if (JKSCLOG_CPP_LIB)
  set(SRC_FILES cpp/jkscLog.cpp)
else()
  set(SRC_FILES jkscLog.c)
endif()

# When using MSVC, it is required to define _CRT_SECURE_NO_WARNINGS to use localtime()
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_library(jkscLog STATIC ${SRC_FILES})
