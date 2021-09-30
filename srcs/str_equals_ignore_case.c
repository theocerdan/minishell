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


int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}