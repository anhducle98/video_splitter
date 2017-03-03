cmake_minimum_required(VERSION 2.8)
find_package(OpenCV REQUIRED)
project(video_splitter)

set(source_files main.cpp)
set(exec_name video_splitter)
add_executable(${exec_name} ${source_files})
target_link_libraries(${exec_name} ${OpenCV_LIBS})

