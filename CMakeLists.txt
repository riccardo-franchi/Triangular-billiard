cmake_minimum_required(VERSION 3.16)
project(Triangular-billiard VERSION 1.0.0)

# enable testing
include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set C++ version to C++20, without nonstandard extensions
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# use TBB library
find_package(TBB REQUIRED)

# enable warnings
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

# enable address sanitizer and undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

add_executable(Triangular-billiard src/main.cpp src/billiard.cpp src/statistics.cpp src/commands.cpp)
target_link_libraries(Triangular-billiard PRIVATE TBB::tbb)

# to disable testing, use parameter -DBUILD_TESTING=OFF when configuring CMake
if (BUILD_TESTING)

  add_executable(billiard.test tests/billiard.test.cpp src/billiard.cpp)
  add_executable(statistics.test tests/statistics.test.cpp src/billiard.cpp src/statistics.cpp)
  
  add_test(NAME billiard.test COMMAND billiard.test)
  add_test(NAME statistics.test COMMAND statistics.test)
  target_link_libraries(billiard.test PRIVATE TBB::tbb)
  target_link_libraries(statistics.test PRIVATE TBB::tbb)

endif()

