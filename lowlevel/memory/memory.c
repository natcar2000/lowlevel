#include <string.h>
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
    void *copy;
    struct Allocation *next;
} Allocation;


typedef struct Queue
{
    Allocation *first;
    Allocation *last;
} Queue;


int create_node(void *memory, size_t size);
int generate_id(void);
API void *allocate_memory(size_t size);
API int free_memory(void *memory); 
API int get_allocation_id(void *memory);
Allocation *return_node(int id);
int validate(size_t size, size_t allocation_size, const void *data);
API void *write_memory(int id, size_t size, const void *data);
API void *read_memory(size_t size, const void *data);

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
    int status = 1;
    
    Allocation *previous = NULL;
    Allocation *node_to_remove = queue.first;

    if(node_to_remove == NULL)
    {
        return status;
    }
      
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
            free(node_to_remove->copy);
            free(node_to_remove);
            
            status = 0;
            return status;
        }
          
        previous = node_to_remove;
        node_to_remove = node_to_remove->next;
    }    
    
    return status;
}


API int get_allocation_id(void *memory)
{
    Allocation *node = queue.first;
    
    if(node == NULL)
    {
        return 1;
    }
    
    while(node != NULL)
    {
        if(node->memory == memory)
        {
            return node->id;
        }
        node = node->next;
    }
    
    return 1;
}


Allocation *return_node(int id)
{
    Allocation *node = queue.first;
    
    if(node == NULL)
    {
        return NULL;
    }
    
    while(node != NULL)
    {
        if(node->id == id)
        {
            return node;
        }
        node = node->next;
    }
    
    return NULL;
}


int validate(size_t size, size_t allocation_size, const void *data)
{
    if(size == 0 || data == NULL)
    {
        return 0;
    }
    
    if(size > allocation_size)
    {
        return 0;
    }

    return 1;
}


API void *write_memory(int id, size_t size, const void *data)
{
    Allocation *node = return_node(id);
    
    if(node == NULL)
    {
        return NULL;
    }
    
    int validation = validate(size, node->size, data);
    
    if(validation == 1)
    {
        
        memcpy(node->memory, data, size);
        return node->memory;
    }
    
    return NULL;
}


API void *read_memory(int id, size_t size, const void *data)
{
    Allocation *node = return_node(id);
    
    if(node == NULL)
    {
        return NULL;
    }
    
    int validation = validate(size, node->size, data);
    
    if (validation == 1)
    {
        if(node->copy != NULL)
        {
            free(node->copy);
        }
        
        void *copy = malloc(size);
        
        if(copy == NULL)
        {
            return NULL;
        }
        
        memcpy(copy, data, size);
        
        node->copy = copy;
        
        return copy;
    }
    
    return NULL;
}
