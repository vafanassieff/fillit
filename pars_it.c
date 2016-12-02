/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trmoreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 15:13:39 by trmoreau          #+#    #+#             */
/*   Updated: 2016/12/01 19:02:06 by trmoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Fonction comtant le nobre de tetrimino et verifiant si le formatage
** du fichier est correcte.
** Oui i, x et y c'est pour la norme.
*/

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

/*
** Convertit le buffer du read en char **, avec 1ligne/tetriminos
** Encore les maleurs de la norme pour i et i2
*/

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

/*
** Check la validitude des tetriminos
** AHAHAAHAHHAHAHAHAHAHAH ! NORME ! AHHAHAHAHAHHAHAHAHAHAHA !
*/

void	check_err(char **tetri, int y, int x, int i)
{
	int	ok;
	int	fok;

	while (tetri[++y] != NULL)
	{
		fok = 0;
		while (tetri[y][++x] != '\0')
		{
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
		}
		if (fok <= 1 || i != 4)
			error(ERRERR);
		i = 0;
		x = -1;
	}
}

/*
** Met des zolis lettre a la place des '#' mdr
*/

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

/*
** "main" du parsing. Renvoie le nombre de tetriminos.
**
** Voici une merveilleuse fanfiction sur Doom
**
** John Stalvern waited. The lights above him blinked and sparked
** out of the air.
** There were demons in the base.
** He didn’t see them, but had expected them now for years.
** His warnings to Cernel Joson were not listenend to and now it was too late.
** Far too late for now, anyway.
** John was a space marine for fourteen years. When he was young he watched
** the spaceships and he said to dad “I want to be on the ships daddy.”
** Dad said “No! You will BE KILL BY DEMONS”
** There was a time when he believed him. Then as he got oldered he stopped.
** But now in the space station base of the UAC he knew there were demons.
** “This is Joson” the radio crackered. “You must fight the demons!”
** So John gotted his palsma rifle and blew up the wall.
** “HE GOING TO KILL US” said the demons
** “I will shoot at him” said the cyberdemon and he fired the rocket missiles.
** John plasmaed at him and tried to blew him up.
** But then the ceiling fell and they were trapped and not able to kill.
** “No! I must kill the demons” he shouted
** The radio said “No, John. You are the demons”
** And then John was a zombie.
*/

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
