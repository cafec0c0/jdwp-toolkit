cmake_minimum_required(VERSION 3.29)
project(jdwp_toolkit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(jdwp_toolkit
        ApplicationContext.cpp ApplicationContext.h
        main.cpp
)

target_link_libraries(jdwp_toolkit
        Qt::Core
        Qt::Gui
        Qt::Widgets
        jdwp
)

target_include_directories(jdwp_toolkit PRIVATE .)

add_subdirectory(ui)
add_subdirectory(controllers)
add_subdirectory(model)
add_subdirectory(client)
add_subdirectory(util)

