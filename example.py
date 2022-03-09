import mylib
import numpy as np

mylib.print_buffer_info(np.random.rand(3, 3).astype(np.float16))
print()
mylib.print_buffer_info(np.random.rand(3, 3).astype(np.float32))
print()
mylib.print_buffer_info(np.random.rand(3, 3).astype(np.float64))
print()
mylib.print_buffer_info(np.random.rand(3, 3).astype(np.float128))
print()
print(mylib.array_add_value(np.random.rand(3, 5).astype(np.double), np.pi))
