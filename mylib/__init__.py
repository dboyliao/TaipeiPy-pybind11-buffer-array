import numpy as np

from ._mylib import *


def create_mat(rows, cols):
    return np.array(MyMatrix(rows, cols), copy=False)
