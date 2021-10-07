#include "../includes/minishell.h"

int     no_need_to_tokenization(char *cmd)
{
	int		i;

	if (cmd[0] == '\0')
		return (1);
	i = 0;
	while (cmd[i] == ' ' || cmd[i] == '\t')
	{
		if (cmd[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

///////////////////////////

int		is_builtin(char *value)
{
	if (!value)
		return (0);
	if (!(ft_strcmp(value, "echo\0")) || !(ft_strcmp(value, "cd\0")))
		return (1);
	if (!(ft_strcmp(value, "pwd")) || !(ft_strcmp(value, "export")))
		return (1);
	if (!(ft_strcmp(value, "unset")) || !(ft_strcmp(value, "env")))
		return (1);
	if (!(ft_strcmp(value, "exit")))
		return (1);
	return (0);
}

int		is_operator(char *value)
{
	if (!(ft_strcmp(value, "|")))
		return (1);
	if (!(ft_strcmp(value, ">")) || !(ft_strcmp(value, "<")))
		return (1);
	if (!(ft_strcmp(value, ">>")) || !(ft_strcmp(value, "<<")))
		return (1);
	return (0);
}

int		define_operator(char *value)
{
	if (!(ft_strcmp(value, "|")))
		return (T_PIPE);
	if (!ft_strcmp(value, ">") || !ft_strcmp(value, "<") || !ft_strcmp(value, ">>"))
		return (T_REDIRECT);
	if (!(ft_strcmp(value, "<<")))
		return (T_REDIRECT);
	return (0);
}

int		define_type(char *value)
{
	if (is_builtin(value))
		return (T_BUILTIN);
	else if (is_operator(value))
		return (define_operator(value));
	else
		return (T_LITERAL);
	return (0);
}

void	print_token(void *ptr)
{
	t_token *token_list = (t_token*)ptr;

	printf("%d=%s\n", token_list->type, token_list->value);
}

void	print_all_token(t_shell *shell)
{
	ft_lstiter((shell->token_list), &print_token);
}

void	ft_create_token(int type, char *value, t_shell *shell)
{
	t_token *token;

	token = ft_safe_malloc(sizeof(t_token), shell);
	token->type = type;
	token->value = value;
	ft_lstadd_back(&(shell->token_list), ft_lstnew(token));
}

void    init_token(t_shell *shell, char *cmd)
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

void	tokenization(t_shell *shell, char *cmd)
{
	if (no_need_to_tokenization(cmd))
	{
		printf("--> no need to tokenize\n");
		return ;
	}
	init_token(shell, cmd);
}
