cmake_minimum_required(VERSION 3.13...3.27)

project(Kokotris VERSION 0.1
               DESCRIPTION "Cross-platform implementation of tetris engine"
               LANGUAGES C)

add_executable(tetris src/main.c src/input_linux.c src/draw.c src/engine.c)

target_compile_options(tetris PUBLIC "-g")
