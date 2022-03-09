#include "init_array.hpp"
#include "init_buffer_protocol.hpp"
#include "pybind11/pybind11.h"

namespace py = pybind11;

PYBIND11_MODULE(_mylib, m) {
  m.doc() = "Example demo extension module";
  init_buffer_protocol(m);
  init_array(m);
}