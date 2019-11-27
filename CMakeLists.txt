######################
# set up the project #
######################
cmake_minimum_required(VERSION 3.5.1)

project(yaml_cpp_catkin)

# required to use std::shared_ptr in code and to link the python bindings
if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--no-as-needed")
endif()
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

# ensuring path to libraries are set during install
set(CMAKE_SKIP_BUILD_RPATH  FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

###########################
# Define the dependencies #
###########################

set(CATKIN_PKGS ${CATKIN_PKGS}
    # MPI-IS dependencies
    mpi_cmake_modules
)
find_package(catkin REQUIRED COMPONENTS ${CATKIN_PKGS})

add_required_dependency("yaml-cpp >= 0.5")
build_prefix_for_pkg("yaml-cpp" yaml_cpp_name)

search_for_eigen()

##########################################
# export the package as a catkin package #
##########################################

catkin_package(
  LIBRARIES ${${yaml_cpp_name}_LIBRARIES}
  INCLUDE_DIRS include
)

#######################
# Include directories #
#######################

include_directories(
  tests
  include
  ${EIGEN3_INCLUDE_DIR}
  ${GTEST_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
  ${${yaml_cpp_name}_INCLUDE_DIRS}
)

#########
# tests #
#########

set(GTEST_FILES ${GTEST_FILES}
  tests/GtestMain.cpp
  tests/TestYamlTools.cpp
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  LINK_DIRECTORIES(/usr/local/lib)
endif()

catkin_add_gtest(yaml_cpp_catkin_tests ${GTEST_FILES})
target_link_libraries(yaml_cpp_catkin_tests ${${yaml_cpp_name}_LIBRARIES} ${catkin_LIBRARIES})

##########################
# building documentation #
##########################

build_doxygen_documentation()