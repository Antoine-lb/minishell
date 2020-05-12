#include "../libft/libft.h"
#include "../includes/command.h"

int	    last_exit_code(int val)
{
	static int last_val;

	if (val > 0)
		last_val = val;
	return (last_val);
}

int     ft_string(char *str, int b) 
{
    static int  a;
    static int  c;

    if (c != 0) {
        a = (int)(str[b - 1]);
        c = 0;
    }
    if ((int)(str[b]) == 39 || (int)(str[b]) == 34)
	{
		if (a == 0 && ((int)(str[b - 1]) != 92 || b == 0))
			c = (int)(str[b]);
		else if (((int)(str[b]) == 39 ||
					(int)(str[b]) == 34) && ((int)str[b - 1]) != 92)
			a = 0;
	}
    if (a != 0)
        return (a);
    return (0);
}

void    ft_parser(t_parser **psr, char ***env, char c, int d) 
{
    char            *tmp;
    char            buf[2];
    static int      escape;
    static char     *var;
    int             size;

    buf[0] = c;
    buf[1] = '\0';
    size = ft_strlen((*psr)->command) - 1;
    if (var != NULL && d != 39) 
    {
        if (!ft_isalnum(c) && c != '_') 
        {
            if (ft_strcmp(var, "\0") == 0 && c == '?') {
                escape = 1;
                tmp = ft_strjoin((*psr)->command, ft_itoa(last_exit_code(-1)));
            }
            else {
                if ((c == '=' || c == 34) && ft_strlen(var) == 0) {
                    tmp = ft_strjoin((*psr)->command, ft_strdup("\\$"));
                } else
                    tmp = ft_strjoin((*psr)->command, get_env_var_value(var, env));
            }
            free((*psr)->command);
            (*psr)->command = tmp;
            free(var);
            var = NULL;
        }
        else 
            var = ft_strjoin(var, buf);
    }
    if (c == '$' && ((*psr)->command)[size] != 92 && d != 39)
        var = ft_strdup("");
    else if (var == NULL && c != '\0')
    {
        if (escape == 0) {
            tmp = ft_strjoin((*psr)->command, buf);
            free((*psr)->command);
            (*psr)->command = tmp;
        } else {
            escape = 0;
        }
    }
}

int		command(t_parser **psr, char **line, char ***env) 
{
    int             a;
    static int      b;
    int             c;
    int             d;

    a = b;
    c = 0;
    d = 0;
    *psr = (t_parser *)malloc(sizeof(t_parser));
    (*psr)->command = ft_strdup("");
    while ((*line)[a + 1])
    {
        if ((d = ft_string(*line, a)) == 0)
        {
            if ((c = ft_getnext(";|<>", 0, (*line)[a])) < 4 && (*line)[a - 1] != 92) 
            {
                if ((((*line)[a] == (*line)[a + 1]) || (ft_includes(ft_strtrim((*line), " ")[0], ";|"))) && c < 3)
                {
                    ft_putstr_fd("Error: syntax error near unexpected token\n", 0);
                    exit(2);
                }
                if (c == 3 && (*line)[a + 1] == '>')
                    c = 4;
                (*psr)->sep = c;
                if (c == 4)
                    a++;
                b = a + 1;
                (*psr)->sep++;
                if (ft_strcmp((*psr)->command, ";") == 0 || ft_strcmp((*psr)->command, "|") == 0)
                {
                    ft_putstr_fd("Error: syntax error near unexpected token\n", 0);
                    exit(2);
                }
                return (1);
            }
            if ((*line)[a] != 92 || ((*line)[a] == 92 && (*line)[a + 1] == 32) || ft_includes((*line)[a + 1], "$\'\"")) {
                ft_parser(psr, env, (*line)[a], d);
                if ((*line)[a] == 92) {
                    a = ft_getnnext((*line), a + 1, ' ') - 1;
                    if (ft_includes((*line)[a + 1], "$\'\""))
                        a++;
                    ft_parser(psr, env, (*line)[a], d);
                }
            }
        } else {
            ft_parser(psr, env, (*line)[a], d);
        }
        a++;
    }
    (*psr)->sep = -1;
    ft_parser(psr, env, (*line)[a], d);
    ft_parser(psr, env, (*line)[a + 1], d);
    (*psr)->command = ft_strtrim((*psr)->command, " ");
    if (ft_strcmp((*psr)->command, ";") == 0 || ft_strcmp((*psr)->command, "|") == 0 || ft_strcmp((*psr)->command, "<") == 0)
    {
        ft_putstr_fd("Error: syntax error near unexpected token\n", 0);
        exit(2);
    }
    b = 0;
    return (0);
}