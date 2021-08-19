cmake_minimum_required(VERSION 3.2)
project(Demoalloc)

add_executable(Demoalloc 2alloc.cpp )

target_link_directories(Demoalloc
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)
