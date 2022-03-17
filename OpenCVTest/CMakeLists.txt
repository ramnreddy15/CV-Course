cmake_minimum_required(VERSION 2.8)
project( Chapter2 )
find_package( OpenCV REQUIRED )
add_executable( Chapter2 Chapter2.cpp )
target_link_libraries( Chapter2 ${OpenCV_LIBS} )

