To run unit tests in a terminal:

1. cmake -B build -S . -DBUILD_GUI=OFF
2. cmake --build build
3. ctest or ./build/unit_tests
