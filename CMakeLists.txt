CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(eng)

# setup custom cmake modules path
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")

OPTION(USE_PCH "Use precompiled header" ON)

# choose a default build type if not specified
IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
ENDIF(NOT CMAKE_BUILD_TYPE)
MESSAGE(STATUS "BUILD TYPE: " ${CMAKE_BUILD_TYPE})

# setup compiler options
IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(CXX_WARNS "")
    SET(CMAKE_CXX_FLAGS " -std=gnu++0x -pipe ${CXX_WARNS}")
    SET(CMAKE_CXX_FLAGS_DEBUG "-g -ggdb")
    SET(CMAKE_CXX_FLAGS_RELEASE "-O2")
    SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O1 -g -fno-inline")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)


INCLUDE_DIRECTORIES(
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
    ADD_DEFINITIONS(-D_DEBUG)
ENDIF(CMAKE_BUILD_TYPE STREQUAL "Debug")

SET(SOURCES
  src/main.cpp
  src/matrix.cpp
  src/matrix.h
)

# target executable
ADD_EXECUTABLE(eng ${SOURCES})

# target link libraries
TARGET_LINK_LIBRARIES(
    eng
)


