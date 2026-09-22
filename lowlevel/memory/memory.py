import ctypes


memory = ctypes.CDLL("./memory.dll")

memory.allocate_memory.argtypes = [ctypes.c_size_t]
memory.allocate_memory.restype = ctypes.c_void_p


def allocate(size):    
   address = memory.allocate_memory(size)
   return address
