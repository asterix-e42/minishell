/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envie.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:31:38 by tdumouli          #+#    #+#             */
/*   Updated: 2017/03/01 16:43:54 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include "mini.h"

extern char **environ;

static int	ft_strcmpi(char *s1, char *s2)
{
	int     i;

	i = 0;
	while (*(s1 + i) == *(s2 + i) && *(s2 + i) != '\0')
		i++;
	if (*(s2 + i) == '\0')
		return (0);
	return (*(s1 + i) - *(s2 + i));
}

int			env_search(char *name, char **env)
{
	int count;

	count = 0;
	while(*(environ + count) && ft_strcmp((char *)environ[count], name) != '=')
         count++;
	return(count);
}

char		**env_ralloc(int diff, char **env)
{
	char	**new;
	int		lenght;

	lenght = -1;
	while(*(env + ++lenght))
		;//printf("%s\n", *(env + lenght));
	new = (char **)malloc(sizeof(char *) * (lenght + diff + 1));
	*(new + lenght + diff) = NULL;
	while (--lenght != -1)
		if ((*(new + lenght) = (char *)malloc(ft_strlen(*(env + lenght)))))
			*(new + lenght) = ft_strcpy(*(new + lenght), *(env + lenght));
		else
			return (NULL);
	return (new);
}
	
void		env_add(char *name, char *new, char ***env)
{
	int		where;
	char	*tmp;

	where = env_search(name, *env);
		printf("%d\n", where);
	if (!(*env)[where])
		*env = env_ralloc(1, *env);
	else
		free(*(*env + where));
	*(*env + where) = ft_strjoini(name, new, '=');
}

void		env_lvlup(char **env)
{
	int		where;
	char	*name;

	name = "SHLVL";
	where = env_search(name, env);
	if (*(*(env + where) + ft_strlen(*(env + where)) -1) == '9')
		printf("chiant\n");
		//*env = env_ralloc(1, *env);
	else
		++*(*(env + where) + ft_strlen(*(env + where)) -1); 
	//	free((*env)[where]);
//	*(*env + where) = ft_strjoini(name, new, '=');
}
