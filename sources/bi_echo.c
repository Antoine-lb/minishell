#include "../includes/minishell.h"

int     bi_echo(char **args) {
    int     a;
    int     b;

    a = 1;
    b = 1;
    if (ft_strcmp(args[a], "-n") == 0) {
        b = 0;
        a++;
    }
    while (args[a] != NULL) {
        ft_putstr_fd(args[a], 1);
        ft_putchar_fd(' ', 1);
        a++;
    }
    if (b == 1)
        ft_putchar_fd('\n', 1);
    return (1);
}