#include "init_array.hpp"

#include <stdexcept>
#include <vector>

#include "pybind11/numpy.h"

namespace py = pybind11;

static py::array_t<double> array_add_value(const py::array_t<double> &in_arr,
                                           double v = 1.0);
static py::array arg_min(const py::array &in_arr, int32_t axis = -1);
template <typename T>
py::buffer_info arg_min_impl_(const py::array &in_arr,
                              int32_t axis = -1) noexcept;

void init_array(py::module m) {
  m.def("array_add_value", &array_add_value, R"(add by given value)",
        py::arg("input_array"), py::arg("value") = 0.0)
      .def("arg_min", &arg_min, R"(argmin along given axis)",
           py::arg("input_array"), py::arg("axis") = -1);
}

py::array_t<double> array_add_value(const py::array_t<double> &in_arr,
                                    double v) {
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

py::array arg_min(const py::array &in_arr, int32_t axis) {
  auto info = in_arr.request();
  py::buffer_info out_info;
  if (info.format == py::format_descriptor<float>::format()) {
    out_info = arg_min_impl_<float>(in_arr, axis);
  } else if (info.format == py::format_descriptor<double>::format()) {
    out_info = arg_min_impl_<double>(in_arr, axis);
  } else if (info.format == py::format_descriptor<long double>::format()) {
    out_info = arg_min_impl_<long double>(in_arr, axis);
  } else if (info.format == py::format_descriptor<int8_t>::format()) {
    out_info = arg_min_impl_<int8_t>(in_arr, axis);
  } else if (info.format == py::format_descriptor<uint8_t>::format()) {
    out_info = arg_min_impl_<uint8_t>(in_arr, axis);
  } else if (info.format == py::format_descriptor<uint16_t>::format()) {
    out_info = arg_min_impl_<uint16_t>(in_arr, axis);
  } else if (info.format == py::format_descriptor<int16_t>::format()) {
    out_info = arg_min_impl_<int16_t>(in_arr, axis);
  } else if (info.format == py::format_descriptor<int32_t>::format()) {
    out_info = arg_min_impl_<int32_t>(in_arr, axis);
  } else if (info.format == py::format_descriptor<uint32_t>::format()) {
    out_info = arg_min_impl_<uint32_t>(in_arr, axis);
  } else if (info.format == py::format_descriptor<int64_t>::format()) {
    out_info = arg_min_impl_<int64_t>(in_arr, axis);
  } else if (info.format == py::format_descriptor<uint64_t>::format()) {
    out_info = arg_min_impl_<uint64_t>(in_arr, axis);
  } else {
    throw std::runtime_error("unsupported input datatype " + info.format);
  }
  return py::array(out_info);
}

template <typename T>
py::buffer_info arg_min_impl_(const py::array &in_arr, int32_t axis) noexcept {
  auto in_info = in_arr.request();
  if (axis < 0) {
    axis += in_info.ndim;
  }
  size_t axis_idx = static_cast<size_t>(axis);
  py::ssize_t axis_size = in_info.shape[axis_idx];
  py::ssize_t outer_size = 1;
  for (size_t idx = 0; idx < axis_idx; ++idx) {
    outer_size *= in_info.shape[idx];
  }
  py::ssize_t inner_size = 1;
  for (size_t idx = axis_idx + 1; idx < in_info.ndim; ++idx) {
    inner_size *= in_info.shape[idx];
  }

  int64_t *out_data = (int64_t *)malloc(
      sizeof(int64_t) * static_cast<size_t>(outer_size * inner_size));
  T *in_data = (T *)in_info.ptr;
  for (size_t outer = 0; outer < outer_size; ++outer) {
    for (size_t inner = 0; inner < inner_size; ++inner) {
      T min_value = in_data[outer * axis_size * inner_size + inner];
      int64_t min_idx = 0;
      for (size_t i = 0; i < axis_size; ++i) {
        T value = in_data[(outer * axis_size + i) * inner_size + inner];
        if (value <= min_value) {
          min_value = value;
          min_idx = static_cast<int64_t>(i);
        }
      }
      out_data[outer * inner_size + inner] = min_idx;
    }
  }
  py::ssize_t out_stride = sizeof(int64_t);
  std::vector<py::ssize_t> out_shape, out_strides;
  for (int idx_ = in_info.ndim - 1; idx_ >= 0; --idx_) {
    size_t idx = static_cast<size_t>(idx_);
    if (idx == axis_idx) {
      continue;
    }
    out_shape.insert(out_shape.begin(), in_info.shape[idx]);
    out_strides.insert(out_strides.begin(), out_stride);
    out_stride *= in_info.shape[idx];
  }
  py::buffer_info out_info(out_data, sizeof(int64_t),
                           py::format_descriptor<int64_t>::format(),
                           in_info.ndim - 1, out_shape, out_strides);
  return out_info;
}