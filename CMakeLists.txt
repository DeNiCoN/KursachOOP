cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (Transport)

add_executable(transport
  "src/main.cpp"
  "src/frontend.hpp"
  "src/frontend.cpp"
  "src/factory_base.hpp"
  "src/factories.hpp"
  "src/factories.cpp"
  "src/graphics.hpp"
  "src/graphics.cpp"
  "src/process_manager.hpp"
  "src/roads.hpp"
  "src/vehicle.hpp"
  "src/vehicles.hpp"
  "src/vehicles.cpp"
  "src/vertex.hpp"
  "src/vertices.hpp"
  "src/empty_renderer.hpp"
  "src/graph.hpp"
  "src/graph.cpp"
  "src/router.hpp"
  "src/router.cpp"
  "src/node.hpp"
  "src/node.cpp")

add_subdirectory(libs)
target_link_libraries(transport libs)
