from pathlib import Path
import ctypes


dll_path = Path(__file__).parent / "memory.dll"

memory = ctypes.CDLL(str(dll_path))

memory.allocate_memory.argtypes = [ctypes.c_size_t]
memory.allocate_memory.restype = ctypes.c_void_p

memory.free_memory.argtypes = [ctypes.c_void_p]
memory.free_memory.restype = ctypes.c_int

memory.get_allocation_id.argtypes = [ctypes.c_void_p]
memory.get_allocation_id.restype = ctypes.c_int

memory.write_memory.argtypes = [ctypes.c_int, ctypes.c_size_t, ctypes.c_void_p]
memory.write_memory.restype = ctypes.c_void_p

memory.read_memory.argtypes = [ctypes.c_int, ctypes.c_size_t]
memory.read_memory.restype = ctypes.c_void_p


def validate_address(address):
    if type(address) != int:
        raise TypeError("Address must be a valid integer.")


def validate_data(data, size):
    if type(data) != bytes:
        raise TypeError("Data must be bytes.")

    if len(data) == 0:
        raise ValueError("Data must not be empty.")

    if size > len(data):
        raise ValueError("Size cannot be greater than data length.")


def validate_size(size):
    if type(size) != int:
        raise TypeError("Size must be an integer.") 
   
    if size <= 0:
        raise ValueError("Size must be greater than zero.")
        

def allocate(size): 
    validate_size(size)    

    address = memory.allocate_memory(size)

    return address


def free(address):	
    validate_address(address)
    return memory.free_memory(address)   


def get_id(address):
    validate_address(address)
    return memory.get_allocation_id(address) 


def write(id, size, data):
    validate_size(size)
    validate_data(data, size)
    
    buffer = ctypes.create_string_buffer(data) 
 
    return memory.write_memory(id, size, ctypes.cast(buffer, ctypes.c_void_p))


def read(id, size):
    validate_size(size)
    
    result = memory.read_memory(id, size)
    
    return ctypes.string_at(result, size)
