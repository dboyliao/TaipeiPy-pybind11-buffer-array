#include "init_buffer_protocol.hpp"

#include <iostream>
#include <vector>

namespace {
class MyMatrix {
 private:
  py::ssize_t rows_, cols_;
  float *data_;

 public:
  MyMatrix(py::ssize_t rows, py::ssize_t cols) : rows_(rows), cols_(cols) {
    data_ = new float[static_cast<size_t>(rows * cols)];
    memset(data_, 0, sizeof(float) * (size_t)(rows * cols));
  }
  MyMatrix(const MyMatrix &other) : rows_(other.rows_), cols_(other.cols_) {
    std::cout << "copy constr" << std::endl;
    data_ = new float[static_cast<size_t>(other.rows_ * other.cols_)];
    memcpy(data_, other.data_, sizeof(float) * (size_t)(rows_ * cols_));
  }
  MyMatrix(MyMatrix &&other) noexcept
      : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
    std::cout << "move constr" << std::endl;
    other.rows_ = 0;
    other.cols_ = 0;
    other.data_ = nullptr;
  }
  ~MyMatrix() {
    std::cout << "deleting: " << data_ << std::endl;
    delete[] data_;
  }

  MyMatrix &operator=(const MyMatrix &other) {
    std::cout << "copy assign op" << std::endl;
    if (this == &other) {
      return *this;
    }
    delete[] data_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    data_ = new float[static_cast<size_t>(rows_ * cols_)];
    memcpy(data_, other.data_,
           sizeof(float) * static_cast<size_t>(rows_ * cols_));
    return *this;
  }

  MyMatrix &operator=(MyMatrix &&other) noexcept {
    std::cout << "move assign op" << std::endl;
    if (&other != this) {
      delete[] data_;
      rows_ = other.rows_;
      cols_ = other.cols_;
      data_ = other.data_;
      other.rows_ = 0;
      other.cols_ = 0;
      other.data_ = nullptr;
    }
    return *this;
  }

  float *data() const { return data_; }
  py::ssize_t rows() const { return rows_; }
  py::ssize_t cols() const { return cols_; }
};
}  // namespace

static void print_vector(const std::vector<py::ssize_t> &vec,
                         std::ostream &os = std::cout);
static void print_buffer_info(py::buffer b);

void init_buffer_protocol(py::module m) {
  m.def("print_buffer_info", &print_buffer_info, R"(print buffer info)");
  py::class_<MyMatrix>(m, "MyMatrix", py::buffer_protocol())
      .def(py::init<int, int>(), py::arg("rows"), py::arg("cols"))
      .def_buffer([](const MyMatrix &m) {
        return py::buffer_info(
            /* the memory block */
            m.data(),
            /* Size of one scalar */
            sizeof(float),
            /* string, Python struct-style format descriptor */
            py::format_descriptor<float>::format(),
            /* Number of dimensions */
            2,
            /* Buffer shape */
            {m.rows(), m.cols()},
            /* Strides (in bytes) for each index */
            {sizeof(float) * m.cols(), sizeof(float)});
      });
}

void print_vector(const std::vector<py::ssize_t> &vec, std::ostream &os) {
  os << "{";
  for (size_t i = 0; i < vec.size() - 1; ++i) {
    os << vec[i] << ", ";
  }
  if (vec.size() >= 1) {
    os << vec.back();
  }
  os << "}" << std::endl;
}

void print_buffer_info(py::buffer b) {
  auto info = b.request();
  std::cout << "ptr: " << info.ptr << std::endl;
  std::cout << "item size: " << info.itemsize << std::endl;
  std::cout << "size: " << info.size << std::endl;
  std::cout << "format: " << info.format << std::endl;
  std::cout << "ndim: " << info.ndim << std::endl;
  std::cout << "shape: ";
  print_vector(info.shape);
  std::cout << "strides (in bytes): ";
  print_vector(info.strides);
}