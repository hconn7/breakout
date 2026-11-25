cmake_minimum_required(VERSION 3.16)
project(breakout CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find packages first
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)

# 2. Collect your source files
file(GLOB SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(breakout ${SOURCES})

# 4. NOW apply your options and directories to the valid target
target_compile_options(breakout PRIVATE -g -Wall -Wextra -Wshadow)


add_custom_command(TARGET breakout POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${CMAKE_SOURCE_DIR}/assets"
          "$<TARGET_FILE_DIR:breakout>/assets"
            "${CMAKE_SOURCE_DIR}/levelDat"
            "$<TARGET_FILE_DIR:breakout>/levelDat"
            "${CMAKE_SOURCE_DIR}/playerDat"
            "$<TARGET_FILE_DIR:breakout>/playerDat"


)
target_include_directories(breakout PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

# 5. Link libraries last
target_link_libraries(breakout PRIVATE 
    SDL3_image::SDL3_image
    SDL3::SDL3
    SDL3_ttf
)
