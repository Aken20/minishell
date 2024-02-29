#include "minishell.h"

bool parsing(char *s, char **env)
{
    if (ft_check_redirections(s, 1) == 41)
        return (false);
    if (ft_check_builtins(s, env))
        return (false);
    return (true);
}
