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

int		is_builtin(char *value)
{
	if (!value)
		return (0);
	if (!(ft_strcmp(value, "echo\0")) || !(ft_strcmp(value, "cd\0")) || !(ft_strcmp(value, "pwd")) || !(ft_strcmp(value, "export")) || !(ft_strcmp(value, "unset")) || !(ft_strcmp(value, "env")) || !(ft_strcmp(value, "exit")))
		return (1);
	return (0);
}

int		is_operator(char *value)
{
	if (!(ft_strcmp(value, "|")) || !(ft_strcmp(value, ">"))|| !(ft_strcmp(value, "<")) || !(ft_strcmp(value, ">>")) || !(ft_strcmp(value, "<<")))
		return (1);
	return (0);
}

int		is_env(char *value)
{
	int		i;

	i = 0;
	while (value[i])
	{
		if ((value[i] >= 65 && value[i] <= 90) || value[i] == 36)
			i++;
		else
			return (0);
	}
	return (1);
}

int		is_flag(char *value)
{
	if (value[0] == '-' && value[1] == 'n')
		return (1);
	return (0);
}

int		define_operator(char *value)
{
	if (!(ft_strcmp(value, "|")))
		return (PIPE);
	if (!ft_strcmp(value, ">") || !ft_strcmp(value, "<") || !ft_strcmp(value, ">>") || !ft_strcmp(value, "<<"))
		return (REDIRECT);
	return (0);
}

int		define_type(char *value)
{
	if (is_builtin(value))
		return (BUILTIN);
	else if (is_operator(value))
		return (define_operator(value));
	else if (is_env(value))
		return (ENV_TOKEN);
	else if (is_flag(value))
		return (FLAG);
	else
		return (LITERAL);
	return (0);
}

void	print_token(void *ptr)
{
	t_token *token_list;

	token_list = (t_token*)ptr;
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
	ft_lstadd_front(&(shell->token_list), ft_lstnew(token));
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

//////////////////////

void	free_aux_strings(char **left, char **operator, char **right, char **first_part)
{
	free(*left);
	free(*operator);
	free(*right);
	free(*first_part);
}

char	*insert_spaces(char *line, char operator_pointer, int off_set)
{
	char	*left;
	char	*operator;
	char	*right;
	char	*first_part;
	char	*final_part;

	if (line[off_set - 1] == ' ')
		left = ft_substr(line, 0, off_set - 1);
	else
		left = ft_substr(line, 0, off_set);
	operator = (char *)malloc(sizeof(char) * 3 + 1);
	if (line[off_set + 1] == ' ')
	{
		operator[0] = ' ';  
		operator[1] = operator_pointer;  
		operator[2] = '\0'; 
	}
	else
	{
		operator[0] = ' ';  
		operator[1] = operator_pointer;  
		operator[2] = ' '; 
		operator[3] = '\0'; 
	}
	right = ft_substr(line, off_set + 1, ft_strlen(line));
	first_part = ft_strjoin(left, operator);
	final_part = ft_strjoin(first_part, right);
	free_aux_strings(&left, &operator, &right, &first_part);
	return (final_part);
}

int	ft_isblank(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_between_blanks(char after_char, char before_char)
{
	if ((ft_isblank(before_char) && (ft_isblank(after_char))))
		return (1);
	return (0);
}

int	no_blanks_around_operator(char current_char, char after_char, char before_char)
{
	if ((current_char == '|') && !(is_between_blanks(after_char, before_char)))
		return (1);
	return (0);
}

char	*check_and_insert_spaces(char *cmd)
{
	char	*current;
	char	*tmp;
	char	*result;
	int		i;

	i = 0;
	current = cmd;
	tmp = cmd;
	result = " ";
	while (current != NULL && current[i])
	{
		if (i > 0 && no_blanks_around_operator(current[i], current[i + 1], current[i - 1]))
		{
			tmp = insert_spaces(cmd, current[i], i);
			result = ft_strjoin(result, tmp);
		}
		else
			result = tmp;
		i++;
	}
	return (result);
}

int		toujours_mal_formate(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|' && !(is_between_blanks(cmd[i + 1], cmd[i - 1])))
			return (1);
		i++;
	}
	return (0);
}

char	*resolve_space_issue(char *cmd)
{
	char	*result;

	result = cmd;
	do
	{
		result = check_and_insert_spaces(result);
	} while (toujours_mal_formate(result));
	return (result);
	
}

void	tokenization(t_shell *shell, char *cmd)
{
	if (no_need_to_tokenization(cmd))
		return ;
	cmd = resolve_space_issue(cmd);
	shell->command_line_clean = cmd;
	//printf("after:%s|\n", cmd);
	init_token(shell, cmd);
	//print_all_token(shell);
}
