*This project has been created as part of the 42 curriculum by lrain.*

![](banner.jpg)
*I got accepted to 42!!!*

# Libft

My (re)implementation of some of the libc functions
as part of the first 42 project, libft.

## Instructions

### External dependencies

For all of my submission
and most of this repo
`make` is sufficient.
For a few niceties
like running all tests at once
and testing compilation before building
you will need:

- [`just`](https://github.com/casey/just)
- [`nushell`](https://www.nushell.sh/)
- `ruby` (for Unity test runner generation)

### Building the library and a release for submission

With the addition of the subsequent 42 projects that have us expand libft,
the repo now uses a [Pitchfork](https://joholl.github.io/pitchfork-website/)-inspired layout
so the working tree stays tidy:
source files live in `src/`,
headers in `include/`,
tests in `test/`,
and so on.
However,
the original instructions
(and deepthought probably,
even through I shouldn't run into it after GNL)
expects a flat directory
with all `.c` and `.h` files at the root next to the Makefile.
Thus I set up a build system that will take the repo to and from a flat structure
for submissions
and retain an orderly structure for actually working in it:

- `make init`:
  Moves any flat `.c`/`.h` files from the root
  into `src/` and `include/`.
  Idempotent — only fires when the files still sit at root.

- `make` / `make all`:
  Builds `libft.a` from `src/` and `include/`.
  When running inside a turn-in archive (`TURNIN_RUN=true`),
  it also copies the library to the project root
  so the autochecker finds it.

- `make fclean`:
  Undoes `init` — moves `.c` and `.h` files back to the root
  and cleans build artifacts.
  The now-empty `src/` and `include/` directories
  are only removed when `TURNIN_RUN=true`;
  in the normal dev environment `src/` is kept
  because it contains a `.clang-tidy`
  that provides linting according to the school norm.

- `make hclean`:
  The old `fclean` — removes build artifacts
  without flattening.

- `make clean`:
  Removes object files only.

- `make re`:
  Full rebuild (`hclean` + `all`).

- `make bonus`:
  Legacy alias for `all`,
  kept for older external testers
  that check for a `bonus` rule.

- `make stage`:
  Creates a flat distribution environment in `build/dist/`
  with `TURNIN_RUN=true` injected into the Makefile.
  Used by francinette and for submission testing.

- `make dist`:
  Creates a tarball to be downloaded
  and extracted onto a school computer
  and then turned in.
  In future projects
  I used github releases for this.

- `just build-dist`:
  Full clean rebuild followed by `make dist`.
  If compilation fails,
  there's no use in building either.

### Building and running tests

#### Own tests (Unity)

Tests live in `test/` and use the
[Unity](https://github.com/ThrowTheSwitch/Unity) test framework.

- `just test`:
  Builds and runs all tests.
- `just test <name> [name ...]`:
  Builds and runs specific tests,
  e.g. `just test ft_strlen ft_atoi`.
- `make test`:
  Builds all test binaries (without running them).
- `make test-<name>`:
  Builds a single test binary,
  e.g. `make test-ft_strlen`.

Test binaries are placed in `build/bin/test/`.

#### Francinette

If you have francinette installed,
you can just use it by creating a folder
mirroring the submission repo
using

```sh
make stage
cd build/dist/libft_turnin_
francinette #or paco
```

Otherwise, use my just commands to install and run francinette:

```sh
just install-francinette
just test-francinette
# you can also pass francinette flags, like
just test-francinette --strict
```

## Description

Instead of writing the same functions from the piscine for the millionth time now,
I decided to look at how professionals do it,
and use the very performant and widely compatible
[musl libc](https://musl.libc.org/)
as a reference for a lot of my code.
A decision I don't regret,
these people are cracked!

### Libc Functions

As per the guidelines,
my library includes the following:

- `ft_isalpha`:
  Checks if a character is an alphabetic letter.
- `ft_isdigit`:
  Checks if a character is a digit (0-9).
- `ft_isalnum`:
  Checks if a character is alphanumeric
  (a letter or a digit).
- `ft_isascii`:
  Checks if a character is a 7-bit US-ASCII character.
- `ft_isprint`:
  Checks if a character is a printable character.
- `ft_strlen`:
  Calculates the length of a string.
- `ft_memset`:
  Fills a block of memory with a specified value.
- `ft_bzero`:
  Fills a block of memory with zeroes.
- `ft_memcpy`:
  Copies a block of memory from a source to a destination.
- `ft_memmove`:
  Copies a block of memory,
  safely handling overlapping regions.
- `ft_strlcpy`:
  Copies a string up to a specified size,
  ensuring null-termination.
- `ft_strlcat`:
  Concatenates a string up to a specified size,
  ensuring null-termination.
- `ft_toupper`:
  Converts a lowercase letter to its uppercase equivalent.
- `ft_tolower`:
  Converts an uppercase letter to its lowercase equivalent.
- `ft_strchr`:
  Locates the first occurrence of a character in a string.
- `ft_strrchr`:
  Locates the last occurrence of a character in a string.
- `ft_strncmp`:
  Compares two strings up to a specified number of characters.
- `ft_memchr`:
  Locates the first occurrence of a byte in a block of memory.
- `ft_memcmp`:
  Compares two blocks of memory.
- `ft_strnstr`:
  Locates the first occurrence of a substring (needle)
  in a string (haystack),
  up to a specified length.
- `ft_atoi`:
  Converts the initial portion of the string pointed to by `str`
  to an `int`.
- `ft_calloc`:
  Allocates memory for an array of `nmemb` elements,
  each of `size` bytes,
  and initializes all bytes to zero.
- `ft_strdup`:
  Duplicates a string
  by allocating sufficient memory for a copy.

### Additional Functions

- `ft_substr`:
  Extracts a substring from a string,
  starting at `start` and of `len` characters.
- `ft_strjoin`:
  Concatenates two strings (`s1` and `s2`) into a new string.
- `ft_strtrim`:
  Removes any leading and trailing characters
  specified in `set` from `s1`.
- `ft_split`:
  Splits a string `s` by a delimiter character `c`
  into an array of newly allocated strings.
- `ft_itoa`:
  Converts an integer `n` into a null-terminated string.
- `ft_strmapi`:
  Applies a function `f` to each character of the string `s`
  to create a new string
  resulting from successive applications of `f`.
- `ft_striteri`:
  Applies a function `f` to each character of the string `s`,
  passing its index as the first argument
  and the character itself as the second.
- `ft_putchar_fd`:
  Writes a character `c` to the given file descriptor `fd`.
- `ft_putstr_fd`:
  Writes a string `s` to the given file descriptor `fd`.
- `ft_putendl_fd`:
  Writes a string `s` to the given file descriptor `fd`,
  followed by a newline.
- `ft_putnbr_fd`:
  Writes an integer `n` to the given file descriptor `fd`.

### Functions added since turnin

#### ft_printf

Added as a subtree from the subsequent [42 printf project](https://github.com/codingvivi/42-ft_printf).
Implements a simplified `printf` supporting `%c`, `%s`, `%p`, `%d`, `%i`, `%u`, `%x`, `%X`, and `%%`.

- `ft_printf`:
  Formatted output to stdout, returns number of characters printed.

### Linked list (formerly bonus)

- `ft_lstnew`:
  Creates a new list element (node)
  with the given `content`.
- `ft_lstadd_front`:
  Adds the element `new` to the beginning of the list `lst`.
- `ft_lstsize`:
  Counts the number of elements in a list.
- `ft_lstlast`:
  Returns the last element of a list.
- `ft_lstadd_back`:
  Adds the element `new` to the end of the list `lst`.
- `ft_lstdelone`:
  Deletes a single list element,
  freeing its content.
- `ft_lstclear`:
  Deletes and frees all elements of a list,
  starting from `lst`.
- `ft_lstiter`:
  Applies a function `f`
  to the content of each element of the list.
- `ft_lstmap`:
  Creates a new list
  by applying a function `f`
  to each element's content of the original list.

## Resources

### References

Apple Inc., "macOS C Library Reference," Apple Inc., Cupertino, CA, System Documentation Section 3, 2025.

C. Lambert, "Makefile Tutorial by Example," *Makefile Tutorial*. [Online]. Available: https://makefiletutorial.com. [Accessed: Dec. 25, 2025].

cppreference.com contributors, "C reference," *cppreference.com*. [Online]. Available: https://en.cppreference.com/w/c. [Accessed: Dec. 25, 2025].

die.net, "Linux man pages: Library functions (3)," *die.net*. [Online]. Available: https://linux.die.net/man/3/. [Accessed: Dec. 25, 2025].

ISO/IEC JTC 1/SC 22/WG 14, *N1570: Committee Draft of ISO/IEC 9899:2011*, ISO/IEC, Apr. 2011. [Online]. Available: http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf.

M. Kerrisk, "libc(7) — Linux manual page," *man7.org*. [Online]. Available: https://man7.org/linux/man-pages/man7/libc.7.html. [Accessed: Dec. 25, 2025].

M. Vandervoord, "Building With Make," *Throw The Switch*. [Online]. Available: https://www.throwtheswitch.org/build/make. [Accessed: Dec. 25, 2025].

R. Felker, *musl* (ver. 1.2.5), Source code, Feb. 2024. [Online]. Available: https://git.musl-libc.org/cgit/musl/tag/?h=v1.2.5. [Accessed: Dec. 25, 2025].

Throw The Switch, *Unity*, Source code. [Online]. Available: https://github.com/ThrowTheSwitch/Unity. [Accessed: Dec. 25, 2025].

### AI usage

Google Gemini Pro 2.5 and 3.0
was used as a conversational aide
to understand some of the reference code used for this project,
mainly the musl reimplementations and Makefile code.
It also helped formatting the references,
since I was having export issues out of Zotero.
