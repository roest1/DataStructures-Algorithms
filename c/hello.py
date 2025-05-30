import ctypes

lib = ctypes.CDLL("./libarraymath.so")

lib.add.argtypes = (ctypes.c_int, ctypes.c_int)
lib.add.restype = ctypes.c_int

x = lib.add(10,20)
print(f'10+20={x}')
