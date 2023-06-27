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

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <pbind_cpp/easy_bytes.hpp>

static
PyObject *
to_python_wrapper(PyObject *self, PyObject *args)
{
    size_t size;
    if (!PyArg_ParseTuple(args, "n", &size))
    {
        return NULL;
    }

    Bytes* b = to_python(size);
    PyObject* py_obj = PyCapsule_New(b, NULL, NULL);
    return py_obj;
}

static
PyObject *
print_obj_wrapper(PyObject *self, PyObject *args)
{
    PyObject* py_obj;
    if (!PyArg_ParseTuple(args, "O", &py_obj))
    {
        return NULL;
    }

    // Extract the pointer to the custom object from the capsule
    Bytes* obj = (Bytes*)PyCapsule_GetPointer(py_obj, NULL);
    print_obj((Bytes*)obj);
    Py_RETURN_NONE;
}

static
PyObject *
modify_obj_wrapper(PyObject *self, PyObject *args)
{
    PyObject* py_obj;
    if (!PyArg_ParseTuple(args, "O", &py_obj))
    {
        return NULL;
    }

    // Extract the pointer to the custom object from the capsule
    Bytes* obj = (Bytes*)PyCapsule_GetPointer(py_obj, NULL);
    modify_obj((Bytes*)obj);
    Py_RETURN_NONE;
}

// static
// PyObject *
// from_python_wrapper(PyObject *self, PyObject *args)
// {
//     char *command;
//     Py_ssize_t size;
//     int sts;

//     // if (PyArg_ParseTuple(args, "s", &command))
//     // {
//     //     sts = from_python(command);
//     // }
//     if (PyArg_ParseTuple(args, "s#", &command, &size))
//     {
//         Bytes b;
//         b.bytes = (Byte*)command;
//         b.size = size;

//         sts = from_python(&b);
//         // PyMem_Free(command);
//     }
//     else
//     {
//         return NULL;
//     }

//     return PyLong_FromLong(sts);
// }

PyObject *
to_python_bytes_from_obj_aux_(Bytes* bytes)
{
    return PyBytes_FromStringAndSize((const char*)bytes->bytes, bytes->size);
}

static
PyObject *
to_python_bytes_wrapper(PyObject *self, PyObject *args)
{
    size_t size;
    if (!PyArg_ParseTuple(args, "n", &size))
    {
        return NULL;
    }

    Bytes* b = to_python(size);
    return to_python_bytes_from_obj_aux_(b);
}

static
PyObject *
to_python_bytes_from_obj_wrapper(PyObject *self, PyObject *args)
{
    PyObject* py_obj;
    if (!PyArg_ParseTuple(args, "O", &py_obj))
    {
        return NULL;
    }

    // Extract the pointer to the custom object from the capsule
    Bytes* obj = (Bytes*)PyCapsule_GetPointer(py_obj, NULL);

    return to_python_bytes_from_obj_aux_(obj);
}

static PyMethodDef easy_bytes_Methods[] = {
    {"to_python", to_python_wrapper, METH_VARARGS, ""},
    {"print_obj", print_obj_wrapper, METH_VARARGS, ""},
    {"modify_obj", modify_obj_wrapper, METH_VARARGS, ""},
    {"to_python_bytes", to_python_bytes_wrapper, METH_VARARGS, ""},
    {"to_python_bytes_from_obj", to_python_bytes_from_obj_wrapper, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef easy_bytes_module = {
    PyModuleDef_HEAD_INIT,
    "easy_bytes",
    "",
    -1,
    easy_bytes_Methods,
    NULL,
    NULL,
    NULL,
    NULL
};

PyMODINIT_FUNC PyInit_pbind_capi(
    void)
{
    return PyModule_Create(&easy_bytes_module);
}
