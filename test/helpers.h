/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test/helpers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:47:54 by lrain             #+#    #+#             */
/*   Updated: 2025/12/20 11:30:47 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H

// # include <assert.h>
#include "libft.h"
#include "unity.h"
#include <stdbool.h>
#include <stdio.h>

#ifdef VERBOSE
#define VERBOSE_PRINT(...) printf(__VA_ARGS__)
#else
#define VERBOSE_PRINT(...)
#endif

#define NUM_OF_ASCIIS 128

#define LOWERCASE_LETTERS "abcdefghijklmnopqrstuvwxyz"
#define UPPERCASE_LETTERS "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define DIGITS "0123456789"
#define SPECIALS "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
#define WHITESPACE " \t\n\v\f\r"

#define ALL_PRINTABLE_ASCII                                                    \
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!\"#$%&'()" \
	"*+,-./:;<=>?@[\\]^_`{|}~ "
#define ALPHANUMERIC_CHARS LOWERCASE_LETTERS UPPERCASE_LETTERS DIGITS
#define ALPHA_CHARS LOWERCASE_LETTERS UPPERCASE_LETTERS

#define INT_MAX_STR "2147483647";
#define INT_MIN_STR "-2147483648";
#define EMPTY_STR "";

void compare_as_bools(bool target, bool actual);
void get_all_asciis(char *str_ptr);
void check_against_stdlib(char *tgt, char *act);

#define HELPERS_H
#endif
