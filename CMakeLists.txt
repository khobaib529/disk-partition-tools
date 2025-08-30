cmake_minimum_required(VERSION 3.11)

project(disk-partition-tools)

# mbr executable
add_executable(mbr src/mbr.cc src/utils.cc)
target_include_directories(mbr PUBLIC third_party/CLI11)
target_include_directories(mbr PUBLIC include/)

# gpt executable
add_executable(gpt src/gpt.cc src/utils.cc)
target_include_directories(gpt PUBLIC third_party/CLI11)
target_include_directories(gpt PUBLIC include/)

# install mbr and gpt binary
install(TARGETS mbr gpt RUNTIME DESTINATION /usr/local/bin)
