// Copyright 2022 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

%module swig_easy_bytes

// SWIG helper modules
%include "stdint.i"
%include "std_array.i"
%include "std_string.i"
%include "std_vector.i"

// Definition of internal types
typedef short int16_t;
typedef int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

%{
#include <pbind_cpp/easy_bytes.hpp>
%}

namespace std {
   %template(bytes) vector<uint8_t>;
}

%inline %{
#include <vector>

struct PyBytes : public Bytes {};

// Add the C++ function to_python_bytes.
PyBytes* to_python_bytes(size_t size)
{
    Bytes* b = to_python(size);
    return (PyBytes*)b;
}

std::vector<Byte> to_vector(Bytes* b)
{
    return std::vector<Byte>(b->bytes, b->bytes + b->size);
}

%}

%pythoncode %{
def to_python_bytes_from_obj(b):
    return bytes(to_vector(b))
%}

%include "typemaps.i"  // Include typemaps for converting C++ types to Python.

%typemap(in) PyBytes * (PyBytes temp)
{
    // Convert the Python bytes object to a C++ Bytes struct.
    if (!PyBytes_Check($input))
    {
        PyErr_SetString(PyExc_TypeError, "Expected a bytes object.");
        SWIG_fail;
    }

    $1 = &temp;
    $1->bytes = reinterpret_cast<PyBytes *>(PyBytes_AsString($input));
    $1->size = PyBytes_Size($input);
}

%typemap(argout) PyBytes *
{
    // Convert the C++ Bytes struct to a Python bytes object.
    $result = PyBytes_FromStringAndSize(reinterpret_cast<char *>($1->bytes), $1->size);
}

%apply (PyBytes *ARGOUT) { PyBytes *to_python(size_t) };  // Apply the typemaps to the to_python function.

%include <pbind_cpp/easy_bytes.hpp>


// This forbids to use strings in the whole module
// %begin %{
// #define SWIG_PYTHON_STRICT_BYTE_CHAR
// %}
