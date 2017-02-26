
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft/include/libft.h"

extern char **environ;

static int	ft_strcmpi(unsigned char *s1, unsigned char *s2)
{
	int     i;

	i = 0;
	while (*(s1 + i) == *(s2 + i) && *(s2 + i) != '\0')
		i++;
	if (*(s2 + i) == '\0')
		return (0);
	return (*(s1 + i) - *(s2 + i));
}

static char	*ft_strjoini(char const *s1, char const *s2, char c)
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

int			exe(char *argv)
{
	int		count = 0;
	char	**path;
	char	**av;
	pid_t	pid;
	int ret;

	ret = 1;
	pid = fork();
	if (pid == 0)
	{
		//ft_putnbr(getpid());
		av = ft_strsplit(argv, ' ');
		if (!access(*av, X_OK))
			ret = execve(*av, av, environ);
		else
		{
			while(ft_strcmpi((unsigned char *)environ[count], (unsigned char *)"PATH"))
				count++;
			path = ft_strsplit(*(environ + count) + 5, ':');
			count = -1;
			while (*(path + ++count) && access(ft_strjoini(*(path + count), *av, '/'), F_OK))
				;//printf("%s\n", ft_strjoini(*(path + count), *av, '/'));
			if (*(path + count))
				ret = execve(ft_strjoini(*(path + count), *av, '/'), av, environ);
			else
				write(1, "\x1b[31m", 6);
		}
		exit(1);
	}
	else
		wait(&ret);
	//ft_putnbr(WEXITSTATUS (ret));
	return ret;
}
