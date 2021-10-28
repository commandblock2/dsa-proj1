#include "data.hpp"
#include "common.hpp"

template <typename iter>
void insertion_sort(iter const first, iter const last)
{
    using param_type = decltype(*first);
    insertion_sort(first, last, [](param_type lhs, param_type rhs){ return lhs < rhs;});
}


template <typename iter, typename comp>
void insertion_sort(iter const first, iter const last, comp pred)
{
    int constexpr element_size = sizeof(*first);
    using element_type = decltype(*first);
    
    byte *key_space = new byte[element_size];
    
    for (iter i = first + 1; i != last; i++)
    {
        iter j = i - 1;
        memory_copy_by_addr(key_space, to_byte_ptr(&*(i)), element_size);
        
        while (j + 1 != first && pred(*to_ptr<element_type>(key_space), *j))
        {
            memory_copy(*(j + 1), *j);
            j--;
        }
        
        memory_copy_by_addr(to_byte_ptr(&*(j + 1)), key_space, element_size);
    }
    
    delete[] key_space;
}


int main(int argc, char **argv)
{
    using namespace data;
    
    print_data();
    
    insertion_sort(testA, testA + sizeof(testA) / sizeof(testA[0]));
    insertion_sort(testB, testB + sizeof(testB) / sizeof(testB[0]), [](int *lhs, int *rhs){ return *lhs < *rhs;});
    
    print_data(true);
}
