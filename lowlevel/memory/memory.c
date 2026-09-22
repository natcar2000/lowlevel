#include <stddef.h>
#include <stdlib.h>


#ifdef _WIN32
    #define API __declspec(dllexport)
#else
    #define API
#endif


API void *allocate_memory(size_t size)
{   
    if(size == 0)
    {
        return NULL;
    }
   
    void *memory = malloc(size);
    
    if(memory == NULL)
    {
        return NULL;
    }

    return memory;
}
