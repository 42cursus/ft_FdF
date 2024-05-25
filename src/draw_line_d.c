/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:07:19 by abelov            #+#    #+#             */
/*   Updated: 2024/05/18 01:07:19 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void sub_draw_line_d(t_fdf_struct *fdf,int x,int y,int max_x,int max_y,int color1,int color2,int orientation)
{
	int colour1_shift1;
	int colour1_shift2;
	int color;
	int curr;
	int neg;

	neg = (max_x >= x) ? 1 : -1;
	colour1_shift1 = color1 >> 0x10 & 0xff;
	colour1_shift2 = color1 >> 8 & 0xff;
	curr = x;
	while (curr * neg <= max_x * neg) {
		color = (colour1_shift1 + (int)((curr - x) * ((color2 >> 0x10 & 0xffU) - colour1_shift1)) / (max_x - x) & 0xffU) * 0x10000 +
				(colour1_shift2 + (int)((curr - x) * ((color2 >> 8 & 0xffU) - colour1_shift2)) / (max_x - x) & 0xffU) * 0x100 +
				((color1 & 0xffU) + (int)((curr - x) * ((color2 & 0xffU) - (color1 & 0xffU))) / (max_x - x) & 0xff);
		if (orientation == 0) {
			mlx_pixel_put(fdf->mlx_app,fdf->main_win,y + ((max_y - y) * (curr - x)) / (max_x - x),curr,color);
		}
		else {
			mlx_pixel_put(fdf->mlx_app,fdf->main_win,curr,y + ((max_y - y) * (curr - x)) / (max_x - x),color);
		}
		curr = neg + curr;
	}
}

void draw_line_d(t_fdf_struct *fdf,int x,int y,int max_x,int max_y,int color1,int color2)

{
	int y_diff;
	int x_diff;

	if (max_x - x < 0)
		x_diff = -(max_x - x);
	else
		x_diff = max_x - x;

	if (max_y - y < 0)
		y_diff = -(max_y - y);
	else
		y_diff = max_y - y;

	if (x_diff < y_diff)
		sub_draw_line_d(fdf, y, x, max_y, max_x, color1, color2, 0);
	else {
		if ((x == max_x) && (y == max_y))
			mlx_pixel_put(fdf->mlx_app, fdf->main_win, x, max_y, color1);
		else
			sub_draw_line_d(fdf, x, y, max_x, max_y, color1, color2, 1);
	}
}
