##############################################################################
# CMake
##############################################################################

cmake_minimum_required(VERSION 2.8.9)
project(gui_application)

SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Werror")

##############################################################################
# Catkin
##############################################################################

# qt_build provides the qt cmake glue, roscpp the comms for a default talker
find_package(catkin REQUIRED COMPONENTS roscpp api_application)
include_directories(${catkin_INCLUDE_DIRS})
# Use this to define what the package will export (e.g. libs, headers).
# Since the default here is to produce only a binary, we don't worry about
# exporting anything. 
catkin_package()

##############################################################################
# Qt Environment
##############################################################################

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

##############################################################################
# SDL2
##############################################################################

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
Include_directories(${SDL2_INCLUDE_DIRS})

##############################################################################
# Sources
##############################################################################

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS *.cpp)
file(GLOB_RECURSE QT_UI RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS *.ui)

qt5_wrap_ui(UI_HEADERS ${QT_UI})

qt5_add_resources(RESOURCES icons.qrc 3d.qrc)

##############################################################################
# Binaries
##############################################################################

add_executable(kitrokopter ${QT_SOURCES} ${UI_HEADERS} ${RESOURCES})
target_link_libraries(kitrokopter
  ${catkin_LIBRARIES}
  ${SDL2_LIBRARIES}
  libIrrlicht.so
)

install(TARGETS kitrokopter RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

qt5_use_modules(kitrokopter Widgets Concurrent)

