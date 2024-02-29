# include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*s;
	int		i;

	i = 0;
	while (1)
	{
		s = readline("bash: ");
		add_history(s);
		ft_exit(s);
        s = ft_check_env(s, env);
		if (parsing(s, env) == true)
		{
			printf("%s\n", s);
			free (s);
		}
        else
            free (s);
	}
	return (0);
}
