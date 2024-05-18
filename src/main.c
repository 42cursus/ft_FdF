/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:05:13 by abelov            #+#    #+#             */
/*   Updated: 2024/05/17 20:05:14 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"



int main(int argc,char **argv)
{
	unsigned long tmp_var;
	int shortest_side;
	int longest_side;
	t_fdf_struct fdf;
	t_arguments *args;
	int arg_num;
	int ret_code;

	ret_code = 0;
	args = (t_arguments *)argv;
	arg_num = argc;
	if ((argc != 2) && (argc != 4)) {
		printf("Usage : %s <filename> [ case_size z_size ]\n",*argv);
		exit(1);
	}
	fdf.filename = argv[1];
	fdf.map = NULL;
	fdf.custom_colour = 0;
	load_data(&fdf);
	if ((fdf.cols != 0) && (fdf.rows != 0)) {
		fdf.case_size = 0x14;
		if (fdf.cols < fdf.rows)
			longest_side = fdf.rows;
		else
			longest_side = fdf.cols;
		fdf.w_width = (longest_side * 280) / 10;
		if (1000 < fdf.w_width) {
			fdf.w_width = 1000;
			if (fdf.cols < fdf.rows)
				shortest_side = fdf.rows;
			else
				shortest_side = fdf.cols;
			fdf.case_size = (int)(10000 / (long)(shortest_side * 0xe)) + 1;
		}
		fdf.z_size = fdf.case_size;
		fdf.w_height = fdf.max_height * fdf.case_size + (fdf.case_size * (fdf.cols + fdf.rows) * 7) / 0x14;
		if (800 < fdf.w_height) {
			fdf.w_height = 800;
			fdf.z_size = (800 - (fdf.case_size * (fdf.cols + fdf.rows) * 7) / 0x14) / fdf.max_height + 1;
		}
		if (arg_num == 4) {
			tmp_var = strtoul(args->case_size,NULL,0);
			if (tmp_var != 0) {
				tmp_var = strtoul(args->z_size,NULL,0);
				if (tmp_var != 0) {
					tmp_var = strtoul(args->case_size,NULL,0);
					fdf.case_size = (int)tmp_var;
					tmp_var = strtoul(args->z_size,NULL,0);
					fdf.z_size = (int)tmp_var;
				}
			}
		}
		fdf.mlx_app = mlx_init();
		if (fdf.mlx_app == NULL)
			exit(1);
		fdf.main_win = mlx_new_window(fdf.mlx_app,fdf.w_width,fdf.w_height,"fdf");
		on_expose(&fdf);
		mlx_key_hook(fdf.main_win,out,NULL);
		mlx_loop(fdf.mlx_app);
		return (ret_code);
	}
	printf("No data found.\n");
	exit(1);
}
