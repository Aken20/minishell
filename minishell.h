

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include "libft/libft.h"


void	ft_exit(char *s);
char	*ft_check_env(char *s, char	**env);
int     ft_check_redirections(char *s, int j);
int     ft_check_builtins(char *s, char **env);
bool    parsing(char *s, char **env);
