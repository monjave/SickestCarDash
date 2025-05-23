
# cmake_minimum_required(VERSION 3.21.1)
project(CarDashboardApp VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Qml SerialPort Widgets Test)
qt_standard_project_setup(REQUIRES 6.4.2)

# # ================== Configurable Options ==================
option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)
option(BUILD_GUI "Build the Qt GUI application" ON)
option(BUILD_TESTING "Build unit tests" ON)

# ================== Core Library ==================
add_library(core STATIC
    # ${CMAKE_CURRENT_LIST_DIR}/src/CircularBuffer.cc
    # ${CMAKE_CURRENT_LIST_DIR}/src/CircularBufferManager.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/VehicleParser.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/VehicleConnection.cpp
    ${CMAKE_CURRENT_LIST_DIR}/include/VehicleParser.h
    ${CMAKE_CURRENT_LIST_DIR}/include/VehicleConnection.h
)

# Link QtCore to core lib
target_link_libraries(core PUBLIC Qt6::Core Qt6::SerialPort)

# Enable AUTOMOC for QObject macros
set_target_properties(core PROPERTIES AUTOMOC ON)

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


    include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
    include_directories(${CMAKE_CURRENT_LIST_DIR}/src)

    qt_add_executable(CarDashboardApp
        App/main.cpp
        include/CircularBuffer.h
        include/CircularBufferManager.h
        include/CircularBufferManagerWrapper.h
        src/CircularBufferManagerWrapper.cpp
        include/VehicleConnection.h
        src/VehicleConnection.cpp
        include/VehicleParser.h
        src/VehicleParser.cc
    )

    target_link_libraries(CarDashboardApp
        PRIVATE
            Qt6::Core
            Qt6::Quick
            Qt6::Qml
            Qt6::Widgets
            Qt6::SerialPort
            core
    )


if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets/qtquickcontrols2.conf")
    qt_add_resources(${CMAKE_PROJECT_NAME} "configuration"
        PREFIX "/"
        FILES
            assets/qtquickcontrols2.conf
    )
endif()
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
    # 1.  Make CTest targets visible to the build.
    #    The argument is optional – `enable_testing()` with no args
    #    is the canonical form, but `enable_testing(true)` works too.
    enable_testing()

    # 2.  Find the Qt module that provides the QTest harness.
    # find_package(Qt6 REQUIRED COMPONENTS Test)

    # 3.  Build **one** test executable.
    #    Target name == executable name  ==> fewer places to typo later.
    qt_add_executable(CircularBufferTest
        test/TestCircularBuffer.cc            # <-- source file(s)
    )

    # 4.  Link everything the test binary needs.
    target_link_libraries(CircularBufferTest
        PRIVATE
        core                                   # your static library
        Qt6::Test                              # imported Qt6 target
    )

    # 5.  Register with CTest so `ctest` picks it up.
    add_test(
        NAME    CircularBufferTest             # human‑readable label
        COMMAND CircularBufferTest             # executable to run
    )
endif()


# if(BUILD_TESTING)
#     enable_testing()

#     include(FetchContent)
#     FetchContent_Declare(
#       googletest
#         URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
#     )
#     FetchContent_MakeAvailable(googletest)

#     add_executable(unit_tests
#         test/TestCircularBuffer.cc
#         test/TestCircularBufferManager.cc
#         test/TestVehicleParser.cc
#         test/TestVehicleConnection.cc
#         # test/ReplayParser.cc
#     )

#     target_link_libraries(unit_tests
#         core
#         gtest_main
#     )

#     include(GoogleTest)
#     gtest_discover_tests(unit_tests)
# endif()
