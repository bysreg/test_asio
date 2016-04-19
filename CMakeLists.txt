find_package(BOOST REQUIRED system)

include_directories(
	${Boost_INCLUDE_DIRS}
)

add_executable(prog main.cpp)
target_link_libraries(Boost_LIBRARIES)
