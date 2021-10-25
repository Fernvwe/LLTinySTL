cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)
project(TestDemo)
add_executable(2alloc 2alloc.cpp)
add_compile_options(-std=c++14)
target_link_directories(2alloc
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)

add_executable(2list 2list.cpp)
target_link_directories(2list
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)
add_executable(2vector 2vector.cpp)
target_link_directories(2vector
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)

add_executable(2deque 2deque.cpp)
target_link_directories(2deque
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)
add_executable(2algorithm 2algorithm.cpp)
target_link_directories(2algorithm
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)

add_executable(2stackAqueue 2stackAqueue.cpp)
target_link_directories(2stackAqueue
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)