BUILD_DIR='build'

.PHONY: compile upload monitor clean

upload: compile
	picotool load -f ./build/main.uf2

compile: build
	make -C build

build:
	cmake -DPICO_BOARD=pico2 -S . -B ${BUILD_DIR}

monitor:
	picocom /dev/ttyACM0

clean:
	rm -rf ${BUILD_DIR}
