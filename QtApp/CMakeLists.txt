cmake_minimum_required(VERSION 3.16)
project(QtApp VERSION 0.1 LANGUAGES CXX)

# # ================== Configurable Options ==================
option(BUILD_GUI "Build the Qt GUI application" ON)
# option(BUILD_TESTING "Build unit tests" ON)

# ================== Core Library ==================
add_library(core STATIC
    ${CMAKE_CURRENT_LIST_DIR}/src/CircularBuffer.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/CircularBufferManager.cc
    ${CMAKE_CURRENT_LIST_DIR}/include/CircularBuffer.h
    ${CMAKE_CURRENT_LIST_DIR}/include/CircularBufferManager.h
)

target_include_directories(core
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# ================== Qt GUI App (Optional) ==================
if(BUILD_GUI)
    find_package(Qt6 REQUIRED COMPONENTS Quick)
    qt_standard_project_setup(REQUIRES 6.8)

    include_directories(${CMAKE_CURRENT_LIST_DIR}/include)
    include_directories(${CMAKE_CURRENT_LIST_DIR}/src)

    qt_add_executable(appQtApp
        main.cpp
        include/CircularBuffer.h
        include/CircularBufferManager.h
        include/CircularBufferManagerWrapper.h
        src/CircularBuffer.cc
        src/CircularBufferManager.cc
        src/CircularBufferManagerWrapper.cpp
    )

    qt_add_qml_module(appQtApp
        URI QtApp
        VERSION 1.0
        QML_FILES
            Main.qml
        RESOURCES
            "assets/pointers/Needle.png"
            "assets/dials/DialBg.png"
            "assets/dials/RPMOld.png"
            "assets/dials/SpeedometerOld.png"
            "assets/pointers/NeedleOld.png"
            "assets/images/bgArt.png"
            "assets/images/Hotwheel.png"
    )

    set_target_properties(appQtApp PROPERTIES
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    )

    target_link_libraries(appQtApp
        PRIVATE Qt6::Quick core
    )

    install(TARGETS appQtApp
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
