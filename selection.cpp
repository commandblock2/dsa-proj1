#include "data.hpp"
#include "common.hpp"

template <typename iter>
void selection_sort(iter const first, iter const last)
{
    using param_type = decltype(*first);
    selection_sort(first, last, [](param_type lhs, param_type rhs){ return lhs < rhs;});
}


template <typename iter, typename comp>
void selection_sort(iter const first, iter const last, comp pred)
{
    for (iter i = first; i != last - 1; i++)
    {
        iter min_index = i;
        
        for (iter j = i + 1; j != last; j++)
            if (pred(*j, *min_index))
                min_index = j;
            
        swap_copy(*i, *min_index);
    }
}


int main(int argc, char **argv)
{
    using namespace data;
    
    print_data();
    
    selection_sort(testA, testA + sizeof(testA) / sizeof(testA[0]));
    selection_sort(testB, testB + sizeof(testB) / sizeof(testB[0]), [](int *lhs, int *rhs){ return *lhs < *rhs;});
    
    print_data(true);
}
