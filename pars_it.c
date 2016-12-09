/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trmoreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 15:13:39 by trmoreau          #+#    #+#             */
/*   Updated: 2016/12/09 13:51:53 by trmoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		count_tetri(char *str, int i, int x, int y)
{
	if (str[ft_strlen(str) - 1] == str[ft_strlen(str) - 2])
		error(ERRERR);
	while (str[++i] != '\0')
	{
		if (++x == 4)
		{
			if (str[i] == '\n')
				++i;
			else
				error(ERRERR);
			x = 0;
			y++;
		}
		if (y == 4)
		{
			if (str[i] == '\n' || str[i] == '\0')
				i++;
			else
				error(ERRERR);
			y = 0;
		}
	}
	if (x != 0 || y != 0)
		error(ERRERR);
	return (i / 21);
}

char	**temp_to_final(char *temp, int tnb, int i, int i2)
{
	char	**tetri;

	if ((tetri = malloc((tnb * sizeof(char *)) + 1)) == NULL)
		error(ERRALOC);
	tetri[tnb] = NULL;
	while (i < tnb)
	{
		if ((tetri[i++] = malloc(17 * sizeof(char))) == NULL)
			error(ERRALOC);
		tetri[i - 1][16] = '\0';
	}
	i = 0;
	tnb = 0;
	while (temp[i] != '\0')
	{
		if (temp[i] != '\n')
			tetri[i2][tnb++] = temp[i];
		if (((i + 1) % 21) == 0)
		{
			tnb = 0;
			++i2;
		}
		++i;
	}
	return (tetri);
}

void	check_err(char **tetri, int y, int x, int i)
{
	int	ok;
	int	fok;

	while (tetri[++y] != NULL)
	{
		fok = 0;
		while ((tetri[y][++x] != '\0') && (tetri[y][x] == '.'
			|| tetri[y][x] == '\n' || tetri[y][x] == '#'))
			if (tetri[y][x] == '#')
			{
				if ((ok = check_arround(tetri, x, y)) > 0)
				{
					++i;
					if (ok > 1)
						fok = ok;
				}
				else
					error(ERRERR);
			}
		if (fok <= 1 || i != 4 || tetri[y][x] != '\0')
			error(ERRERR);
		i = 0;
		x = -1;
	}
}

void	hash_to_ascii(char **tetri)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	x = 0;
	c = 'A';
	while (tetri[y] != NULL)
	{
		while (tetri[y][x] != '\0')
		{
			if (tetri[y][x] == '#')
				tetri[y][x] = c;
			++x;
		}
		++c;
		++y;
		x = 0;
	}
	if (c > 'Z' + 1)
		error(ERREXPLOSION);
}

char	**pars_it(int fd, char **tetri)
{
	char	*temp;
	int		len;
	int		tnb;

	if ((temp = malloc(BUFFSIZE + 1)) == NULL)
		error(ERRALOC);
	len = read(fd, temp, BUFFSIZE + 1);
	if (len == (BUFFSIZE + 1))
		error(ERRERR);
	temp[len] = '\0';
	if ((tnb = count_tetri(temp, 0, 0, 0)) == 0)
		error(ERRERR);
	tetri = temp_to_final(temp, tnb, 0, 0);
	free(temp);
	check_err(tetri, -1, -1, 0);
	hash_to_ascii(tetri);
	return (tetri);
}
