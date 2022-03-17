from functools import reduce

import numpy as np

import mylib


def test_arg_min():
    for _ in range(10):
        shape = np.random.randint(1, 10, size=np.random.randint(3, 10))
        axis = np.random.choice(range(len(shape)), size=1)[0]
        in_arr = np.random.randn(reduce(lambda a, b: a * b, shape, 1)).reshape(shape)
        out = mylib.arg_min(in_arr, axis)
        out_np = np.argmin(in_arr, axis)
        if not np.alltrue(out == out_np):
            raise RuntimeError("incorrect result")
