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

bool ft_check_char_after_direction(char	*s)
{
	int i;

	i = 0;
	while (s[i] == ' ')
		i++;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '<' || s[i] == '>')
			i++;
		else
			return (true);
	}
	return (false);
}

int	ft_check_redirections_2(char *s, int j, char c)
{
	int		i;

	i = 0;
	if (s[i] == '<' && c == '<')
		i++;
	while(s[i] == ' ')
		i++;
	if (s[i] == c)
	{
		i++;
		j++;
	}
	if (s[i] == c)
	{
		i++;
		j++;
	}
	while (s[i] == ' ')
		i++;
	if (s[i] && (s[i] == '<' || s[i] == '>'))
		return (0);
	return (j);
}

int	ft_check_redirections(char *s, int j)
{
	int		i;

	i = 0;
	if (!s[i] || !(ft_strchr(s, '>') || ft_strchr(s, '<')))
		return (j);
	while (s[i])
	{
		if (s[i] && s[i] == '>')
		{
			j = ft_check_redirections_2(s + i, j, '>');
			if (j == 0 || !ft_check_char_after_direction(s + i))
				return (printf("bash: syntax error near unexpected token\n"));
			i += j - 1;
		}
		else if (s[i] && s[i] == '<')
		{
			j = ft_check_redirections_2(s + i, j, '<');
			if (j == 0 || !ft_check_char_after_direction(s + i))
				return (printf("bash: syntax error near unexpected token\n"));
			i += j - 1;
		}
		i++;
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

// int	main(int ac, char **av, char **env)
// {
// 	char	*s;
// 	char	*p;
// 	int		i;

// 	i = 0;
// 	while (1)
// 	{
// 		s = readline("bash: ");
// 		add_history(s);
// 		ft_exit(s);
// 		if (ft_check_redirections(s, 1))
// 		{
// 			printf("%s\n", s);
// 			free (s);
// 		}
// 	}
// 	return (0);
// }
