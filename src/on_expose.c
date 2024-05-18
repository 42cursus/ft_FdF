/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_expose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 02:00:29 by abelov            #+#    #+#             */
/*   Updated: 2024/05/16 02:00:29 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void * on_expose(t_fdf_struct *fdf)

{
	t_list_node *node;
	int curr_row;
	int curr_col;
	int prev_col;
	int prev_row;

	node = fdf->map;
	curr_row = fdf->rows;
	while (curr_row--, curr_row > 0) {
		prev_row = curr_row + 1;
		curr_col = fdf->cols;
		while (curr_col--, curr_col > 0) {
			prev_col = curr_col + 1;
			draw_line_d(fdf,
						((curr_col * fdf->case_size * 7) / 10 - (curr_row * fdf->case_size * 7) / 10) + fdf->w_width / 2,
						fdf->w_height - ((int)node->heights[curr_col] * fdf->z_size + (curr_col * fdf->case_size * 7) / 0x14 + (curr_row * fdf->case_size * 7) / 0x14),
						(((prev_col + -2) * fdf->case_size * 7) / 10 - (curr_row * fdf->case_size * 7) / 10) + fdf->w_width / 2,
						fdf->w_height - ((int)node->heights[prev_col + -2] * fdf->z_size + ((prev_col + -2) * fdf->case_size * 7) / 0x14 + (curr_row * fdf->case_size * 7) / 0x14),
						node->colors[curr_col],
						node->colors[prev_col + -2]);
			draw_line_d(fdf, ((curr_col * fdf->case_size * 7) / 10 - (curr_row * fdf->case_size * 7) / 10) + fdf->w_width / 2,
						fdf->w_height - ((int)node->heights[curr_col] * fdf->z_size + (curr_col * fdf->case_size * 7) / 0x14 + (curr_row * fdf->case_size * 7) / 0x14),
						((curr_col * fdf->case_size * 7) / 10 - ((prev_row + -2) * fdf->case_size * 7) / 10) + fdf->w_width / 2,
						fdf->w_height - ((int)node->next->heights[curr_col] * fdf->z_size + (curr_col * fdf->case_size * 7) / 0x14 + ((prev_row + -2) * fdf->case_size * 7) / 0x14),
						node->colors[curr_col],
						node->next->colors[curr_col]);
			if (fdf->custom_colour != 0) {
				draw_line_d(fdf, ((curr_col * fdf->case_size * 7) / 10 - (curr_row * fdf->case_size * 7) / 10) + fdf->w_width / 2,
							fdf->w_height - ((int)node->heights[curr_col] * fdf->z_size + (curr_col * fdf->case_size * 7) / 0x14 + (curr_row * fdf->case_size * 7) / 0x14),
							(((prev_col + -2) * fdf->case_size * 7) / 10 - ((prev_row + -2) * fdf->case_size * 7) / 10) + fdf->w_width / 2,
							fdf->w_height - ((int)node->next->heights[prev_col + -2] * fdf->z_size + ((prev_col + -2) * fdf->case_size * 7) / 0x14 + ((prev_row + -2) * fdf->case_size * 7) / 0x14),
							node->colors[curr_col],
							node->next->colors[prev_col + -2]);
			}
		}
		if (curr_row % (fdf->rows / 10 + 1) == 0)
			mlx_do_sync(fdf->mlx_app);
		node = node->next;
	}
	return NULL;
}
