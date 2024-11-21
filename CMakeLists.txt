
cmake_minimum_required(VERSION 3.14)

project(
	fastvec 
	VERSION 0.1
	DESCRIPTION "Fast Cpp Vector Reimplementation "
	HOMEPAGE_URL "https://github.com/retrodeb/fastvec"
	LANGUAGES CXX
)

add_library(${CMAKE_PROJECT_NAME} INTERFACE)

set(FASTVEC_IS_MASTER_PROJECT OFF)
if (${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
	set(FASTVEC_IS_MASTER_PROJECT ON)
endif()

# Print the project name
message("PROJECT_NAME: ${PROJECT_NAME}")
# Print the CMake project name
message("CMAKE_PROJECT_NAME: ${CMAKE_PROJECT_NAME}")
message("is master: ${FASTVEC_IS_MASTER_PROJECT}")
option(FASTVEC_BUILD_INSTALL "Generate the install target" ${FASTVEC_IS_MASTER_PROJECT})
option(FASTVEC_BUILD_TESTS "Build the test programs" ${FASTVEC_IS_MASTER_PROJECT})

#target_compile_features(${CMAKE_PROJECT} INTERFACE cxx_std_17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

include(GNUInstallDirs)

target_include_directories(
	${CMAKE_PROJECT_NAME}
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if (FASTVEC_BUILD_TESTS)
	include(CTest)
	add_subdirectory(test)
endif()

if (FASTVEC_BUILD_INSTALL)

	include(CMakePackageConfigHelpers)
	write_basic_package_version_file(
		"${CMAKE_CURRENT_BINARY_DIR}/fastvecConfigVersion.cmake"
		VERSION ${PROJECT_VERSION}
		COMPATIBILITY SameMajorVersion
	)
	install(
		FILES "${CMAKE_CURRENT_BINARY_DIR}/fastvecConfigVersion.cmake"
		DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/fastvec"
	)

	install(
		TARGETS fastvec
		EXPORT fastvec
	)
	install(
		EXPORT fastvec
		DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/fastvec"
		NAMESPACE fastvec::
		FILE fastvecConfig.cmake
	)

	install(
    	DIRECTORY include/
    	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    	FILES_MATCHING
    	PATTERN "*.hpp"
	)
endif()
