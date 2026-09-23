#include <stddef.h>
#include <stdlib.h>


#ifdef _WIN32
    #define API __declspec(dllexport)
#else
    #define API
#endif


typedef struct 
{
    int id;
    void *memory;
    size_t size;
    struct Allocation *next;
} Allocation;


typedef struct 
{
    Allocation *first;
    Allocation *last;
} Queue;


int create_node(void *memory, size_t size);
int generate_id(void);


Queue *queue = malloc(sizeof(Queue));
queue->first = NULL;
queue->last = NULL;


int create_node(void *memory, size_t size, Queue *queue)
{
    Allocation *node = malloc(sizeof(Allocation));

    if(node == NULL)
    {
        free(memory);
        return 1;
    }

    node->id = generate_id(queue);
    node->memory = memory;
    node->size = size;
    node->next = NULL;

    if(queue->first == NULL && queue->last == NULL)
    {
        queue->first = node;
        queue->last = node;
    }
    else
    {
        Allocation *last_node = queue->last;
        queue->last = node;
        last_node->next = node;
    }

    return 0;
}



int generate_id(Queue *queue)
{
    int id;
    
    id = rand() % 100000;

    Allocation *node = queue->first; 
    
    while(node != NULL)
    {
        if(node->id == id)
        {
                id = generate_id(queue);
        }
        node = node->next;
    }

    return id;
}


API void *allocate_memory(size_t size, Queue *queue)
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

    int allocation = create_node(memory, size, queue);
    if(allocation != 0)
    {
        return NULL;
    }
            
    return memory;
}
