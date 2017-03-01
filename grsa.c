
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/include/libft.h"
#include "mini.h"

extern char **environ;

char	*ft_strjoini(char const *s1, char const *s2, char c)
{
	char    *ret;
	int     i;
	int     j;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(ret = (char *)malloc(sizeof(char) * (i + j + 2))))
		return (NULL);
	*(ret + i + j + 1) = '\0';
	while (j--)
		*(ret + i + j + 1) = *(s2 + j);
	*(ret + i) = c;
	while (i--)
		*(ret + i) = *(s1 + i);
	return (ret);
}

void change(char **s)
{
	int i;

	while (*s)
	{
		i = -1;
		while(*(s + ++i))
			if(*(*s + i) == '$' && *(*s + i + 1))
				;
			else if(*(*s + i) == '*')
				;
		++s;
	}
}

void build(char **av, char **env)
{
	char	*tmp;

	if (!ft_strcmp(*av, "cd"))
	{
		tmp = *(env + env_search("PWD", env));
		if (*(av + 1))
		{
		if (*(av + 2))
			*(ft_strstr(tmp, *(av + 2)) - 1) = '\0';
		printf("1%s\n", tmp);
		tmp = ft_strjoini(tmp + 4, *(av + 1), '/');
		printf("2%s\n", tmp);
		pwd_short(&tmp);
		printf("3%s\n", tmp);
		if (!*tmp && !(*(tmp + 1) = '\0'))
			*tmp = '/';
		env_add("PWD", tmp, &env);
		}
		printf("4%s\n", tmp);
		chdir(tmp);
		free(tmp);
	}	
	write(1, "fd", 2);
}

int			exe(char *argv, char **env)
{
	int		count;
	char	**path;
	char	**av;
	pid_t	pid;

	av = ft_strsplit(argv, ' ');
	pid = fork();
	if (pid == 0)
	{
		//ft_putnbr(getpid());
		change(av);
		if (!access(*av, X_OK))
			execve(*av, av, env);
		path = ft_strsplit(*(env + env_search("PATH", env)) + 5, ':');
		count = -1;
		while (*(path + ++count) && access(ft_strjoini(*(path + count), *av, '/'), F_OK))
			;//printf("%s\n", ft_strjoini(*(path + count), *av, '/'));
		if (*(path + count))
			execve(ft_strjoini(*(path + count), *av, '/'), av, env);
		exit(1);
	}
	else
		wait(&count);
	write(1, "\x1b[31m", 6);
	if (!WEXITSTATUS (count))
	{
		write(1, "\x1b[39m", 6);
		build(av, env);
	}
	return count;
}
