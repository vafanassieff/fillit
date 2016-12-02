/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trmoreau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 13:45:06 by trmoreau          #+#    #+#             */
/*   Updated: 2016/12/01 19:49:19 by trmoreau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

/*
** Macros pour les messages d'erreur
*/

# define ERRERR	"error\n"
# define ERRARG "Error : wrong number of arguments.\nUsage : ./fillit [file]\n"
# define ERRFILE "Error : can't access the target file.\n"
# define ERRCLO "Error : can't close the target file. Oo\n"
# define ERRALOC "Error : malloc failed (returned NULL)\n"
# define ERREXPLOSION "Error : LE VIETNAM ! LA GUERRE ! AAAAAAAAAAARGHHH !\n"

/*
** Taille maximal du fichier avec X tetriminos
*/

# define BUFFSIZE 545

/*
** Lib
*/

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <unistd.h>

/*
** utility.c
*/

int		ft_strlen(char *str);
void	error(char *err_msg);
void	aff_tab(char **tab);
int		count_tab(char **tab);
int		check_arround(char **tetri, int x, int y);

/*
** pars_it.c
*/

int		count_tetri(char *str, int i, int x, int y);
char	**temp_to_final(char *temp, int tnb, int i, int i2);
void	check_err(char **tetri, int y, int x, int i);
void	hash_to_ascii(char **tetri);
char	**pars_it(int fd, char **tetri);

/*
** util_fillit.c
*/

int		ft_count_line(char **square);
int		ft_square(int n);
char	**new_square(int size);
void	free_square(char **square);

/*
** tetri.c
*/

int		how_many_four(int x);
int		get_orig(char *tetri);
int		is_ok(char **square, char *tetri, int x, int y);
char	**put_tetri(char **square, char *tetri, int x, int y);
char	**remove_tetri(char **square, int x, int y, char *tetri);

/*
** fillit.c
*/

void	fillit(char **tetri, int tnb);
int		resolve(char **tetri, char **square, int i);

#endif
