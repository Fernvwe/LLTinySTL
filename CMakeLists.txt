cmake_minimum_required(VERSION 3.2)

project(TestDemo)
add_executable(2alloc 2alloc.cpp)
target_link_directories(2alloc
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)

add_executable(2list 2list.cpp)
target_link_directories(2list
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)
