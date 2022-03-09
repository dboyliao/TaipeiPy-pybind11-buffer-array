PYTHON_EXECUTABLE?=$$(pyenv which python3)

all: lib slides

slides:
	jupyter nbconvert Pybind11_Buffer_Array_Interface.ipynb --to slides

lib:
	mkdir -p build; \
	cmake -DPYTHON_EXECUTABLE=$(PYTHON_EXECUTABLE) -S . -B build; \
	cmake --build build

clean:
	@cmake --build build --target clean

.PHONY: clean