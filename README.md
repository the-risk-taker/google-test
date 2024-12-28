# Google Test Notes

Some [notes](<Google Test Notes.md>) about Google Test with examples `/examples`.

## Setup and build

Setup project and build with CMake:

```shell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
```

## Explore

Look at the `/examples`, then run tests with CTest:

```shell
ctest --test-dir build
```

or run them from `build` dir manually.
