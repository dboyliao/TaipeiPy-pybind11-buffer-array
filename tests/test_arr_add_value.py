import numpy as np

import mylib


def test_arr_add_value():
    for _ in range(10):
        shape = np.random.randint(1, 10, size=np.random.randint(3, 10)).tolist()
        in_arr = np.random.rand(*shape).astype(np.double)
        ok = np.allclose(mylib.array_add_value(in_arr, np.pi), in_arr + np.pi)
        if not ok:
            raise ValueError("incorrect result")
