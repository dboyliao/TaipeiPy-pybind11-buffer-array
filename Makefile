PYTHON_EXECUTABLE?=$$(pyenv which python3)
BUILD_TYPE?=Debug

all: lib slides

slides:
	jupyter nbconvert \
	--to slides \
	--SlidesExporter.reveal_theme=serif \
	Pybind11_Buffer_Array_Interface.ipynb

lib:
	mkdir -p build; \
	cmake -DPYTHON_EXECUTABLE=$(PYTHON_EXECUTABLE) -S . -B build -DCMAKE_BUILD_TYPE=${BUILD_TYPE}; \
	cmake --build build -- -j 2

tests:
	PYTHONPATH=$$(pwd) pytest --pdb -s -v tests/

debug: lib
	lldb $(PYTHON_EXECUTABLE) \
	--one-line "target modules add mylib/$$(ls mylib | grep _mylib.*\.so)" \
	-- -m pytest tests \
	-vv --pdb

clean:
	@if [ -d build ]; then \
		cmake --build build --target clean; \
	fi;

.PHONY: clean tests