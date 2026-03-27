/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test/test_ft_atoi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:41:48 by lrain             #+#    #+#             */
/*   Updated: 2025/12/20 11:22:29 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*                                  includes                                  */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "unity.h"
#include "helpers.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*                                  globals                                   */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
static char *g_str_ft;
static char *g_str_control;

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*                                 functions                                  */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~ set up & tear down ~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void setUp(void)
{
	g_str_ft = NULL;
	g_str_control = NULL;
}

void tearDown(void)
{
	if (g_str_ft != NULL)
		free(g_str_ft);
	if (g_str_control != NULL)
		free(g_str_control);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ helpers ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void        create_test_str_copy(char *test_str, char **target_str_ptr);
static void returns_test_stdlib_control(void);
// static void	returns_test_hand_control(int expected_value);
static void modification_test(char *original_str);

static void all_tests_stdlib_control(char *test_str)
{
	create_test_str_copy(test_str, &g_str_ft);
	create_test_str_copy(test_str, &g_str_control);
	returns_test_stdlib_control();
	modification_test(test_str);
}

// static void	all_tests_hand_control(char *test_str, int expected_value)
// {
// 	create_test_str_copy(test_str, &g_str_ft);
// 	create_test_str_copy(test_str, &g_str_control);
// 	returns_test_hand_control(expected_value);
// 	modification_test(test_str);
// }

void create_test_str_copy(char *test_str, char **target_str_ptr)
{
	*target_str_ptr = (char *) malloc(strlen(test_str) + 1);
	if (*target_str_ptr == NULL)
		return;
	strcpy(*target_str_ptr, test_str);
	return;
}

static void returns_test_stdlib_control(void)
{
	TEST_ASSERT_EQUAL_INT(atoi(g_str_control), ft_atoi(g_str_ft));
}

// static void	returns_test_hand_control(int expected_value)
// {
// 	TEST_ASSERT_EQUAL_INT(expected_value, ft_atoi(g_str_ft));
// }

static void modification_test(char *original_str)
{
	TEST_ASSERT_EQUAL_STRING_MESSAGE(g_str_control, g_str_ft, "String got modified differently than by stdlib atoi!");
	TEST_ASSERT_EQUAL_STRING_MESSAGE(original_str, g_str_ft, "string has changed from what it was before!");
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ runners ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void test_int_max(void)
{
	all_tests_stdlib_control("2147483647");
}

void test_int_min(void)
{
	all_tests_stdlib_control("-2147483648");
}

void test_empty(void)
{
	all_tests_stdlib_control("");
}

void test_all_whitespace(void)
{
	char test_string[] = WHITESPACE INT_MIN_STR;

	all_tests_stdlib_control(test_string);
}

// technically not needed, remainder from piscine
void test_no_number(void)
{
	char test_string[] = WHITESPACE "--------";

	all_tests_stdlib_control(test_string);
}

void test_multi_0(void)
{
	char test_string[] = WHITESPACE "---------00000000";

	all_tests_stdlib_control(test_string);
}

void test_multi_0_num(void)
{
	char test_string[] = WHITESPACE "---------00000000" INT_MAX_STR;

	all_tests_stdlib_control(test_string);
}

void test_wrong_minus(void)
{
	char test_string[] = WHITESPACE "---------00000000" INT_MIN_STR;

	all_tests_stdlib_control(test_string);
}

void test_plus_num(void)
{
	char test_string[] = WHITESPACE "---++---+00000000" INT_MAX_STR;

	all_tests_stdlib_control(test_string);
}

void test_plus_multi_num(void)
{
	char test_string[] = WHITESPACE "+++++++++00000000" INT_MAX_STR;

	all_tests_stdlib_control(test_string);
}

void test_invalid_chars(void)
{
	char test_string[] = "0123456789";
	char c;

	create_test_str_copy(test_string, &g_str_ft);
	create_test_str_copy(test_string, &g_str_control);
	c = 1;
	while (c <= 126)
	{
		test_string[7] = c;
		g_str_ft[7] = c;
		g_str_control[7] = c;
		returns_test_stdlib_control();
		modification_test(test_string);
		c++;
	}
}

/*
// originals from piscine
void	test_no_number(void)
{
    char	test_string[] = WHITESPACE "--------";

    all_tests_hand_control(test_string, 0);
}

void	test_multi_0(void)
{
    char	test_string[] = WHITESPACE "---------00000000";

    all_tests_hand_control(test_string, 0);
}

void	test_multi_0_num(void)
{
    char	test_string[] = WHITESPACE "---------00000000" INT_MAX_STR;

    all_tests_hand_control(test_string, -INT_MAX);
}

void	test_wrong_minus(void)
{
    char	test_string[] = WHITESPACE "---------00000000" INT_MIN_STR;

    all_tests_hand_control(test_string, 0);
}

void	test_plus_num(void)
{
    char	test_string[] = WHITESPACE "---++---+00000000" INT_MAX_STR;

    all_tests_hand_control(test_string, INT_MAX);
}

void	test_plus_multi_num(void)
{
    char	test_string[] = WHITESPACE "+++++++++00000000" INT_MAX_STR;

    all_tests_hand_control(test_string, INT_MAX);
}

void	test_invalid_chars(void)
{
    char	test_string[] = "0123456789";
    char	c;

    create_test_str_copy(test_string, &g_str_ft);
    create_test_str_copy(test_string, &g_str_control);
    c = 1;
    while (c <= 126)
    {
        test_string[7] = c;
        g_str_ft[7] = c;
        g_str_control[7] = c;
        returns_test_stdlib_control();
        modification_test(test_string);
        c++;
    }
}
*/
