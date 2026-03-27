root-dir := justfile_directory()

name := "libft"

src-dir := root-dir / "src"
build-dir := root-dir / "build"

dist-dir := build-dir / "dist"
stage-dir := dist-dir / name + "_turnin_" 

ext-dir := root-dir / "external"

francinette-bin := ext-dir / "francinette/tester.sh"

    
build-dist:
    make fclean
    make all
    make dist

install-francinette:
    git submodule add -b master https://github.com/codingvivi/francinette.git external/francinette || true
    git submodule update --init --recursive
    python3 -m venv external/francinette/venv
    external/francinette/venv/bin/pip3 install -r external/francinette/requirements.txt

test-francinette *args:
    make stage
    cd {{stage-dir}} && bash {{francinette-bin}} {{args}}
