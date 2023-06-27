
#include <iostream>
#include <stdexcept>

#include <pbind_cpp/easy_bytes.hpp>

char new_char()
{
    static int c = 1;
    return ' ' + (c++ % ('~' - ' '));
}

char add_1_to_char(char& c)
{
    c = ' ' + ( (c + 1 - ' ') % ('~' - ' ') );
    return c;
}

Bytes* to_python(size_t size)
{
    std::cout << "START to_python: " << size << std::endl;

    if (!size)
    {
        std::cout << "ERROR: to_python called with 0." << std::endl;
        throw std::invalid_argument("to_python 0");
    }

    Bytes* b = new Bytes();
    b->bytes = (Byte*) malloc(size * sizeof(Byte));

    for (int i=0; i<size; i++)
    {
        b->bytes[i] = new_char();
    }

    b->size = size;

    print_obj(b);
    std::cout << "FINISH to_python." << std::endl;

    return b;
}

Bytes* from_ptr(Byte* bytes, size_t size)
{
    std::cout << "START from_ptr: " << bytes << "  " << size << std::endl;
    Bytes* b = new Bytes();
    b->bytes = bytes;
    b->size = size;
    print_obj(b);
    std::cout << "FINISH from_ptr." << std::endl;

    return b;
}

bool are_same_bytes(Bytes* bytes1, Bytes* bytes2)
{
    std::cout << "START are_same_bytes." << std::endl;
    print_obj(bytes1);
    print_obj(bytes2);

    int equal = 0;

    if (bytes1 == bytes2)
    {
        std::cout << "Same object." << std::endl;
        equal = 1;
    }
    else
    {
        std::cout << "Not Same object." << std::endl;
        equal = -1;
    }

    if (bytes1->bytes == bytes2->bytes)
    {
        std::cout << "Same internal object." << std::endl;
        equal = 1;
    }
    else
    {
        std::cout << "Not same internal object." << std::endl;
        equal = -1;
    }

    if (bytes1->size != bytes2->size)
    {
        std::cout << "Not same size." << std::endl;
        equal = -1;
    }

    for (size_t i = 0; i < bytes1->size && equal == 0; i++)
    {
        if (bytes1->bytes[i] != bytes2->bytes[i])
        {
            equal = -1;
            break;
        }
    }

    if (equal == 1)
    {
        std::cout << "Same values." << std::endl;
    }
    else
    {
        std::cout << "NOT Same values." << std::endl;
    }

    std::cout << "FINISH are_same_bytes." << std::endl;

    return equal == 1;
}

void print_obj(Bytes* bytes)
{
    if (!bytes)
    {
        std::cout << "ERROR: print_obj called with null." << std::endl;
        throw std::invalid_argument("print_obj null");
    }

    if (!bytes->bytes)
    {
        std::cout << "ERROR: print_obj called with internal null." << std::endl;
        throw std::invalid_argument("print_obj internal null");
    }

    std::cout << "{" << std::endl << "  BYTES" << std::endl;
    std::cout
        << "  " << static_cast<const void*>(bytes)
        << "   with size: " << bytes->size
        << "   with internal value: " << static_cast<const void*>(bytes->bytes)
        << std::endl << "  ";

    for (size_t i = 0; i < bytes->size; i++)
    {
        std::cout << "  "
            << bytes->bytes[i] << "("
            << static_cast<int>(bytes->bytes[i]) << ")"
            << "  ";
    }
    std::cout << std::endl << "}" << std::endl;
}

void modify_obj(Bytes* bytes)
{
    for (int i=0; i<bytes->size; i++)
    {
        add_1_to_char((char&)bytes->bytes[i]);
    }
}
