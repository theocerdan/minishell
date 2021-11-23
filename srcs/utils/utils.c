/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:50:39 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:50:40 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int get_size(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int ft_is_special(char c)
{
	if ((c >= 33 && c <= 47) || (c >= 123 && c <= 126) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96))
		return (1);
	return (0);
}

int ft_is_uppercase(char c)
{
	if (c >= 65 && c <= 90)
		return (1);
	return (0);
}

int ft_is_lowercase(char c)
{
	if (c >= 97 && c <= 122)
		return (1);
	return (0);
}

char *lower_str(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_is_uppercase(str[i]))
			str[i] = str[i] + 32;
		i++;
	}
	return (str);
}

int count_spacing(char c, char *text)
{
	char **malaga = ft_split(text, c);
	int i = 0;
	while (malaga[i])
		i++;

	return (i);
}

//

char    *ft_strdup_clean(t_shell *shell, const char *s1)
{
    char *ret;
    ret = ft_strdup(s1);
    ft_add_to_garbage(ret, shell);
    return (ret);
}
char    *ft_strjoin_clean(t_shell *shell, const char *s1, const char *s2)
{
    char *ret;
    ret = ft_strjoin(s1, s2);
    ft_add_to_garbage(ret, shell);
    return (ret);
}
char    *ft_substr_clean(t_shell *shell, char const *s, unsigned int start, size_t len)
{
    char *ret;
    ret = ft_substr(s, start, len);
    ft_add_to_garbage(ret, shell);
    return (ret);
}
char    **ft_split_clean(t_shell *shell, char const *s, char c)
{
    char **ret;
    int i;
    i = 0;
    ret = ft_split(s, c);
    while (ret[i])
    {
        ft_add_to_garbage(ret[i], shell);
        i++;
    }
    ft_add_to_garbage(ret, shell);
    return (ret);
}
