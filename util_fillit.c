/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_fillit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafanass <vafanass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 11:33:52 by vafanass          #+#    #+#             */
/*   Updated: 2016/12/01 19:48:16 by trmoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		ft_count_line(char **carre)
{
	int i;

	i = 0;
	while (carre[i])
		i++;
	return (i);
}

int		ft_square(int n)
{
	int	size;

	size = 2;
	while (size * size < n)
		size++;
	return (size);
}

char	**new_square(int size)
{
	char	**square;
	int		i;
	int		j;

	i = 0;
	if (!(square = malloc(size * (sizeof(char *) + 1))))
		return (NULL);
	square[size] = NULL;
	while (i < size)
	{
		if (!(square[i++] = malloc(sizeof(char) * (size + 1))))
			return (NULL);
		square[i - 1][size] = '\0';
	}
	i = 0;
	while (square[i] != NULL)
	{
		j = 0;
		while (j < size)
			square[i][j++] = '.';
		i++;
	}
	return (square);
}

void	free_square(char **square)
{
	int i;
	int j;

	j = 0;
	i = ft_count_line(square);
	while (j < i)
	{
		free(square[j]);
		j++;
	}
	free(square);
}
