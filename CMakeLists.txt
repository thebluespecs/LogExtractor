cmake_minimum_required(VERSION 3.1...3.14)
project( LogExtractor )

# -------------SMOL--------------------
# set(core ./Smol/src/core)
# set(log ./Smol/src/log)

# set(smolheader ./Smol)

#-------------VENDOR--------------------
# set(vspdlog ./Smol/vendor/spdlog/include)
# include_directories(${core} ${log} ${smolheader} ${vspdlog})

#-------------SOURCE--------------------
# SET(smolsrc ${core}/Application.cpp ${log}/Log.cpp)
include_directories(./src/include)
SET(source ./src/main.cpp)

# ADD_LIBRARY(smol SHARED ${smolsrc})

ADD_EXECUTABLE(LogExtractor ${source})
# TARGET_LINK_LIBRARIES(LogExtractor smol)