set -e  # Exit on any command failure

echo "[0/3] Removing previous build files"
rm -rf build

echo "[1/3] Configuring project with BUILD_GUI=OFF..."
cmake -B build -S . -DBUILD_GUI=OFF

echo "[2/3] Building project..."
cmake --build build

echo "[3/3] Running tests..."
cd build/QtApp && ctest --output-on-failure

cd ../../QtApp/test/build/Debug
rm -rf "empty.csv" "malformed.csv" "valid.csv"
cd ....