cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

add_executable(ft_containers main.cpp /
        utils.hpp/
        containers/queue.class.hpp containers/vector.class.hpp /
        containers/stack.class.hpp containers/list.class.hpp containers/multiset.class.hpp /
        Iterators/list_iterator.hpp Iterators/vector_iterator.hpp)
