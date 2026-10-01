cmake_minimum_required(VERSION 4.2)
project(theme_switcher LANGUAGES C CXX)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)
qt_standard_project_setup()

file(GLOB_RECURSE CPP_SRC CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.h")

message(STATUS "Headers: ${HEADERS}")
message(STATUS "source: ${CPP_SRC}")

qt_add_executable(${PROJECT_NAME} ${CPP_SRC} ${HEADERS})

file(GLOB_RECURSE QML_SRC
  CONFIGURE_DEPENDS
  RELATIVE ${CMAKE_SOURCE_DIR}
  "${CMAKE_SOURCE_DIR}/qml/*.qml"
)

qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)

qt_add_qml_module(${PROJECT_NAME}
  URI ThemeSwitcher
  VERSION 1.0
  QML_FILES ${QML_SRC}
)

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE
  Qt6::Core
  Qt6::Gui
  Qt6::Qml
  Qt6::Quick
)
