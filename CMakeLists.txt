project(gthumb-openexr-extension)
cmake_minimum_required(VERSION 3.20)

find_package(PkgConfig REQUIRED)

pkg_check_modules (GTHUMB REQUIRED gthumb-3.10)
pkg_check_modules (GLIB2 REQUIRED glib-2.0)
pkg_check_modules(GTK REQUIRED gtk+-3.0)

# Newer versions of OpenEXR (>= 3.0) ship with their own module
find_package(Imath CONFIG)
find_package(OpenEXR CONFIG)
if (OpenEXR_FOUND)
    set(OpenEXR_LIBRARIES 
        OpenEXR::OpenEXR
        Imath::Imath
    )
else()
    set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
    find_package(OpenEXR REQUIRED)
endif()


# set(LIBRARY "libgthumb-openexr-viewer")
set(API 3.10)
set(EXT_VERSION 3.10.0)

# configure_file(config.h.in config.h)
configure_file(openexr-viewer.extension.in openexr-viewer.extension)

add_library(openexr-viewer SHARED
    src/ExrLoader.cpp
    src/ExrLoader.h
    src/main.c
    )

target_include_directories(openexr-viewer
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${GTHUMB_INCLUDE_DIRS}
    /usr/include/gthumb
    ${GLIB2_INCLUDE_DIRS}
    ${GTK_INCLUDE_DIRS}
    )

target_link_libraries(openexr-viewer PUBLIC 
    ${OpenEXR_LIBRARIES}
    ${GTHUMB_LIBRARIES}
    ${GLIB2_LIBRARIES}
    ${GTK_LIBRARIES}
)



set(GTHUMB_EXT_DIR "lib/gthumb/extensions/")

install(TARGETS openexr-viewer DESTINATION ${GTHUMB_EXT_DIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/openexr-viewer.extension DESTINATION ${GTHUMB_EXT_DIR})