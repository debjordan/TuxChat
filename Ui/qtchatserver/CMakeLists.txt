cmake_minimum_required(VERSION 3.14)

# Nome do projeto
project(ChatServer)

# Configurações básicas
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Encontrar o Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Gui Qml Quick)
# Adicionar o executável
add_executable(ChatServer main.cpp tcpserver.cpp)

# Incluir os cabeçalhos
target_include_directories(ChatServer PRIVATE ${Qt5Core_INCLUDE_DIRS} ${Qt5Network_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS})

# Linkar as bibliotecas do Qt
target_link_libraries(ChatServer Qt5::Core Qt5::Network Qt5::Gui)

set(CMAKE_PREFIX_PATH "/usr/lib/qt5")