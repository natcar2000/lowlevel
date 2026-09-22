import ctypes


memory = ctypes.CDLL("./memory.dll")

memory.allocate_memory.argtypes = [ctypes.c_size_t]
memory.allocate_memory.restype = ctypes.c_void_p

memory.free_memory.argtypes = [ctypes.c_void_p]
memory.free_memory.restype = None


def allocate(size):    
   address = memory.allocate_memory(size)
   return address


def free(address):
   memory.free_memory(address)
