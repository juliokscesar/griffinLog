cmake_minimum_required(VERSION 3.9)

project(jkscLog VERSION 0.1)

set(SRC_FILES
	jkscLog.c
)

add_library(jkscLog STATIC ${SRC_FILES})
