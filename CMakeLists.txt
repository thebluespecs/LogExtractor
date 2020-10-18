cmake_minimum_required(VERSION 3.1...3.14)
project( LogExtractor )

#-------------VENDOR--------------------
set(vspdlog ./vendor/spdlog/include)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

#-------------SOURCE--------------------
SET(source ./src/main.cpp ./src/Log.cpp)
include_directories(./src/include ${vspdlog})

# -----------EXECUTION------------------
# ADD_LIBRARY(smol SHARED ${smolsrc})
ADD_EXECUTABLE(LogExtractor ${source})
TARGET_LINK_LIBRARIES(LogExtractor ${Boost_LIBRARIES})