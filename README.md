# lowlevel

A low-level memory management library for Python, implemented in **C**
and integrated through `ctypes`.

`lowlevel` provides operations for allocating, freeing, identifying,
writing, and reading raw memory blocks.

## Version

**v1.0.0**

## Features

-   Dynamic memory allocation
-   Memory deallocation
-   Allocation identification through numeric IDs
-   Writing raw bytes to memory
-   Reading raw bytes from memory
-   Internal allocation management
-   Python/C integration through `ctypes`
-   DLL compilation
-   Binary data handling

## Architecture

``` text
Python
   │
   │ ctypes
   ▼
memory.dll
   │
   ▼
C code
   │
   ├── malloc()
   ├── free()
   ├── memcpy()
   ├── Allocation
   └── Queue
```

Each allocated memory block receives a numeric ID that can be used to
locate the allocation.

## Python API

### `allocate(size)`

Allocates `size` bytes of memory and returns its address.

``` python
address = allocate(1024)
```

### `free(address)`

Frees the memory associated with an address.

``` python
free(address)
```

### `get_id(address)`

Returns the ID associated with an allocation.

``` python
allocation_id = get_id(address)
```

### `write(id, size, data)`

Writes raw `bytes` data to the memory associated with an ID.

``` python
data = b"Hello World!"
write(id, len(data), data)
```

### `read(id, size)`

Reads `size` bytes from an allocation and returns them as Python
`bytes`.

``` python
data = read(id, len(data))
print(data)
```

## Example

``` python
data = b"Hello World!"
address = allocate(len(data))

try:
    allocation_id = get_id(address)
    write(allocation_id, len(data), data)
    result = read(allocation_id, len(data))
    print(result)
finally:
    free(address)
```

Output:

``` text
b'Hello World!'
```

## Numeric Data

Because `lowlevel` works with raw memory, numeric values can be
converted to bytes before being stored.

``` python
value = 123456
data = value.to_bytes(4, byteorder="little", signed=True)

address = allocate(4)

try:
    allocation_id = get_id(address)
    write(allocation_id, 4, data)
    result = read(allocation_id, 4)
    value = int.from_bytes(result, byteorder="little", signed=True)
    print(value)
finally:
    free(address)
```

## Audio Test

`lowlevel` was also tested with audio data. An audio file was loaded as
bytes, stored in C-managed memory, read back through the library, and
successfully reproduced with `pygame`.

``` text
Audio file → bytes → allocate() → write() → C memory
                                      │
                                      ▼
                              read() → bytes → pygame → Audio
```

This demonstrates that the library can handle arbitrary binary data
without the C layer needing to interpret its semantic type.

## Internal Structure

Each allocation is represented by an `Allocation` node:

``` c
typedef struct Allocation
{
    int id;
    void *memory;
    size_t size;
    void *copy;
    struct Allocation *next;
} Allocation;
```

Allocations are managed through a queue:

``` c
typedef struct Queue
{
    Allocation *first;
    Allocation *last;
} Queue;
```

## Compilation

Using GCC/MinGW-w64:

``` bash
gcc -shared -Wall -Wextra -o memory.dll memory.c
```

The generated `memory.dll` must be available to the Python application.

## Technologies

-   C
-   Python
-   `ctypes`
-   GCC / MinGW-w64
-   DLL
-   pygame

## Status

**v1.0.0 --- Completed**

-   [x] Memory allocation
-   [x] Memory deallocation
-   [x] Allocation IDs
-   [x] Byte writing
-   [x] Byte reading
-   [x] Python/C integration
-   [x] Functional DLL
-   [x] Numeric data testing
-   [x] Audio data testing
-   [x] Successful audio playback

## Project Objective

`lowlevel` was developed as a practical project for studying **low-level
programming, memory management, pointers, data structures, C, and
Python/C integration**.

It also provides a foundation for future applications that require
direct manipulation of binary data in memory.

------------------------------------------------------------------------

**lowlevel v1.0.0**

Developed by **Natanael Rodrigues**.
