/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trmoreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 14:21:05 by trmoreau          #+#    #+#             */
/*   Updated: 2016/12/01 19:33:04 by trmoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[++i] != '\0')
		;
	return (i);
}

void	error(char *err_msg)
{
	if (err_msg != NULL)
		write(1, err_msg, ft_strlen(err_msg));
	exit(1);
}

void	aff_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i] != NULL)
	{
		write(1, tab[i], ft_strlen(tab[i] - 1));
		write(1, "\n", 1);
	}
}

int		count_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		++i;
	return (i);
}

int		check_arround(char **tetri, int x, int y)
{
	return (((x - 1) >= 0 && tetri[y][x - 1] == '#')
			+ ((x - 4) >= 0 && tetri[y][x - 4] == '#')
			+ ((x + 1) <= 15 && tetri[y][x + 1] == '#')
			+ ((x + 4) <= 15 && tetri[y][x + 4] == '#'));
}
