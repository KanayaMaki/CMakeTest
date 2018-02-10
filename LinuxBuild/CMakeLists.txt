cmake_minimum_required(VERSION 2.8)
enable_language(CXX)
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
if(GNU)

endif(GNU)

find_package(GLUT)
find_package(GLEW)
find_package(OpenGL)

set(CPOT_SRC_ROOT "../Source")
file(GLOB_RECURSE SOURCES ${CPOT_SRC_ROOT}/*.cpp ${CPOT_SRC_ROOT}/*.c)

add_definitions(-DCPOT_LINUX)
add_definitions(-DCPOT_64BIT)

include_directories(${CPOT_SRC_ROOT})
include_directories(${CPOT_SRC_ROOT}/Pot/ThirdParty/Include/Zlib)
add_executable(Main ${SOURCES})
target_link_libraries(Main ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${GLEW_LIBRARY} m)
