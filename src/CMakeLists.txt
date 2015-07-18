cmake_minimum_required(VERSION 2.6)
project(Test)

find_package(OpenThreads)
find_package(osg)
find_package(osgDB)
find_package(osgGA)
find_package(osgUtil)
find_package(osgViewer)

macro(config_project PROJNAME LIBNAME)
    include_directories(${${LIBNAME}_INCLUDER_DIR})
    target_link_libraries(${PROJNAME} ${${LIBNAME}_LIBRARY})
endmacro()

add_executable(Test main.cpp)
config_project(Test OPENTHREADS)
config_project(Test OSG)
config_project(Test OSGDB)
config_project(Test OSGGA)
config_project(Test OSGUTIL)
config_project(Test OSGVIEWER)

