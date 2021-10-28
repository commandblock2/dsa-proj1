#ifndef DATA
#define DATA

#include <cstdio>

namespace data
{
    int testA[] = {1, 62, 81, 0, 23, 55, 76, 87, 20, 54, 65, 76, 1};
    int testB[][2] = {{71, 2}, {64, 8}, {31, 56}, {98, 1}, {3, 6}, {59, 837}, {49, 58}, {61, 8}};
    
    void print_data(bool print_sorted = false)
    {
        printf("data %s sort\n", print_sorted ? "after" : "before");
        
        for (auto i : testA)
            printf("%d ", i);
        printf("\n");
        
        for (auto i : testB)
            printf("(%d, %d) ", i[0], i[1]);
        printf("\n");
    }
}

#endif
