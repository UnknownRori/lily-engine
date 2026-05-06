BUILD_TYPE=debug

all: desktop
	echo "Done"

clean:
	rm -rf dist

build:
	meson compile -C builddir
	meson install -C builddir

desktop:
	meson setup builddir --wipe --native-file ./native.ini --buildtype=$(BUILD_TYPE) --prefix=$(pwd)/dist
web:
	meson setup builddir --wipe --cross-file ./web.ini --buildtype=$(BUILD_TYPE) --prefix=$(pwd)/dist

