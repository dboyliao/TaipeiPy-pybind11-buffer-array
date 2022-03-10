PYTHON_EXECUTABLE?=$$(pyenv which python3)

all: lib slides

slides:
	jupyter nbconvert \
	--to slides \
	--SlidesExporter.reveal_theme=serif \
	Pybind11_Buffer_Array_Interface.ipynb

lib:
	mkdir -p build; \
	cmake -DPYTHON_EXECUTABLE=$(PYTHON_EXECUTABLE) -S . -B build; \
	cmake --build build

clean:
	@cmake --build build --target clean

.PHONY: clean