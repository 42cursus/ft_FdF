/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:01:46 by abelov            #+#    #+#             */
/*   Updated: 2024/05/18 01:01:47 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void data_convert(t_fdf_struct *fdf,t_list_node *node)
{
	long *long_array;
	int *int_array;
	long height;
	ulong colour;
	char *endptr;
	int i;
	t_list_node *current_node;
	t_fdf_struct *l_fdf;

	current_node = node;
	l_fdf = fdf;
	long_array = (long *)malloc((long)fdf->cols << 3);
	current_node->heights = long_array;
	int_array = (int *)malloc((long)l_fdf->cols << 2);
	current_node->colors = int_array;
	i = l_fdf->cols;
	while (i != 0)
		current_node->colors[--i] = 0xffffff;
	i = 0;
	while( true ) {
		if (l_fdf->cols <= i)
			return;
		if (current_node->word_tab[i] == NULL) break;
		height = strtol(current_node->word_tab[i],&endptr,0);
		current_node->heights[i] = height;
		if ((long) l_fdf->max_height < current_node->heights[i])
			l_fdf->max_height = (int) current_node->heights[i];
		if (*endptr == ',') {
			colour = strtoul(endptr + 1,NULL,0);
			current_node->colors[i] = (int)colour;
			l_fdf->custom_colour = 1;
		}
		i++;
	}
	printf("Found wrong line length. Exiting.\n");
	/* WARNING: Subroutine does not return */
	exit(1);
}
