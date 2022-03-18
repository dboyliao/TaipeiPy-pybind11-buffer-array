import numpy as np

import mylib


def test_print_buffer():
    print()
    mylib.print_buffer_info(np.random.rand(3, 3).astype(np.float16))
    print()
    mylib.print_buffer_info(np.random.rand(3, 3).astype(np.float32))
    print()
    mylib.print_buffer_info(np.random.rand(3, 3).astype(np.float64))
    print()
    mylib.print_buffer_info(np.random.rand(3, 3).astype(np.float128))
