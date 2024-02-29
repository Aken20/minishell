#include "minishell.h"

char	*ft_remove_wrong_var(char *s)
{
	int	len_befor;
	int	len_after;
	int	i;
	int	j;
	char *n_s;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '$')
		i++;
	len_befor = i;
	while (s[i] && s[i] != ' ')
		i++;
	int stop = i;
	while (s[i++])
		j++;
	len_after = j;
	n_s = malloc(len_befor + len_after + 1);
	ft_strlcpy(n_s, s, len_befor + 1);
	ft_strlcpy(n_s + len_befor, s + stop, len_after + 1);
	return (free(s) , n_s);
}

char	*ft_replace_env(char *s, char *env)
{
	int	len_befor;
	int	var_len;
	int	len_after;
	int	i;
	int	j;
	char *n_s;

	var_len = ft_strlen(ft_strchr(env, '=') + 1);
	i = 0;
	j = 0;
	while (s[i] && s[i] != '$')
		i++;
	len_befor = i;
	while (s[i] && s[i] != ' ')
		i++;
	int stop = i;
	while (s[i++])
		j++;
	len_after = j;
	n_s = malloc(len_befor + len_after + var_len + 1);
	ft_strlcpy(n_s, s, len_befor + 1);
	ft_strlcpy(n_s + len_befor, ft_strchr(env, '=') + 1, var_len + 1);
	ft_strlcpy(n_s + len_befor + var_len, s + stop, len_after + 1);
	return (free(s) , n_s);
}

char	*ft_check_env(char *s, char	**env)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	if (!s[i] || !ft_strchr(s, '$'))
		return (s);
	p = ft_strchr(s, '$') + 1;
	if (!p[i] || p[i] == '(')
		return (s);
	while (env[i])
	{
		if (env[i][j] == p[j])
		{
			while (p[j] && env[i][j] && p[j] != ' ' && p[j] == env[i][j])
				j++;
			if (env[i][j] == '=' && (!p[j] || p[j] == ' '))
				return (ft_check_env(ft_replace_env(s, env[i]), env));
		}
		j = 0;
		i++;
	}
	return (ft_check_env(ft_remove_wrong_var(s), env));
}

// void	ft_exit(char *s)
// {
// 	int	i;

// 	i = 0;
// 	if (ft_strlen(s) != 4)
// 		return ;
// 	while (i < ft_strlen(s) && s[i] == "exit"[i])
// 		i++;
// 	if (i == 4)
// 	{
// 		free(s);
// 		rl_clear_history();
// 		exit(0);
// 	}
// 	return ;
// }

// int	main(int ac, char **av, char **env)
// {
// 	char	*s;
// 	char	*p;
// 	int		i;

// 	i = 0;
// 	while (env[i])
// 		printf("%s\n", env[i++]);
// 	while (1)
// 	{
// 		s = readline("bash: ");
// 		add_history(s);
// 		ft_exit(s);
// 		s = ft_check_env(s, env);
// 		if (s)
// 		{
// 			printf("%s\n", s);
// 			free (s);
// 		}
// 	}
// 	return (0);
// }
