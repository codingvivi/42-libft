_This project has been created as part of the 42 curriculum by lrain_

# 42-ft_printf

![](./printing.jpg)

## Description

`ft_printf` is a partial reimplementation of the C standard library's `printf`.
It parses a format string and consumes variadic arguments to produce formatted output on stdout,
returning the total number of characters written.

Supported conversions:

| Specifier | Output |
|-----------|-------------------------------------|
| `%c` | Single character |
| `%s` | String (`(null)` if pointer is NULL)|
| `%p` | Pointer address as `0x...` hex (`(nil)` if pointer is NULL) |
| `%d`, `%i`| Signed decimal integer |
| `%u` | Unsigned decimal integer |
| `%x` | Unsigned hexadecimal (lowercase) |
| `%X` | Unsigned hexadecimal (uppercase) |
| `%%` | Literal `%` |

If the format string itself is `NULL`, `ft_printf` returns `-1` and writes nothing.

## Instructions

### Building

Download the latest release archive from the [releases page](https://github.com/codingvivi/42-ft_printf/releases),
then:

```bash
tar -xzvf lrain-42-ft_printf.tar.gz
cd lrain-42-ft_printf/
make
```

Run `make [target]`. Available targets:

| Target | Description |
|----------|--------------------------------------|
| `all` | Build `libftprintf.a` (default) |
| `clean` | Remove object files |
| `fclean` | Remove object files and the library |
| `re` | Full rebuild (`fclean` + `all`) |
| `test` | Build and link the test runner |

### Developing

While this is relevant for pretty much me only,
since I am the sole person wanting to create a distributable
(read: one conforming to the the 42 turnin requirements)
version of this source code,
the build/testchain for doing so requires:

- [rsync](https://rsync.samba.org/) (if it's not already preinstalled on the machine)
- [just](https://github.com/casey/just) (For orchestration, could have stuck everything into a makefile, but `just` is faster to work with and was already installed on my machine anyway. Non of the justfile's contents is trailblazing stuff, the individual commands it calls can be run manually as well)
- optional:[bear](https://github.com/rizsotto/Bear) (for clangd/LSP linting)

If installed, run `just [recipe]`. Available recipes:

| Recipe | Description |
|-----------------|--------------------------------------------------------------------------|
| `build-project` | Runs `make` to build the library (default) |
| `build-dist` | Syncs the distributable files into `dist/` via rsync |
| `build-release` | Cleans `dist/`, runs `build-dist`, then compresses the result into a `.tar.gz` |
| `fclean` | Runs `make fclean` and removes `dist/` and the release archive |
| `re` | Runs `fclean`, rebuilds the library, then runs `build-dist` |
| `test` | Builds the test runner and executes it |
| `retest` | Runs `re`, builds the test runner, and executes it |
| `cc-db` | Generates `compile_commands.json` via `bear` (for clangd/LSP) |

## Algorithm

### Format string parsing

`ft_printf` scans the format string linearly,
one character at a time.
Non-`%` characters are written directly to stdout with `write(2)`.
When a `%` is encountered,
the next character is read as the conversion specifier
and dispatched to the appropriate handler via an if-else chain.
All handlers return the number of bytes written,
which is accumulated into the return value.

### Helper functions

All of the relevant functions
originally were from the [libft](https://github.com/codingvivi/42_libft) project.
They were modified to allow for returning the write count.
Additionally, the putnbr function has been expanded
to be able to deal with different numeral systems.
It's file now contains a function for unsigneds as well.

#### Number to string conversion

All numeric conversions funnel through two functions.
`ft_pf_putnbr_base_fd` (signed) handles only what is unique to signed integers:
writing the `-` sign if negative and reinterpreting the value as unsigned,
then delegating to `ft_pf_putnbru_base_fd`.
`ft_pf_putnbru_base_fd` (unsigned) handles all other cases,
including `%u`, `%x`, `%X`, and `%p`.
It takes a `uint64_t` rather than `unsigned int` because it also serves `%p`,
and pointers on 64-bit systems are 64 bits wide — wider than `unsigned int` (typically 32 bits).
Using `uint64_t` means a single function covers both without truncating pointer values.

The underlying `itoa_fwd_fd` avoids the conventional approach of building the digit string
in reverse and then reversing it or using a stack.
Instead it writes digits directly left-to-right by first finding the highest place value
— the largest power of the base that fits into the number —
then extracting each digit from most significant to least:

```
place_val = highest power of base ≤ nb
while nb != 0:
    write digit at nb / place_val
    nb = nb % place_val
    place_val /= base
write any remaining trailing zeros
```

For example, `1234` in base 10: place value starts at `1000`, yielding `1`, `2`, `3`, `4` in one pass with no buffer.

The base is defined by a `base_digits` string (e.g. `"0123456789abcdef"`),
whose length determines the base and each index maps to its character.
This is what allows `%d`, `%u`, `%x`, `%X`, and `%p` to all share the same conversion code,
as mentioned above.

## Resources

### References

[1] "Fixed width integer types (since C99)," *cppreference.com*. Accessed: Feb. 20, 2026. [Online]. Available: https://en.cppreference.com/w/c/types/integer.html

[2] R. Felker, *musl libc*. (Feb. 29, 2024). C. Accessed: Feb. 12, 2026. [Online]. Available: https://git.musl-libc.org/cgit/musl/tag/?h=v1.2.5

[3] "va_arg," *cppreference.com*. Accessed: Feb. 20, 2026. [Online]. Available: https://en.cppreference.com/w/c/variadic/va_arg.html

[4] "va_end," *cppreference.com*. Accessed: Feb. 20, 2026. [Online]. Available: https://en.cppreference.com/w/c/variadic/va_end.html

[5] "va_start," *cppreference.com*. Accessed: Feb. 18, 2026. [Online]. Available: https://en.cppreference.com/w/c/variadic/va_start.html

[6] "Variadic arguments," *cppreference.com*. Accessed: Feb. 18, 2026. [Online]. Available: https://en.cppreference.com/w/c/language/variadic.html

[7] "Variadic functions," *cppreference.com*. Accessed: Feb. 15, 2026. [Online]. Available: https://en.cppreference.com/w/c/variadic.html

### AI usage

Claude Opus 4.6
was used for gruntwork, like:

- refactoring (e.g. update argument structures of functions accross files)
- updating printouts for my justfile to make it more readable
- Edit/correct sections of the readme
- Convert Zoteros reference formatting to markdown
