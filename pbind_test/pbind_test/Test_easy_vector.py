
from py_utils.debugging.debug_utils import debug_variable_introspection, debug_separator
from py_utils.logging.log_utils import activate_debug, logger
from ctypes import create_string_buffer

def main():

    activate_debug()

    from pbind_test.pybind import pybind
    from pbind_test.swig import swig
    from pbind_test.capi import capi
    from pbind_test.c_types import c_types

    # modules = [swig]
    modules = {
        "ctypes": c_types,
        # "pybind": pybind,
        # "swig": swig,
        # "capi": capi,
    }

    tests = [
        # test__to_python,
        # test__to_python_and_print,
        # test__to_python_bytes,
        # test__reference,
        # test__reference_memoryview,
        # test__reference_bytearray,
        # test__from_bytearray,
        test__from_memoryview
    ]

    for test in tests:
        for module in modules.items():

            debug_separator()
            test(module[1], module[0])

        debug_separator()


def test__to_python(module, module_name):

    print(f'--- TEST - TO PYTHON --- module : <{module_name}>')

    to_python_result = module.to_python(3)
    debug_variable_introspection(to_python_result)


def test__to_python_and_print(module, module_name):

    print(f'--- TEST - TO PYTHON & PRINT --- module : <{module_name}>')

    to_python_result = module.to_python(5)
    module.print_obj(to_python_result)


def test__to_python_bytes(module, module_name):

    print(f'--- TEST - TO PYTHON BYTES --- module : <{module_name}>')

    to_python_result = module.to_python_bytes(3)

    if type(to_python_result) != bytes:
        print('ERROR: no bytes types')
    else:
        print('HURRAY: bytes types')
    print(to_python_result)


def test__reference(module, module_name):

    print(f'--- TEST - REFERENCE --- module : <{module_name}>')

    cpp_obj = module.to_python(3)
    py_bytes = module.to_python_bytes_from_obj(cpp_obj)

    module.modify_obj(cpp_obj)
    module.print_obj(cpp_obj)
    print(f'== PY BYTES after modifying: <{bytes(py_bytes)}>')


def test__reference_memoryview(module, module_name):

    print(f'--- TEST - REFERENCE MEMORYVIEW --- module : <{module_name}>')

    cpp_obj = module.to_python(3)
    py_mv = module.to_python_memoryview_from_obj(cpp_obj)
    debug_variable_introspection(py_mv)

    module.modify_obj(cpp_obj)

    module.print_obj(cpp_obj)
    print(f'== PY BYTES after modifying: <{bytes(py_mv)}>')

    # Cannot modify values
    py_mv[0] = 70


def test__reference_bytearray(module, module_name):

    print(f'--- TEST - REFERENCE BYTEARRAY --- module : <{module_name}>')

    cpp_obj = module.to_python(3)
    py_mv = module.to_python_bytearray_from_obj(cpp_obj)
    debug_variable_introspection(py_mv)

    module.modify_obj(cpp_obj)

    module.print_obj(cpp_obj)
    print(f'== PY BYTES after modifying: <{bytes(py_mv)}>')

    py_mv[0] = py_mv[1]

    module.print_obj(cpp_obj)
    print(f'== PY BYTES after modifying: <{bytes(py_mv)}>')


def test__from_memoryview(module, module_name):

    print(f'--- TEST - FROM BYTEARRAY --- module : <{module_name}>')

    b = bytearray(b'!0aZ~')
    mv = memoryview(b)

    cpp_obj = module.from_python_memoryview(mv)

    module.print_obj(cpp_obj)
    print(f'== PY BYTES after modifying: <{bytes(mv)}>')

    # Modify in python
    b[0] += 1
    module.print_obj(cpp_obj)
    print(f'== PY BYTES after modifying: <{bytes(mv)}>')

    # Modify in C++
    module.modify_obj(cpp_obj)
    module.print_obj(cpp_obj)
    print(f'== PY BYTES after modifying: <{bytes(mv)}>')


if __name__ == '__main__':
    main()
