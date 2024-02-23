#include "minishell.h"

static int	ft_double_arry_len(char **d)
{
	int	i;

	i = 0;
	while (d[i])
		i++;
	return (i);
}

static void	ft_free_split(char **d)
{
	int	i;

	i = ft_double_arry_len(d);
	while (i > 0)
	{
		free(d[i]);
		i--;
	}
	free(d);
	return ;
}

int	ft_check(char *s)
{
	int		i;
	int		j;
	char	**d;

	i = 0;
	j = 0;
	if (ft_strchr(s, '>') || ft_strchr(s, '<'))
	{
		d = ft_split(s, ' ');
		if (!d || !d[0])
			return (ft_free_split(d), 0);
		i = ft_double_arry_len(d) - 1;
		if (!d[i])
			return (ft_free_split(d), 0);
		j = strlen(d[i]) - 1;
		if (d[i][j] == '>' || d[i][j] == '<')
			return (ft_free_split(d), 0);
		ft_free_split(d);
	}
	return (1);
}

void	ft_exit(char *s)
{
	int	i;

	i = 0;
	if (ft_strlen(s) != 4)
		return ;
	while (i < ft_strlen(s) && s[i] == "exit"[i])
		i++;
	if (i == 4)
	{
		free(s);
		exit(0);
	}
	return ;
}

int	main(void)
{
	char	*s;
	char	*p;

	while (1)
	{
		s = readline("bash: ");
		ft_exit(s);
		if (ft_check(s))
			printf("%s\n", s);
		else
			printf("bash: syntax error near unexpected token `newline'\n");
		free (s);
	}
	return (0);
}
