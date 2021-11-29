cmake_minimum_required (VERSION 3.21.3)
project (DTOPGUI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


file(GLOB_RECURSE SOURCES
	source/*.h
	source/*.cpp
)

list(FILTER lib_srcs EXCLUDE REGEX ".*olcPixelGameEngine\\.h$")

add_executable (dtopgui ${SOURCES})

