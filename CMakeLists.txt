PROJECT(CUTES)
cmake_minimum_required(VERSION 2.8.8)

set(NAME cutes)

IF(NOT DEFINED VERSION)
MESSAGE(FATAL_ERROR "Define VERSION")
ENDIF(NOT DEFINED VERSION)

IF(NOT DEFINED LONG_VERSION)
set(LONG_VERSION "${VERSION}")
ENDIF(NOT DEFINED LONG_VERSION)

set(CUTES_INCLUDES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(prefix ${CMAKE_INSTALL_PREFIX})

option(ENABLE_MULTIARCH "enable support for multi-arch distros (lib64)" OFF)
IF(ENABLE_MULTIARCH)
  IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
    SET(LIB_SUFFIX "")
  ELSE(CMAKE_SIZEOF_VOID_P EQUAL 4)
    SET(LIB_SUFFIX 64)
  ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
ELSE()
  SET(LIB_SUFFIX "")
ENDIF()
SET(DST_LIB lib${LIB_SUFFIX})

configure_file(cutes.pc.in cutes.pc @ONLY)
install(FILES cutes.pc DESTINATION ${DST_LIB}/pkgconfig)

set(CUTES_LIB_PATH "${prefix}/share/cutes")

if("${prefix}" STREQUAL "/usr")
  set(CUTES_LIB_PATH "${CUTES_LIB_PATH}:/usr/${DST_LIB}/qt5/cutes")
else("${prefix}" STREQUAL "/usr")
  set(CUTES_LIB_PATH "${CUTES_LIB_PATH}:${prefix}/${DST_LIB}/qt5/cutes:/usr/share/cutes:/usr/${DST_LIB}/qt5/cutes")
endif("${prefix}" STREQUAL "/usr")
message(STATUS "Using CUTES_LIB_PATH: ${CUTES_LIB_PATH}")

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Qml REQUIRED)
find_package(Qt5Quick REQUIRED)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} -DCUTES_LIB_PATH=\"${CUTES_LIB_PATH}\" -fPIC -W -Wall -Wextra -Werror -g -O2 -std=c++0x")

#-Wno-psabi is to remove next g++ warning/note:
#the mangling of 'va_list' has changed in GCC 4.4
set(CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} -Wno-psabi")

install(
  DIRECTORY include/cutes
  DESTINATION include
  FILES_MATCHING
  PATTERN "*.hpp"
  PATTERN "*.h"
)

add_subdirectory("src")
add_subdirectory("doc")
