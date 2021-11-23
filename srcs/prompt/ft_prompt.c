/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:35:54 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:35:55 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *join_prompt_element(char *begin, char *pwd, char *end, t_shell *shell)
{
	char *tmp;
	char *prompt;

	tmp = ft_strjoin(begin, pwd);
	prompt = ft_strjoin(tmp, end);
	ft_add_to_garbage(tmp, shell);
	ft_add_to_garbage(begin, shell);
	ft_add_to_garbage(pwd, shell);
	ft_add_to_garbage(end, shell);
	ft_add_to_garbage(tmp, shell);
	return (prompt);
}

char *create_prompt(t_shell *shell)
{
	char *pwd;
	char *result;
	char *buffer;
	char *home_path;

	buffer = NULL;
	home_path = get_env_object("HOME", shell)->value;
	pwd = get_env_object("PWD", shell)->value;
	if (ft_strlen(pwd) >= ft_strlen(home_path))
		pwd += ft_strlen(home_path);
	result = join_prompt_element(ft_strdup("~"),
								 ft_strdup(pwd), ft_strdup("$ "), shell);
	return (result);
}

char *start_prompt(t_shell *shell, char *cmd)
{
	char *prompt;

	prompt = create_prompt(shell);
	cmd = readline(prompt);
	if (cmd == NULL)
		exit(EXIT_SUCCESS);
	ft_add_to_garbage(prompt, shell);
	return (cmd);
}
