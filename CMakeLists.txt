cmake_minimum_required(VERSION 3.16)
project(AlienStateUniversityofPeopleandStuff)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

file(GLOB SOURCES "src/*.cpp" "src/*.h")


add_subdirectory(SDL EXCLUDE_FROM_ALL)

add_executable(AlienStateUniversityofPeopleandStuff ${SOURCES})

target_link_libraries(AlienStateUniversityofPeopleandStuff PRIVATE SDL3::SDL3)

target_include_directories(AlienStateUniversityofPeopleandStuff PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/SDL/include
)

# cmake -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER="C:\MinGW\bin\gcc.exe" -DCMAKE_CXX_COMPILER="C:\MinGW\bin\g++.exe"