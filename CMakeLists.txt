cmake_minimum_required(VERSION 3.16)
project(statistics VERSION 0.1.0)

# abilita il supporto per i test, tra cui l'opzione BUILD_TESTING usata sotto
include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# richiedi l'uso di C++20, senza estensioni non-standard offerte dal compilatore usato 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

find_package(TBB REQUIRED)

# abilita warning
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

# abilita l'address sanitizer e l'undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

#add_executable(main main.cpp)
#target_link_libraries(billiard.test PRIVATE TBB::tbb)

# se il testing e' abilitato...
#   per disabilitare il testing, passare -DBUILD_TESTING=OFF a cmake durante la fase di configurazione
if (BUILD_TESTING)

  # aggiungi l'eseguibile billiard.test
  add_executable(billiard.test tests/billiard.test.cpp src/billiard.cpp)
  # aggiungi l'eseguibile billiard.test alla lista dei test
  add_test(NAME billiard.test COMMAND billiard.test)
  target_link_libraries(billiard.test PRIVATE TBB::tbb)

endif()

