cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

# Search in the directorys for additional CMake modules.
set(CMAKE_MODULE_PATH
  "${CMAKE_SOURCE_DIR}/CMake"
  "${CMAKE_SOURCE_DIR}/CMake/Utils"
  "${CMAKE_SOURCE_DIR}/CMake/Packages"
)
set(CMAKE_TEMPLATE_PATH "${CMAKE_SOURCE_DIR}/CMake/Templates")

# Set the project name.
project(NODEJS_NGE2)
set(NODEJS_NGE2_SRCS)
set(NODEJS_NGE2_LIBS)
set(NODEJS_NGE2_VERSION 2.1)

include(Common)
include(SetupDepends)
include(Nodejs)

prepare_nodejs(BIN_VERSION)

# Put libraries into `lib'.
if(NOT WIN32)
  set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
endif()

if(LINUX)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
endif()

set(NODEJS_NGE2_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE INTERNAL
  "Real variable for build." FORCE)

if(${NODEJS_NGE2_BUILD_TYPE} STREQUAL "Debug")
  set(NODEJS_NGE2_IS_DEBUG 1)
endif()

# Search for C header files in these directories.
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_BINARY_DIR}/include)

list(APPEND NODEJS_NGE2_SRCS
  src/NgeApp.cpp
  src/nge2.cpp
  src/graphics.cpp
  src/input.cpp
  src/main.cpp
  )
list(APPEND NODEJS_NGE2_LIBS ${NODEJS_NGE2_DEP_LIBS})

add_node_extension(node_nge2 ${NODEJS_NGE2_SRCS})
target_link_libraries(node_nge2 ${NODEJS_NGE2_LIBS})
