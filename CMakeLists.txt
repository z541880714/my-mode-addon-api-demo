cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0042 NEW)
set (CMAKE_CXX_STANDARD 11)

project (build-node-addon-api-with-cmake)
include_directories(${CMAKE_JS_INC})
file(GLOB SOURCE_FILES hello.cc)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

# Include Node-API wrappers
execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_DIR
        )
string(REGEX REPLACE "[\r\n\"]" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})


# define NAPI_VERSION
add_definitions(-DNAPI_VERSION=3)

# include_directories(D:/myLibrary/12.cpplib/02_opencv/opencv/build/include)
# file(GLOB my_libs D:/myLibrary/12.cpplib/02_opencv/opencv-4.10.0/build/lib/Debug/*.lib)



# set(OpenCV_DIR D:/1.Environment/9_libs/05_opencv/opencv/sources/cmake-build-debug)
# find_package(OpenCV REQUIRED)
file(GLOB cv_libs D:/1.Environment/9_libs/05_opencv/opencv/sources/cmake-build-debug/lib/*.lib)
#include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(D:/1.Environment/9_libs/05_opencv/opencv/sources/cmake-build-debug)

MESSAGE(CMAKE_SOURCE_DIR====>  ${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB my_libs ${CMAKE_SOURCE_DIR}/libs/*.lib)


target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} ${my_libs} ${cv_libs})

message(==================================================  )
message(==================================================  )