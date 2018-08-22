cmake_minimum_required(VERSION 3.10)
project(treinamento_pdi)

set(CMAKE_CXX_STANDARD 17)

add_executable(treinamento_pdi main.cpp)

find_package( OpenCV REQUIRED )
set(SOURCE_FILES Objects.cpp)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries( treinamento_pdi ${OpenCV_LIBS} )

find_package(cvBlob REQUIRED)
target_link_libraries(treinamento_pdi ${cvBlob_LIBS})
