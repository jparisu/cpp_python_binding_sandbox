
import ctypes
import ctypes.util

from py_utils.debugging.debug_utils import debug_variable_introspection, debug_separator
from py_utils.logging.log_utils import activate_debug, logger


# Define the Bytes struct in Python using ctypes
class Bytes(ctypes.Structure):
    _fields_ = [
        ('bytes', ctypes.POINTER(ctypes.c_uint8)),
        ('size', ctypes.c_size_t),
    ]


# Load the shared library
library_path = ctypes.util.find_library('pbind_cpp')
pbind_cpp_library = ctypes.CDLL(library_path)  # Update with the correct path

# to_python
to_python = pbind_cpp_library.to_python
to_python.argtypes = (ctypes.c_size_t, )
to_python.restype = ctypes.POINTER(Bytes)

# from_ptr
from_ptr = pbind_cpp_library.from_ptr
from_ptr.argtypes = (ctypes.POINTER(ctypes.c_uint8), ctypes.c_size_t)
from_ptr.restype = ctypes.POINTER(Bytes)

# print_obj
print_obj = pbind_cpp_library.print_obj
print_obj.argtypes = (ctypes.POINTER(Bytes),)
print_obj.restype = None

# modify_obj
modify_obj = pbind_cpp_library.modify_obj
modify_obj.argtypes = (ctypes.POINTER(Bytes),)
modify_obj.restype = None

# bytes
get_bytes = pbind_cpp_library.get_bytes
get_bytes.argtypes = (ctypes.POINTER(Bytes),)
get_bytes.restype = ctypes.POINTER(ctypes.c_uint8)

# size
get_size = pbind_cpp_library.get_size
get_size.argtypes = (ctypes.POINTER(Bytes),)
get_size.restype = ctypes.c_size_t


# to_python_bytes
def to_python_bytes(n):
    b = to_python(n)
    return to_python_bytes_from_obj(b)


# to_python_bytes_from_obj
def to_python_bytes_from_obj(obj):
    b = get_bytes(obj)
    size = get_size(obj)
    byte_obj = bytes(ctypes.cast(b, ctypes.POINTER(ctypes.c_uint8 * size)).contents)
    return byte_obj


def to_python_memoryview_from_obj(obj):
    b = get_bytes(obj)
    size = get_size(obj)
    byte_obj = memoryview(ctypes.cast(b, ctypes.POINTER(ctypes.c_uint8 * size)).contents)
    return byte_obj


def to_python_bytearray_from_obj(obj):
    b = get_bytes(obj)
    size = get_size(obj)
    byte_obj = bytearray(ctypes.cast(b, ctypes.POINTER(ctypes.c_uint8 * size)).contents)
    return byte_obj


def from_python_memoryview(mv: memoryview):
    array = ctypes.c_uint8 * len(mv)
    return from_ptr(array.from_buffer(mv), len(mv))
