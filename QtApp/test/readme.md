To run unit tests use the scripts in .scripts or through the command line:

1. cmake -B build -S . -DBUILD_GUI=OFF
2. cmake --build build
3. ctest or ./build/unit_tests
