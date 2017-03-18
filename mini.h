/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 00:31:19 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/18 21:52:52 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <fcntl.h>
# include <unistd.h>
# include "src/libft/include/libft.h"
# include <stdlib.h>

# define BUFF_SIZE 1
# define SHELL "mini"

int		get_next_line(const int fd, char **line);

int		sheel(char **av, char ***env);
int		exe(char *av, char ***env);
char	*ft_strjoini(char const *s1, char const *s2, char c);

int		env_search(char *name, char **env);
void	env_add(char *s, char *ds, char ***env);
char	**env_ralloc(int diff, char **env);
void	env_lvlup(char ***env);
int		env_sup(char *name, char ***env);
void	env_free(char ***env);
void	env_print(char **env);

void	pwd_short(char **pwd);
void	cd(char *av, char **env);

int		insert_home(char **s, int r, char **env);
int		variable(char **s, int symb, char **env);
int		is_dir(char *s);
int		new_process(char **av, char **env, char *error);

void	freeteuse(void **s, int niveau);
void	whereareyou(char *name, char ***env);
int		supersplit(char ****ret, char *av, char s1, char s2);
void	erreur(char *s, char *d);
#endif
