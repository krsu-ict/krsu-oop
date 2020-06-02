cmake_minimum_required(VERSION 3.14)
project(snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS)

if (APPLE)
    set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
else()
    set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
endif()
set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)

add_executable(snake
    models/apple.h
    models/apple.cpp
    models/snake.h
    models/snake.cpp
    models/field.h
    models/field.cpp
    views/view.h
    views/console/apple_console_view.h
    views/console/apple_console_view.cpp
    views/console/field_console_view.h
    views/console/field_console_view.cpp
    views/console/snake_console_view.h
    views/console/snake_console_view.cpp
    views/graphics/apple_graphics_view.h
    views/graphics/apple_graphics_view.cpp
    views/graphics/field_graphics_view.h
    views/graphics/field_graphics_view.cpp
    views/graphics/snake_graphics_view.h
    views/graphics/snake_graphics_view.cpp
    vendor/conio.h
    window/window.h
    window/window.cpp
    window/console_window.h
    window/console_window.cpp
    window/graphics_window.h
    window/graphics_window.cpp
    main.cpp
)

target_link_libraries(snake Qt5::Core Qt5::Widgets ${CONAN_LIBS})

configure_file(${CMAKE_CURRENT_BINARY_DIR}/qt.conf ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/qt.conf COPYONLY)

