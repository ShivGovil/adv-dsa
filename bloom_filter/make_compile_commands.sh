rm -rf build/ .cache/
cmake -B build .
cp build/compile_commands.json .
cmake --build build --verbose
