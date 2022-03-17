import numpy as np

import mylib


def test_print_buffer():
    mylib.print_buffer_info(np.random.rand(3, 3).astype(np.float16))
    mylib.print_buffer_info(np.random.rand(3, 3).astype(np.float32))
    mylib.print_buffer_info(np.random.rand(3, 3).astype(np.float64))
    mylib.print_buffer_info(np.random.rand(3, 3).astype(np.float128))
