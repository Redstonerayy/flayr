.PHONY: build

build:
	CC=/usr/bin/clang CXX=/usr/bin/clang++ cmake -B ./build -S . -G Ninja
	ninja -C ./build

run:
	./build/target

clean:
	rm -rf ./build