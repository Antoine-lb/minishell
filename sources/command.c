#include "../libft/libft.h"
#include "../includes/command.h"

int     ft_string(char *str, int b) 
{
    static int  a;

    if ((int)(str[b]) == 39 || (int)(str[b]) == 34)
	{
		if (a == 0 && ((int)(str[b - 1]) != 92 || b == 0))
			a = (int)(str[b]);
		else if (((int)(str[b]) == 39 ||
					(int)(str[b]) == 34) && ((int)str[b - 1]) != 92)
			a = 0;
	}
    if (a != 0)
        return (1);
    return (0);
}

t_parser    *ft_parser(char *str, int sep) 
{
    t_parser *psr;

    psr = (t_parser *)malloc(sizeof(t_parser));
    psr->sep = sep;
    if (psr->sep >= 0)
        psr->sep++;
    psr->command = ft_strtrim(str, " ");
	free(str);
    return (psr);
}

int		command(t_parser **psr, char **line) 
{
    int             a;
    static int      b;
    int             c;

    a = b;
    c = 0;
    while ((*line)[a + 1])
    {
        if (ft_string(*line, a) == 0 && (c = ft_getnext(";|<>", 0, (*line)[a])) < 4) 
        {
            if (c == 3 && (*line)[a + 1] == '>')
                c = 5;
            *psr = ft_parser(ft_substr((*line), b, a - b), c);
            if (c == 5)
                a++;
            b = a + 1;
            return (1);
        }
        a++;
    }
    *psr = ft_parser(ft_substr((*line), b, a - b + 1), -1);
    b = 0;
    return (0);
}