cmake_minimum_required(VERSION 3.5.1)

# set the project name
project(demo)

LINK_LIBRARIES(pthread curl)

# add the executable
add_executable(main main.c)
