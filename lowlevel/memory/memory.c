#include <stddef.h>
#include <stdlib.h>


#ifdef _WIN32
    #define API __declspec(dllexport)
#else
    #define API
#endif


typedef struct Allocation
{
    int id;
    void *memory;
    size_t size;
    struct Allocation *next;
} Allocation;


typedef struct Queue
{
    Allocation *first;
    Allocation *last;
} Queue;


int create_node(void *memory, size_t size);
int generate_id(void);
void *allocate_memory(size_t size);
int free_memory(void *memory); 

Queue queue = {NULL, NULL};


int create_node(void *memory, size_t size)
{
    Allocation *node = malloc(sizeof(Allocation));

    if(node == NULL)
    {
        free(memory);
        return 1;
    }

    node->id = generate_id();
    node->memory = memory;
    node->size = size;
    node->next = NULL;

    if(queue.first == NULL && queue.last == NULL)
    {
        queue.first = node;
        queue.last = node;
    }
    else
    {
        Allocation *last_node = queue.last;
        queue.last = node;
        last_node->next = node;
    }

    return 0;
}



int generate_id(void)
{
    int id;
    
    id = rand() % 100000;

    Allocation *node = queue.first; 
    
    while(node != NULL)
    {
        if(node->id == id)
        {
                id = generate_id();
        }
        node = node->next;
    }

    return id;
}


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

    int allocation = create_node(memory, size);
    if(allocation != 0)
    {
        return NULL;
    }
            
    return memory;
}


API int free_memory(void *memory)
{
    int status = 0;
    
    Allocation *previous = NULL;
    Allocation *node_to_remove = queue.first;
      
    while(node_to_remove != NULL)
    {
        if(node_to_remove->memory == memory)
        {
            if(previous == NULL)
            {
                queue.first = queue.first->next;
            }
            
            else
            {
                previous->next = node_to_remove->next;
            }
            
            if(queue.first == NULL)
            {
                queue.last = NULL;
            }
            
            if(node_to_remove == queue.last)
            {
                queue.last = previous;
            }
            
            free(node_to_remove->memory);
            free(node_to_remove);
            
            status = 1;
            return status;
        }
          
        previous = node_to_remove;
        node_to_remove = node_to_remove->next;
    }    
    
    return status;
}
