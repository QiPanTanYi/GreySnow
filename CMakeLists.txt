cmake_minimum_required(VERSION 3.21)
project(caption C)

set(CMAKE_C_STANDARD 99)

# 设置目标可执行文件
add_executable(KeyDisplay
        src/main.c
        src/keyhook.c
        src/display.c
        src/utils.c
        src/statusbar.c
        )

# 指定 include 路径
target_include_directories(KeyDisplay PRIVATE include)
