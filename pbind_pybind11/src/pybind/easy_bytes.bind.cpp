// Copyright 2023 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#include <pybind11/pybind11.h>

#include <cstddef>
#include <pbind_cpp/easy_bytes.hpp>

namespace py = pybind11;

py::bytes to_python_bytes_from_obj(Bytes* obj)
{
    return py::bytes(reinterpret_cast<const char*>(obj->bytes), obj->size);
}

py::bytes to_python_bytes(size_t size)
{
    Bytes* b = to_python(size);
    return to_python_bytes_from_obj(b);
}

// Bytes* from_python_bytearray(py::bytearray& b)
// {
//     Bytes* b = to_python(size);
//     return to_python_bytes_from_obj(b);
// }


PYBIND11_MODULE(easy_bytes, m)
{
    m.doc() = "pybind11 easy_bytes";
    m.def("to_python", &to_python);
    m.def("print_obj", &print_obj);
    m.def("modify_obj", &modify_obj);
    m.def("to_python_bytes", &to_python_bytes);
    m.def("to_python_bytes_from_obj", &to_python_bytes_from_obj);
    m.def("from_python", [](py::bytes b){});
    py::class_<Bytes>(m, "Bytes");
};
