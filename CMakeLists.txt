cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS system thread REQUIRED)

include_directories(
	${Boost_INCLUDE_DIRS}
)

add_executable(prog main.cpp)
target_link_libraries(prog ${Boost_LIBRARIES})
