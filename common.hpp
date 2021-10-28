#ifndef COMMON
#define COMMON

using byte = char;


namespace details
{
    void memory_copy(byte *dest, byte *src, int size)
    {
        for (int i = 0; i < size; i++)
            dest[i] = src[i];
    }
    
    template <typename T> struct remove_ref {using type = T;};
    template <typename T> struct remove_ref<T&> {using type = T;};
    template <typename T> struct remove_ref<T&&> {using type = T;};
    
    template <typename T>
    using remove_ref_t = typename remove_ref<T>::type;
}

template <typename T>
void memory_copy_by_addr(T *dest, T *src)
{
    details::memory_copy(
        static_cast<byte*>(static_cast<void*>(dest)), 
        static_cast<byte*>(static_cast<void*>(src)), 
                         sizeof(T));
}

template <typename T>
void memory_copy(T &dest, T &src)
{
    details::memory_copy(
        static_cast<byte*>(static_cast<void*>(&dest)), 
        static_cast<byte*>(static_cast<void*>(&src)), 
                         sizeof(T));
}

template <typename T>
void swap_copy(T &lhs, T &rhs)
{
    int constexpr element_size = sizeof(lhs);
    byte *temp = new byte[element_size];
    
    memory_copy_by_addr(temp, static_cast<byte*>(static_cast<void*>(&lhs)));
    memory_copy_by_addr(&lhs, &rhs);
    memory_copy_by_addr(static_cast<byte*>(static_cast<void*>(&rhs)), temp);
    
    delete[] temp;
}

#endif

