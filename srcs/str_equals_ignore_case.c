#include "../includes/minishell.h"

int str_equals_ignore_case(char *text_1, char *text_2)
{
	int e;

	e = 0;
	if (ft_strlen(text_1) == 0 || ft_strlen(text_2) == 0)
		return (0);
	while (ft_tolower(text_1[e]) == ft_tolower(text_2[e]))
			e++;
	if (ft_strlen(text_1) == (size_t)e - 1)
		return (1);
	return (0);
}