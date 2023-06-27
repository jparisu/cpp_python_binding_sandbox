# PYTHON BINDINGS FROM C++

## Index

- [PYTHON BINDINGS FROM C++](#python-bindings-from-c)
  - [Index](#index)
  - [Tools](#tools)
  - [Performance / utility Test](#performance--utility-test)
    - [Things to test](#things-to-test)
  - [ChatGPT opinion](#chatgpt-opinion)
  - [ToDo](#todo)

---

## Tools

- **SWIG**
  - PROS
    - multi language
  - CONS
    - automatic memory management
    - very hard to become expert

- **Cython**
  - PROS
    - custom memory management
  - CONS
    - more code to write
    - duplicated headers

- **Python/C API**
  - C library to use Python objects

- **ctypes**
  - Python module to use C++ data types and pointers

- **Boost.Python**
  - CONS
    - all boost environment behind

- **pybind11**
  - similar to boost but without boost dependency
  - PROS
    - easy to use

---

## Performance / utility Test

### Things to test

1. Std Header with implementation
   1. function
   2. class
   3. variable
   4. macros

2. Header + source
   1. function
   2. class
   3. variable

3. Linking headers

4. Templates
   1. functions
   2. classes

5. Data Types
   1. int
   2. string
   3. vector
   4. map
   5. array
   6. ptr
   7. shared_ptr
   8. unique_ptr
   9. class

6. Enumerations

7. Inherit and override virtual methods

8. Copies to pass values from py to c++
    1. get as value
    2. get as ref
    3. get as rvalue
    4. get as ptr
    5. get as shared-ptr
    6. get as shared-ptr ref
    7. get as unique-ptr

9. Pass values from c++ to python
    1. get as value
    2. get as ref
    3. get as rvalue
    4. get as ptr
    5. get as shared-ptr
    6. get as shared-ptr ref
    7. get as unique-ptr

10. Pass py object
    1. as string
    2. as bytes
    3. as object

---

## ChatGPT opinion

- SWIG:
  - Pros:
    - Supports multiple programming languages, including Python. 0
    - Handles a wide range of C++ features and complex class hierarchies. 7
  - Cons:
    - Can have a steep learning curve, especially for complex projects. -7
    - Requires additional effort for configuring and setting up the build process. -4
    - Generated wrapper code may not always be as clean and Pythonic as other tools. -3

- CPython:
  - Pros:
    - It is the official Python interpreter and C API, ensuring compatibility. 1
    - Provides a low-level interface for extending Python with C or C++ code.
    - Allows fine-grained control over the Python runtime and object management.
  - Cons:
    - Requires a deep understanding of the Python/C API, which can be complex.
    - Involves manual memory management and reference counting.
    - Writing bindings using the CPython API can be more verbose and error-prone.

- Python/C API:
  - Pros:
    - Offers direct access to the Python runtime, allowing deep integration.
    - Enables high-performance and fine-grained control over the Python interpreter.
  - Cons:
    - Requires in-depth knowledge of the Python/C API and its memory management.
    - Writing bindings using the C API can be challenging and prone to errors.
    - Can be more time-consuming and less convenient compared to higher-level tools.

- ctypes:
  - Pros:
    - Comes with Python by default, requiring no additional dependencies.
    - Allows calling C/C++ functions from Python without the need for compilation.
    - Simple and straightforward to use for simple use cases and small projects.
  - Cons:
    - Limited support for C++ features and handling of complex C++ classes.
    - Manual handling of memory management and conversions between C++ and Python data types.
    - Performance overhead due to the dynamic nature of ctypes.

- Boost.Python:
  - Pros:
    - Offers a rich and intuitive interface for exposing C++ classes and functions to Python.
    - Excellent support for C++ features, including STL containers.
    - Provides automatic conversions between C++ and Python types.
  - Cons:
    - Requires installing and configuring the Boost libraries.
    - More complex compared to other tools, especially for beginners.
    - Build system integration may need extra effort.

- pybind11:
  - Pros:
    - Lightweight and header-only, making it easy to integrate with existing projects.
    - Simplifies the process of creating Python bindings with a clean and modern syntax.
    - Supports a wide range of C++ features, including STL containers and smart pointers.
  - Cons:
    - Requires understanding C++ template metaprogramming concepts.
    - Building and linking the project may require additional configuration.
    - Documentation may not cover all edge cases.

---

## ToDo

Install the result library created by pbind_pybind11: `object_with_bytes.cpython-310-x86_64-linux-gnu.so`.
So far, to link with pbind_pybind11 result library, it must be added `.../build/pbind_pybind11` to `PYTHONPATH`

```sh
export PYTHONPATH="$PYTHONPATH:/home/eprosima/projects/current/poc/python_binding/build/pbind_pybind11"
export PYTHONPATH="$PYTHONPATH:/home/eprosima/projects/current/poc/python_binding/build/pbind_capi/src/pbind_capi"
```
