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

test *names:
    #!/usr/bin/env nu
    let bins = if ("{{names}}" | str trim | is-empty) {
        make test
        glob build/bin/test/*_Runner.out
    } else {
        "{{names}}" | split row " " | each {|name|
            make $"test-($name)"
            $"build/bin/test/test_($name)_Runner.out"
        }
    }
    let pred = {|bin|
        print $"===> Running: ($bin)"
        do -i { run-external $bin }
        let code = $env.LAST_EXIT_CODE
        print ""
        $code != 0
    }
    let failed = $bins | where $pred
    if ($failed | is-not-empty) {
        print $"(ansi red)FAILED ((ansi reset)($failed | length)(ansi red)):(ansi reset)"
        $failed | each {|b| print $"  ($b)" }
        exit 1
    }

test-francinette *args:
    make stage
    cd {{stage-dir}} && bash {{francinette-bin}} {{args}}
