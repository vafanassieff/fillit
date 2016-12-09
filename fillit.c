/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trmoreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 15:15:09 by trmoreau          #+#    #+#             */
/*   Updated: 2016/12/01 19:22:26 by trmoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		resolve(char **tetri, char **square, int i)
{
	int		x;
	int		y;
	char	*tetrilol;

	if (!tetri[i])
		return (1);
	y = -1;
	tetrilol = tetri[i];
	while (++y < ft_count_line(square))
	{
		x = 0;
		while (x < ft_count_line(square))
		{
			if (is_ok(square, tetrilol, x, y) == 0)
			{
				square = put_tetri(square, tetrilol, x, y);
				if (resolve(tetri, square, i + 1) == 1)
					return (1);
				else
					remove_tetri(square, 0, 0, tetrilol);
			}
			x++;
		}
	}
	return (0);
}

void	fillit(char **tetri, int tnb)
{
	char	**square;
	int		size;

	size = ft_square(tnb * 4);
	square = new_square(size);
	while (resolve(tetri, square, 0) == 0)
	{
		size++;
		free_square(square);
		square = new_square(size);
	}
	aff_tab(square);
}
