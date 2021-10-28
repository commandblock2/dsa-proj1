#ifndef COMMON
#define COMMON

using byte = char;

void __memory_copy(byte *dest, byte *src, int size)
{
    for (int i = 0; i < size; i++)
        dest[i] = src[i];
}
    
template <typename T> struct remove_ref {using type = T;};
template <typename T> struct remove_ref<T&> {using type = T;};
template <typename T> struct remove_ref<T&&> {using type = T;};
    
template <typename T>
using remove_ref_t = typename remove_ref<T>::type;


template <typename T>
byte* to_byte_ptr(T *ptr)
{
    return static_cast<byte*>(static_cast<void*>(ptr));
}

template <typename T>
remove_ref_t<T>* to_ptr(byte *ptr)
{
    return static_cast<remove_ref_t<T>*>(static_cast<void*>(ptr));
}

template <typename T>
void memory_copy_by_addr(T *dest, T *src, int size)
{
    __memory_copy(
        to_byte_ptr(dest), 
        to_byte_ptr(src), 
                         size);
}

template <typename T>
void memory_copy(T &dest, T &src)
{
    __memory_copy(
        to_byte_ptr(&dest), 
        to_byte_ptr(&src), 
                         sizeof(T));
}

template <typename T>
void swap_copy(T &lhs, T &rhs)
{
    int constexpr element_size = sizeof(lhs);
    byte *temp = new byte[element_size];
    
    memory_copy_by_addr(temp, to_byte_ptr(&lhs), element_size);
    memory_copy_by_addr(&lhs, &rhs, element_size);
    memory_copy_by_addr(to_byte_ptr(&rhs), temp, element_size);
    
    delete[] temp;
}

#endif

