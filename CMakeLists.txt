#
# Copyright (c) 2019, New York University and Max Planck Gesellschaft.
#
# License BSD-3 clause
#

#
# set up the project
#
cmake_minimum_required(VERSION 3.10.2)

project(yaml_utils)

# Using C++17
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

#
# Dependencies
#

# depend on ament macros
find_package(ament_cmake REQUIRED)
find_package(mpi_cmake_modules REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(Eigen3 REQUIRED)

# export de dependencies
ament_export_dependencies(mpi_cmake_modules yaml-cpp Eigen3)

# prepare the final export
set(all_targets)
ament_export_interfaces(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)

#
# Build the main library
#

# Headers only library.
add_library(${PROJECT_NAME} INTERFACE)
# Add the include dependencies
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>)
# Dependencies
target_link_libraries(${PROJECT_NAME} INTERFACE Eigen3::Eigen)
target_link_libraries(${PROJECT_NAME} INTERFACE ${YAML_CPP_LIBRARIES})
# Export the target.
ament_export_libraries(${YAML_CPP_LIBRARIES})
ament_export_include_directories(include)
# For the installation
list(APPEND all_targets ${PROJECT_NAME})

#
# add unit tests #
#
if(BUILD_TESTING)
  find_package(ament_cmake_gtest)

  # Set a general config folder path for all tests
  set(TEST_CONFIG_PATH ${PROJECT_SOURCE_DIR}/tests/config/)

  ament_add_gtest(test_${PROJECT_NAME} tests/gtest_main.cpp
                  tests/test_yaml_tools.cpp)

  # Link the dependecies to it.
  target_link_libraries(test_${PROJECT_NAME} ${PROJECT_NAME})
endif()

#
# Install the package
#
install(DIRECTORY include/ DESTINATION include)

install(
  TARGETS ${all_targets}
  EXPORT export_${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES
  DESTINATION include)

#
# Building documentation.
#
add_documentation()

#
# Export as an ament_package
#
ament_package()
