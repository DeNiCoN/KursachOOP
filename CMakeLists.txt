cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (Transport)

add_executable(transport
  "src/main.cpp"
  )

add_subdirectory(libs)
target_link_libraries(transport libs)
