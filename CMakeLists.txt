cmake_minimum_required(VERSION 3.11)

project(disk-partition-tools)
add_executable(mbr src/mbr.cc src/utils.cc)
target_include_directories(mbr PUBLIC third_party/CLI11)
target_include_directories(mbr PUBLIC include/)
