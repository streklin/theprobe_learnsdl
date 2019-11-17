cmake_minimum_required(VERSION 3.10)

project(TheProbe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_DIRS})


include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(TheProbe WIN32 ${SOURCES})
target_link_libraries(TheProbe ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} SDL2::Mixer)
