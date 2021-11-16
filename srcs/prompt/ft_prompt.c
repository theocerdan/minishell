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

char *join_prompt_element(char *begin, char *pwd, char *end)
{
	char *tmp;
	char *prompt;

	tmp = ft_strjoin(begin, pwd);
	prompt = ft_strjoin(tmp, end);
	free(tmp);
	free(begin);
	free(pwd);
	free(end);
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
	pwd = getcwd(buffer, 0);
	if (ft_strlen(pwd) >= ft_strlen(home_path))
	{
		pwd += ft_strlen(home_path);
	}
	result = join_prompt_element(ft_strdup("~"),
								 ft_strdup(pwd), ft_strdup("$ "));
	return (result);
}

char *start_prompt(t_shell *shell, char *cmd)
{
	char *prompt;

	//(void)(shell);
	prompt = create_prompt(shell);
	// prompt = "";
	cmd = readline(prompt);
	if (cmd == NULL)
		exit(EXIT_SUCCESS);
	free(prompt);
	return (cmd);
}
