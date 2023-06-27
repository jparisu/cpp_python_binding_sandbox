# cpp_python_binding_sandbox

Several colcon packages that bind a dummy C++ library to use it from Python in a way that data shared is not copied.

It implements a manual [test](pbind_test/pbind_test/Test_easy_vector.py) executable that shows different cases creating objects in C++ and/or python and checking the access to them from C++ and/or Python.

It uses several methods to bind the C++ library to use it from Python:

- [Python/C API](https://docs.python.org/3/c-api/index.html).
- [ctypes](https://docs.python.org/3/library/ctypes.html).
- [pybind11](https://github.com/pybind/pybind11).
- [SWIG](https://www.swig.org/).

## Struct

This repository is divided in several colcon packages:

- **pbind_cpp**: Dummy C++ library with a type `Bytes` and functions to create, print and modify it.
- **pbind_test**: Library with a Python executable and import files that test to send objects to and from C++ and check if the internal memory has been copied or referenced.
- **pbind_capi**: Binding library from `pbind_cpp` to Python using [Python/C API](https://docs.python.org/3/c-api/index.html).
- **pbind_ctypes**: Binding library from `pbind_cpp` to Python using [ctypes](https://docs.python.org/3/library/ctypes.html).
- **pbind_pybind11**: Binding library from `pbind_cpp` to Python using [pybind11](https://github.com/pybind/pybind11).
- **pbind_swig**: Binding library from `pbind_cpp` to Python using [SWIG](https://www.swig.org/).

## Dependencies

It requires `cmake_utils` and `py_utils` libraries: <https://github.com/eProsima/dev-utils>.

## Run it

> ⚠️ this repo is a sandbox for manual testing different libraries.
> It is not meant to be run as it is, but to run it manually changing some values and checking the output.
> Use at your own risk 😏

```sh
# Download workspace
mkdir -p src
git clone https://github.com/jparisu/cpp_python_binding_sandbox src/

# Source dev-utils
source <dev-utils-path>/install/setup.bash

# Build colcon workspace
colcon build --packages-up-to pbind_test

# Source this workspace (some dependencies are not correctly install with python, so is done manually)
source install/setup.bash
export PYTHONPATH="$PYTHONPATH:./build/pbind_pybind11:./install/pbind_capi/lib/"

# Run test manually and read/interpret output
python3 src/pbind_test/pbind_test/Test_easy_vector.py
```

## Conclusions

**So far** the conclusions got from this tests are:

- `ctypes` gives a way to pass C++ *pointer like* chunk of memory to Python, that can read it an interpret without copy as a `memoryview`.
- `ctypes` gives a way to pass Python `memoryview` chunk of memory (available without copy from a `bytes` or `bytearray`) to C++ read as a *pointer like*.

### Other conclusions

- **SWIG**
  - Very hard/long documentation.
  - It is the most automatic one, allowing to increase the library without modifying the `.i` files.
  - Not found a way to do a non copy transition.
- **PyBind11**
  - Probably the most easy one.
  - It does not give access to low level methods, thus zero-copy was unreachable.
- **Python/C API**
  - *Abandon all hope, ye who enter here.*
  - Take your time to read the documentation and read examples, and to debug why in hell nothing works as expected.
  - Funny to know how Python insights works though.
- **ctypes**
  - Easy and intuitive
  - Long to write each parser, as you should copy every function and set every argtypes and restype.
  - 🏆
- **Python**
  - `bytes` and `bytearray` have no way (that I found) to be created without copying the underneath buffer that comes from C++.
  - `memoryview` represents a pointer to a chunk of data, and can be set to data from C++ or from Python, and be read in both.
    Thus, it seems like the way to go.
