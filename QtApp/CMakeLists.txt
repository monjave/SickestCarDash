cmake_minimum_required(VERSION 3.16)

# project(QtApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appQtApp
    main.cpp
)

qt_add_qml_module(appQtApp
    URI QtApp
    VERSION 1.0
    QML_FILES
        Main.qml
    RESOURCES
    "images/Needle.png"
    "images/RPM.png"
    "images/Speedometer.png"
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQtApp PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQtApp
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appQtApp
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appQtApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


# Optional: Allow disabling test build
option(BUILD_TESTING "Build unit tests" ON)

if(BUILD_TESTING)
    enable_testing()
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    )
    FetchContent_MakeAvailable(googletest)

    # Add your core library (src + include)
    add_library(core
        src/CircularBuffer.cc
        src/CircularBufferManager.cc
    )
    target_include_directories(core PUBLIC include)

    # Test target
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