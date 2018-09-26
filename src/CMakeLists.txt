cmake_minimum_required(VERSION 2.8.12)
add_compile_options(-std=c++17) # add_compile_options instead of CMAKE_CXX_FLAGS in CMake 2.8.12 or newer
add_compile_options(-Wall)      # add_compile_options instead of CMAKE_CXX_FLAGS in CMake 2.8.12 or newer
add_compile_options(-ggdb3)     # add_compile_options instead of CMAKE_CXX_FLAGS in CMake 2.8.12 or newer
project (cppcon)
find_package(Boost 1.68 COMPONENTS coroutine context REQUIRED)
if(Boost_FOUND)
  add_executable(fibb fibb.cpp)
  TARGET_LINK_LIBRARIES(fibb ${MANDATORY_LIBRARIES} boost_coroutine boost_context)
endif()

