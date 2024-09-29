cmake_minimum_required(VERSION 3.22.1)

project(DA2024_PRJ1_G17_5)

file(GLOB Src src/*.cpp)
file(GLOB Hpp lib/*.hpp)

add_executable(
	main
  ${Src}
  ${Hpp}
)

set(EXECUTABLE_OUTPUT_PATH ../)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-std=c++14 -pedantic -Wall -Wuninitialized -Werror -Wextra -lm -O -fsanitize=address -fsanitize=undefined)

# Doxygen Build
find_package(Doxygen)
if (DOXYGEN_FOUND)
	set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/doc/output")
	if (NOT EXISTS "${BUILD_DOC_DIR}")
		file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
	endif ()

	set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile")
	set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
	configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

	message("Doxygen build started")
	add_custom_target(Doxygen ALL
			COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
			WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
			COMMENT "Generating API documentation with Doxygen"
			VERBATIM)
else (DOXYGEN_FOUND)
	message("Doxygen needs to be installed to generate the documentation.")
endif (DOXYGEN_FOUND)
