release-name := "lrain-42-ft_printf"
release-tar-gz := release-name + ".tar.gz"

reset  := '\033[0m'
bold   := '\033[1m'
blue   := '\033[34m'
green  := '\033[92m'
yellow := '\033[33m'

_header name:
    @printf "\n{{bold}}{{blue}}=== {{name}} ===\n{{reset}}"

_step desc:
    @printf "{{yellow}}-> {{desc}}...{{reset}}\n"

_done name="":
    @if [ -n "{{name}}" ]; then printf "{{bold}}{{green}}=== done: {{name}} ===\n{{reset}}\n"; else printf "{{bold}}{{green}}=== done ===\n{{reset}}\n"; fi

build-project:
    @just _header "build-project"
    @just _step "building"
    make
    @just _done

build-release:
    @just _header "build-release"
    @just _step "removing previous dist build"
    rm -rfv dist/
    @just _step "building dist"
    just build-dist
    @just _step "compressing to {{release-tar-gz}}"
    tar -czvf {{release-tar-gz}} -C dist/ {{release-name}}/
    @echo "to create a release, run:"
    @echo "gh release create v1.0.0 --fail-on-no-commits dist/*.tar.gz"
    @just _done "{{release-tar-gz}}"

build-dist:
    @just _header "build-dist"
    @just _step "copying files to dist/"
    rsync -av --mkpath --include-from='.dist-include' --exclude='*' . dist/{{release-name}}/
    @just _done

test:
    @just _header "build & run test"
    @just _step "build test"
    make test
    @just _step "run test"
    ./test/runner.out
    @just _done "test"

retest:
    @just _header "rebuild & test"
    @just _step "rebuild"
    just re
    @just _step "test"
    just test
    @just _done "retest"

fclean:
    @just _header "fclean"
    @just _step "running make fclean"
    make fclean
    @just _step "removing dist/ and release archive"
    rm -rfv dist/
    rm -rfv {{release-tar-gz}}
    @just _done

re:
    @just _header "re"
    just fclean
    @just _step "building"
    make
    just build-dist
    @just _done "re"

cc-db:
    @just _header "cc-db"
    @just _step "capturing library build"
    bear -- make re
    @just _step "capturing test build"
    bear --append -- make test
    @just _done "compile_commands.json"
