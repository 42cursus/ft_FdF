/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 03:30:21 by abelov            #+#    #+#             */
/*   Updated: 2024/05/25 03:30:35 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void sub_draw_line(t_fdf_struct *fdf,int x,int y,int max_x,int max_y,int color1,int color2,int orientation)

{
	int i;
	int neg;

	neg = 1;
	i = x;
	if (max_x < x) {
		neg = -1;
	}
	while (i * neg <= max_x * neg) {
		if (color2 == 0) {
			mlx_pixel_put(fdf->mlx_app,fdf->main_win,y + ((max_y - y) * (i - x)) / (max_x - x),i,color1);
		}
		else {
			mlx_pixel_put(fdf->mlx_app,fdf->main_win,i,y + ((max_y - y) * (i - x)) / (max_x - x),color1);
		}
		i = neg + i;
	}
}

void draw_line(t_fdf_struct *fdf,int x,int y,int max_x,int max_y,int color1,int color2)

{
	int y_diff;
	int x_diff;

	if (max_x - x < 0) {
		x_diff = -(max_x - x);
	}
	else {
		x_diff = max_x - x;
	}
	if (max_y - y < 0) {
		y_diff = -(max_y - y);
	}
	else {
		y_diff = max_y - y;
	}
	if (x_diff < y_diff) {
		sub_draw_line(fdf,y,x,max_y,max_x,color1,0,y_diff);
	}
	else {
		if ((x == max_x) && (y == max_y)) {
			mlx_pixel_put(fdf->mlx_app,fdf->main_win,x,max_y,color1);
		}
		else {
			sub_draw_line(fdf,x,y,max_x,max_y,color1,1,y_diff);
		}
	}
}