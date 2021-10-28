#include "data.hpp"
#include "common.hpp"

template <typename iter>
void rank_sort(iter const first, iter const last)
{
    using param_type = decltype(*first);
    rank_sort(first, last, [](param_type lhs, param_type rhs){ return lhs < rhs;});
}


template <typename iter, typename comp>
void rank_sort(iter const first, iter const last, comp pred)
{
    int constexpr element_size = sizeof(*first);
    int const length = last - first;
    using element_type = decltype(*first);
    
    int *rank = new int[length];
    for (int i = 0; i < length; i++)
        rank[i] = 0;
    
    for (int i = 1; i < length; i++)
    {
        int greater_than = 0;
        
        for (int j = 0; j < i; j++)
            pred(*(first + i), *(first + j)) && (greater_than++, rank[j]++);
        
        rank[i] = i - greater_than;
    }
    
    auto *temp = new remove_ref_t<element_type>[length];
    
    for (int i = 0; i < length; i++)
        memory_copy(temp[rank[i]], *(first + i));
    
    delete[] rank;
    
    for (int i = 0; i < length; i++)
        memory_copy(*(first + i), temp[i]);
    
    delete[] temp;
}


int main(int argc, char **argv)
{
    using namespace data;
    
    print_data();
    
    rank_sort(testA, testA + sizeof(testA) / sizeof(testA[0]));
    rank_sort(testB, testB + sizeof(testB) / sizeof(testB[0]), [](int *lhs, int *rhs){ return *lhs < *rhs;});
    
    print_data(true);
}
