cmake_minimum_required(VERSION 3.9)

project(jkscLog VERSION 0.1)

# Function to abort CMake in case no option was provided
function(abort)
  if(UNIX)
    set(KILL_COMMAND "killall")
    execute_process(COMMAND ${KILL_COMMAND} -9 cmake
      WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )
  else()
    set(KILL_COMMAND "taskkill")
    execute_process(COMMAND ${KILL_COMMAND} /IM cmake.exe /F
      WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )
  endif()
endfunction()

# JKSCLOG_C_LIB -> Builds jkscLog C library with jkscLog.c file
option(JKSCLOG_C_LIB "Build C Library" OFF)

# JKSCLOG_CPP_LIB -> Build jkscLog C++ Library with jkscLog.cpp file
option(JKSCLOG_CPP_LIB "Build C++ Library" OFF)

if (JKSCLOG_C_LIB)
	set(SRC_FILES jkscLog.c)
elseif(JKSCLOG_CPP_LIB)
	set(SRC_FILES cpp/jkscLog.cpp)
else()
	message(FATAL_ERROR "NO JKSCLOG OPTION PROVIDED, USE -DJKSCLOG_C_LIB=ON OR -DJKSCLOG_C_LIB=ON")
	abort()
endif()

# When using MSVC, it is required to define _CRT_SECURE_NO_WARNINGS to use localtime()
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_library(jkscLog STATIC ${SRC_FILES})
