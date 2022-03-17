from functools import reduce
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

shape = np.random.randint(1, 10, size=np.random.randint(3, 10))
axis = np.random.choice(range(len(shape)), size=1)[0]
in_arr = np.random.randn(reduce(lambda a, b: a * b, shape, 1)).reshape(shape)
print()
print("in_arr shape:", in_arr.shape)
print("reduce axis:", axis)
out = mylib.arg_min(in_arr, axis)
out_np = np.argmin(in_arr, axis)
print("output shape:", out.shape)
print("argmin ok:", np.alltrue(out == out_np))
