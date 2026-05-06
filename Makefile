BUILD_TYPE=debug

all: desktop
	echo "Done"

clean:
	rm -rf dist

build:
	meson install -C builddir

desktop:
	meson setup builddir --reconfigure --native-file ./native.ini --buildtype=$(BUILD_TYPE) --prefix=$(pwd)/dist
web:
	meson setup builddir --reconfigure --cross-file ./web.ini --buildtype=$(BUILD_TYPE) --prefix=$(pwd)/dist

