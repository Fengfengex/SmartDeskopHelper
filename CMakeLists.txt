cmake_minimum_required(VERSION 3.16)
project(SmartDesktopHelper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets Network REQUIRED)

set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.h
    src/mainwindow.cpp
    src/mainwindow.ui
    
    src/HomePage/homepage.h
    src/HomePage/homepage.cpp
    src/HomePage/homepage.ui
    
    src/HomePage/clockdisplay.h
    src/HomePage/clockdisplay.cpp
    
    src/Utils/timezonemanager.h
    src/Utils/timezonemanager.cpp
    
    src/Utils/filemanager.h
    src/Utils/filemanager.cpp
    
    src/Utils/constants.h
    
    resources/resources.qrc
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)