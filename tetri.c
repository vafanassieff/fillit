/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetri.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trmoreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:59:38 by trmoreau          #+#    #+#             */
/*   Updated: 2016/12/01 18:52:22 by trmoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Compte combien de fois on peut reduire x par 4
*/

int		how_many_four(int x)
{
	int	ret;

	ret = 0;
	while (x >= 4)
	{
		x -= 4;
		++ret;
	}
	return (ret);
}

/*
** Recupere la position
*/

int		get_orig(char *tetri)
{
	int	i;

	i = 0;
	while (tetri[i] == '.')
		++i;
	return (i);
}

/*
** Check la emptynivation des position dans le carre
*/

int		is_ok(char **square, char *tetri, int x, int y)
{
	int	i;
	int	orig;
	int	size;

	orig = get_orig(tetri);
	size = ft_count_line(square);
	i = orig - 1;
	while (tetri[++i] != '\0')
		if (tetri[i] != '.')
		{
			if ((y + how_many_four(i) - how_many_four(orig)) >= size
				|| (x + ((i % 4) - (orig % 4))) >= size
				|| square[y + how_many_four(i) - how_many_four(orig)]
				[x + ((i % 4) - (orig % 4))] != '.')
				return (1);
		}
	return (0);
}

/*
** Place un tetrimino dans le carre selon la position relative
** des bloc par rapport a l'origine du tetrimino
*/

char	**put_tetri(char **square, char *tetri, int x, int y)
{
	char	c;
	int		i;
	int		orig;
	int		size;

	orig = get_orig(tetri);
	size = ft_count_line(square);
	i = orig - 1;
	while (tetri[++i] != '\0')
		if (tetri[i] != '.')
		{
			square[y + how_many_four(i) - how_many_four(orig)]
				[x + ((i % 4) - (orig % 4))] = tetri[i];
		}
	return (square);
}

/*
** ALLER DEGAGE
*/

char	**remove_tetri(char **square, int x, int y, char *tetri)
{
	char	c;

	c = tetri[get_orig(tetri)];
	while (square[y] != NULL)
	{
		while (square[y][x] != '\0')
		{
			if (square[y][x] == c)
				square[y][x] = '.';
			++x;
		}
		x = 0;
		++y;
	}
	return (square);
}
