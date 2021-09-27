cmake_minimum_required(VERSION 3.10)

project(test-malloc)

add_executable(main-glibc main.cc)
target_link_libraries(main-glibc PRIVATE pthread)

#link_directories(${CMAKE_SOURCE_DIR}/../libs)
add_executable(main-tcmalloc main.cc)
target_link_libraries(main-tcmalloc PRIVATE tcmalloc pthread)

add_executable(main-jemalloc main.cc)
target_link_libraries(main-jemalloc PRIVATE jemalloc pthread)