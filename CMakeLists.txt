cmake_minimum_required(VERSION "3.17")

project(cpp20_cookbook)

set(CMAKE_CXX_STANDARD 20)

file(GLOB cpp20_cookbook_SRC
     "src/*.h"
     "src/*.cpp"
)

add_executable(cpp20_cookbook_ex ${cpp20_cookbook_SRC})

