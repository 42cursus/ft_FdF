/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:59:32 by abelov            #+#    #+#             */
/*   Updated: 2024/05/02 19:59:33 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include "libft.h"
# include "mlx.h"

# define DEFAULT_CASE_SIZE 20
# define EXIT_KEY 0x35 /* (53) Number 5 on the main keyboard */

#define COLOUR_MASK 0xffU
typedef struct s_args {
	char *prog_name;
	char *filename;
	char *case_size;
	char *z_size;
} t_arguments;

typedef struct s_list_node t_list_node;
struct s_list_node {
	char * line;
	char ** word_tab;
	long *heights;
	int *colors;
	t_list_node * next;
};

typedef struct s_fdf_struct {
	int w_width;
	int w_height;
	t_xvar *mlx_app;
	t_win_list *main_win;
	t_list_node *map;
	int cols;
	int rows;
	int case_size;
	int z_size;
	int max_height;
	char *filename;
	int custom_colour;
} t_fdf_struct;

int out(int key);
int	main(int argc, char **argv);
void *on_expose (t_fdf_struct * fdf);
void load_data(t_fdf_struct * fdf);
char *get_next_line(int fd);
char **my_str_to_wordtab(char *str);
void data_convert(t_fdf_struct *fdf,t_list_node *node);
void draw_line_d(t_fdf_struct *fdf,int x,int y,int max_x,int max_y,int color1,int color2);
void sub_draw_line_d(t_fdf_struct *fdf,
					 int x,int y,int max_x,int max_y,int color1,int color2,int orientation);

#endif //FT_FDF_H
