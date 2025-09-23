cmake_minimum_required(VERSION 3.15)
project(PcapUtility LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Automatically gather all source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(PcapUtility ${SOURCES})
target_compile_features(PcapUtility PRIVATE cxx_std_20)
target_link_libraries(PcapUtility PRIVATE pcap)
