cmake_minimum_required(VERSION 3.10)

project(BigInt)

 set(ENV{http_proxy} "127.0.0.1:7890")
 set(ENV{https_proxy} "127.0.0.1:7890")

 include(FetchContent)
 FetchContent_Declare(
     googletest
     URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
 )

 set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
 FetchContent_MakeAvailable(googletest)

 add_executable(BigInt 
    ./src/main.cpp
    ./src/BigInt.cpp
    ./src/BigInt.h
    ./src/MyVector.cpp
    ./src/MyVector.h
    ./src/SmartPtr.cpp
    ./src/SmartPtr.h
)

target_link_libraries(
 BigInt
 GTest::gtest_main
)