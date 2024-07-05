cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)
set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

set(PROJECT_NAME chefc)
project(chefc CXX)

if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64"
     OR "${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86"))
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
endif()

set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

####################################
#            Lexer                 #
####################################
set(Lexer_Headers
    "src/lexer/utils.h"
)

set(Lexer_Source
    "src/lexer/utils.cpp"
)

####################################
#            Source                #
####################################
set(Header_Files
    "src/argparse.h"
    "src/core.h"
)
set(Source_Files
    "src/main.cpp"
    "src/core.cpp"
    "src/argparse.cpp"
)

set(ALL_FILES
    ${Lexer_Headers}
    ${Header_Files}
    ${Lexer_Source}
    ${Source_Files}
)

add_executable(${PROJECT_NAME} ${ALL_FILES})

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            /Oi;
            /Gy
        >   
        /permissive-;
        /sdl;
        /W3;
        /std:c++20;
    )
endif()

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)