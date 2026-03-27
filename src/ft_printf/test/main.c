/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrain <lrain@students.42berlin.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:33:21 by lrain             #+#    #+#             */
/*   Updated: 2026/02/22 17:16:50 by lrain            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"
#include <assert.h>
#include <stdio.h>

int main(void) {

  // target
  printf("target:");
  int target_ret = printf(NULL);
  printf("<<END OF PRINT>>\n\n");
  // actual
  printf("actual:");
  int actual_ret = ft_printf(NULL);
  printf("<<END OF PRINT>>\n\n");
  // return check
  assert(target_ret == actual_ret);
  printf("Return values are the same\n\n");

  // target
  printf("target:");
  target_ret = printf(0);
  printf("<<END OF PRINT>>\n\n");
  // actual
  printf("actual:");
  actual_ret = ft_printf(0);
  printf("<<END OF PRINT>>\n\n");
  // return check
  assert(target_ret == actual_ret);
  return (0);
}

