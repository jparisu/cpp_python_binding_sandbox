#pragma once

#include <cstdint>
#include <cstdio>

#ifdef __cplusplus
extern "C" {
#endif

using Byte = uint8_t;

struct Bytes
{
    Byte* bytes = nullptr;
    size_t size = 0;
};

Byte* get_bytes(Bytes* b)
{
    return b->bytes;
}

size_t get_size(Bytes* b)
{
    return b->size;
}

Bytes* to_python(size_t size);
Bytes* from_ptr(Byte* bytes, size_t size);
// bool are_same_bytes(Bytes* bytes1, Bytes* bytes2);

void print_obj(Bytes* bytes);
void modify_obj(Bytes* bytes);

#ifdef __cplusplus
}
#endif
