cmake_minimum_required(VERSION 3.5)

set (CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project (pubsubfrc)

set(SOURCES 
    cpp/main.cc
)

add_executable(pubsubfrc ${SOURCES})

target_include_directories(pubsubfrc
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

