# include "minishell.h"

int main() {
    char *s;
    char *p;

    while (1)
    {
        s = readline("bash: ");
        if (ft_strchr(s, '"'))
        {
            p = ft_strchr(s, '"') + 1;
                while (!ft_strchr(p, '"'))
                {
                    s = ft_strjoin(s, "\n");
                    s = ft_strjoin(s, readline("quote> "));
                    // s = readline("quote> ");
                    p = ft_strchr(s, '"') + 1;
                }
        }
        printf("%s: command not found\n", s);
        free (s);
    }
    return 0;
}
