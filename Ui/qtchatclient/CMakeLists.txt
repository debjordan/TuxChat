cmake_minimum_required(VERSION 3.14)

project(ChatClient)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Network Quick Qml)

add_executable(ChatClient main.cpp tcpclient.cpp)

qt5_add_resources(QML_RESOURCES resources.qrc)

target_include_directories(ChatClient PRIVATE ${Qt5Core_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS} ${Qt5Quick_INCLUDE_DIRS})
target_link_libraries(ChatClient Qt5::Core Qt5::Network Qt5::Quick)

target_sources(ChatClient PRIVATE ${QML_RESOURCES})