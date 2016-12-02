/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trmoreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:44:31 by trmoreau          #+#    #+#             */
/*   Updated: 2016/12/01 19:13:50 by trmoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	**tetri;
	int		tnb;

	if (argc != 2)
		error(ERRARG);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error(ERRFILE);
	tetri = pars_it(fd, tetri);
	if (close(fd) == -1)
		error(ERRCLO);
	tnb = count_tab(tetri);
	fillit(tetri, tnb);
	tnb = 0;
	while (tetri[tnb] != NULL)
	{
		free(tetri[tnb]);
		++tnb;
	}
	free(tetri);
	return (0);
}
