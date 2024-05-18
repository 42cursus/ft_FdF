/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_str_to_wordtab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 01:11:37 by abelov            #+#    #+#             */
/*   Updated: 2024/05/18 01:11:37 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"


char ** my_str_to_wordtab(char *str)

{
	size_t length;
	bool is_space;
	int i;
	int j;
	char **str_tab;

	length = strlen(str);
	i = 0;
	j = 0;
	while (j < (int)length) {
		while (str[j] == ' ')
			j = j + 1;
		if (str[j] != '\0')
			i = i + 1;
		while( true ) {
			is_space = false;
			if (str[j] != '\0')
				is_space = str[j] != ' ';
			if (!is_space) break;
			j = j + 1;
		}
	}
	str_tab = (char **)malloc((long)(i + 1) << 3);
	if (str_tab == NULL)
		str_tab = NULL;
	else {
		i = 0;
		j = 0;
		while (j < (int) length) {
			while (str[j] == ' ') {
				str[j] = '\0';
				j = j + 1;
			}
			if (str[j] != '\0') {
				str_tab[i] = str + j;
				i = i + 1;
			}
			while (true) {
				is_space = false;
				if (str[j] != '\0') {
					is_space = str[j] != ' ';
				}
				if (!is_space) break;
				j = j + 1;
			}
		}
		str_tab[i] = NULL;
	}
	return str_tab;
}
