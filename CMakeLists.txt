cmake_minimum_required(VERSION 3.26)
project(Machine_GUI)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "D:/QT/5.12.3/mingw73_64")
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
#target_link_libraries(Machine_GUI
#        Qt5::Core
#        Qt5::Gui
#        Qt5::Widgets
#)

add_executable(Machine_GUI main.cpp)
