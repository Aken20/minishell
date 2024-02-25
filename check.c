#include "minishell.h"

// static int	ft_double_arry_len(char **d)
// {
// 	int	i;

// 	i = 0;
// 	while (d[i])
// 		i++;
// 	return (i);
// }

// static void	ft_free_split(char **d)
// {
// 	int	i;

// 	i = ft_double_arry_len(d);
// 	while (i > 0)
// 	{
// 		free(d[i]);
// 		i--;
// 	}
// 	free(d);
// 	return ;
// }

int	ft_check2(char *s);

bool ft_check_char(char	*s)
{
	int i;

	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '<' || s[i] == '>')
		ft_check2(s);
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '<' || s[i] == '>')
			i++;
		else
			return (true);
	}
	return (false);
}

int	ft_check2(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (s[i])
	{
		while(s[i] == ' ')
			i++;
		if (s[i] == '>')
		{
			if (s[i + 1] == '>')
				return (printf("bash: syntax error near unexpected token `>>'\n"));
			else
				return (printf("bash: syntax error near unexpected token `>'\n"));
		}
		else if (s[i] == '<')
		{
			if (s[i + 1] == '<' && s[i + 2] == '<')
				return (printf("bash: syntax error near unexpected token `<<<'\n"));
			if (s[i + 1] == '<')
				return (printf("bash: syntax error near unexpected token `<<'\n"));
			else
				return (printf("bash: syntax error near unexpected token `<'\n"));
		}
		i++;
	}
	return (j);
}

int	ft_check(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (ft_strchr(s, '>') || ft_strchr(s, '<'))
	{
		while (s[i])
		{
			while(s[i] == ' ')
				i++;
			if (s[i] == '>')
			{
				if (ft_check_char(s + i) == true)
					break;
				if (s[i] == '>')
					i++;
				if (ft_check_char(s + i) == true && s[i] != '>')
					break;
				j = ft_check2(s + i);
				if (j == 1)
					return (printf("bash: syntax error near unexpected token `newline'\n"));
				else
					return (j);
			}
			else if (s[i] == '<')
			{
				if (s[++i] == '<')
					i++;
				if (s[i] == '<')
					i++;
				if (ft_check_char(s + i) == true && s[i] != '<')
					break;
				j = ft_check2(s + i);
				if (j == 1)
					return (printf("bash: syntax error near unexpected token `newline'\n"));
				else
					return (j);
			}
			i++;
		}
	}
	return (j);
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
		rl_clear_history();
		exit(0);
	}
	return ;
}

int	main(int ac, char **av, char **env)
{
	char	*s;
	char	*p;
	int		i;

	i = 0;
	// while (env[i])
	// 	printf("%s\n", env[i++]);
	while (1)
	{
		s = readline("bash: ");
		add_history(s);
		ft_exit(s);
		if (ft_check(s) == 1)
		{
			printf("%s\n", s);
			free (s);
		}
	}
	return (0);
}
