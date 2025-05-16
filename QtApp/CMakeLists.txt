
cmake_minimum_required(VERSION 3.21.1)
project(CarDashboardApp LANGUAGES CXX)

# # ================== Configurable Options ==================
option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)
option(BUILD_GUI "Build the Qt GUI application" ON)
# option(BUILD_TESTING "Build unit tests" ON)

# ================== Core Library ==================
add_library(core STATIC
    ${CMAKE_CURRENT_LIST_DIR}/src/CircularBuffer.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/CircularBufferManager.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/CircularBufferManagerWrapper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/include/CircularBuffer.h
    ${CMAKE_CURRENT_LIST_DIR}/include/CircularBufferManager.h
    ${CMAKE_CURRENT_LIST_DIR}/include/CircularBufferManagerWrapper.h
)

target_include_directories(core
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
include_directories(${CMAKE_CURRENT_LIST_DIR}/src)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml)
set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY}
    CACHE STRING "Import paths for Qt Creator's code model"
    FORCE
)

# ================== Qt GUI App (Optional) ==================
if(BUILD_GUI)
find_package(Qt6 6.8 REQUIRED COMPONENTS Core Gui Widgets Qml Quick QuickTimeline ShaderTools SerialPort)
qt_standard_project_setup()

#qt_add_executable(${CMAKE_PROJECT_NAME})
qt_add_executable(CarDashboardApp
  App/main.cpp
  include/CircularBuffer.h
  include/CircularBufferManager.h
  include/CircularBufferManagerWrapper.h
  src/CircularBuffer.cc
  src/CircularBufferManager.cc
  src/CircularBufferManagerWrapper.cpp
)

qt_add_resources(${CMAKE_PROJECT_NAME} "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf)

include(qds)

if (BUILD_QDS_COMPONENTS)
    include(qmlcomponents OPTIONAL)
endif()

if (LINK_INSIGHT)
    include(insight OPTIONAL)
endif ()

include(GNUInstallDirs)
install(TARGETS ${CMAKE_PROJECT_NAME}
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
endif()

# ================== Unit Tests (Optional) ==================
if(BUILD_TESTING)
    enable_testing()

    include(FetchContent)
    FetchContent_Declare(
      googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    )
    FetchContent_MakeAvailable(googletest)

    add_executable(unit_tests
        test/testCircularBuffer.cc
        test/testCircularBufferManager.cc
    )

    target_link_libraries(unit_tests
        core
        gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(unit_tests)
endif()
