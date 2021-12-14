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
add_executable(2priority_queue 2priority_queue.cpp)
target_link_directories(2priority_queue
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)

add_executable(2rb_tree 2rb_tree.cpp)
target_link_directories(2rb_tree
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)
add_executable(2set 2set.cpp)
target_link_directories(2set
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)
add_executable(2map 2map.cpp)
target_link_directories(2map
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)
add_executable(2hashtable 2hashtable.cpp)
target_link_directories(2hashtable
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)
add_executable(2unordered_set 2unordered_set.cpp)
target_link_directories(2unordered_set
    PRIVATE 
        ${PROJECT_SOURCE_DIR}
)