cmake_minimum_required(VERSION 3.10)

project(filesender)


find_package(Boost 1.75.0 REQUIRED COMPONENTS  filesystem thread)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})

  add_executable(server server.cpp)
  add_executable(client client.cpp)
  target_link_libraries(server ${Boost_LIBRARIES})
    target_link_libraries(client ${Boost_LIBRARIES})
endif()
