#include "init_array.hpp"

#include "pybind11/numpy.h"

namespace py = pybind11;

static py::array_t<double> array_add_value(const py::array_t<double> &in_arr,
                                           double v = 1.0) {
  auto info = in_arr.request();
  double *out_buff = new double[info.size];
  auto in_ptr = (double *)info.ptr;
  for (py::ssize_t idx = 0; idx < info.size; ++idx) {
    *(out_buff + idx) = *(in_ptr + idx) + v;
  }
  auto out_info = py::buffer_info(out_buff, info.itemsize, info.format,
                                  info.ndim, info.shape, info.strides);
  return py::array_t<double>(out_info);
}

void init_array(py::module m) {
  m.def("array_add_value", &array_add_value, R"(add by given value)",
        py::arg("input_array"), py::arg("value") = 0.0);
}