cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (Transport)


file(GLOB_RECURSE SOURCES
  LIST_DIRECTORIES false
  CONFIGURE_DEPENDS
  src/*.hpp src/*.cpp)
set(SOURCES ${SOURCES})

add_executable(transport
  ${SOURCES}
  )

add_subdirectory(libs)
target_link_libraries(transport libs)
