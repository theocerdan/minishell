/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:44:26 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 14:44:27 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_token(void *ptr)
{
	t_token	*token_list;

	token_list = (t_token *)ptr;
	printf("%d=%s\n", token_list->type, token_list->value);
}

void	print_all_token(t_shell *shell)
{
	ft_lstiter((shell->token_list), &print_token);
}

void	ft_create_token(int type, char *value, t_shell *shell)
{
	t_token	*token;

	token = ft_safe_malloc(sizeof(t_token), shell);
	token->type = type;
	token->value = value;
	ft_lstadd_front(&(shell->token_list), ft_lstnew(token));
}

void	init_token(t_shell *shell, char *cmd)
{
	int		i;
	int		type;
	char	*value;
	char	**each_cmd;

	i = 0;
	each_cmd = ft_split(cmd, ' ');
	while (each_cmd[i])
	{
		type = define_type(each_cmd[i]);
		value = each_cmd[i];
		ft_create_token(type, value, shell);
		i++;
	}
}
