/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 00:31:19 by tdumouli          #+#    #+#             */
/*   Updated: 2017/04/13 21:09:32 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 1
# define SHELL "mini"

typedef struct s_data {
	char    *str;
	int     len;
	int     pointeur;
} t_data;
/*
** termcaps
*/
char	*saisie(void);
void	clean(t_data *blk);
void	yolo(int dir, int y);
t_data	*t_dat_init(void);
/*
** main
*/
int		sheel(char **av, char ***env);
int		exe(char *av, char ***env);
/*
** environement
*/
int		env_search(char *name, char **env);
void	env_add(char *s, char *ds, char ***env);
char	**env_ralloc(int diff, char **env);
void	env_lvlup(char ***env);
int		env_sup(char *name, char ***env);
void	env_free(char ***env);
void	env_print(char **env);
/*
** utils
*/
int		insert_home(char **s, int r, char **env);
int		variable(char **s, int symb, char **env);
int		is_dir(char *s);
int		new_process(char **av, char ***env, char *error);

char	*ft_strjoini(char const *s1, char const *s2, char c);
void	freeteuse(void **s, int niveau);
void	whereareyou(char *name, char ***env);
int		supersplit(char ****ret, char *av, char s1, char s2);
void	erreur(char *a, char *s, char *d);
/*
** built in
*/

/*
** cd.h
*/
void	pwd_short(char **pwd);
void	cd(char *av, char ***env);
void	built_cd(char **av, char ***env);

void	ft_setenv(char **av, char ***env);

void	ft_echo(char **av);
#endif
