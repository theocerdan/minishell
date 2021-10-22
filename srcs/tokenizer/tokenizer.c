#include "../includes/minishell.h"

/*int		match(char *current, char c, int pos)
{
	char	*current_char;
	int		i;

	(void)(c);
	current_char = ft_substr(current, pos + 1, ft_strlen(current) - pos);
	i = 0;
	while (current_char[i])
	{
		if (current_char[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		string_between_quotes(char *current)
{
	char	current_char;
	int		i;

	i  = 0;
	while (current[i])
	{
		current_char = current[i];
		if (is_quote(current_char) && match(current, current_char, i))
		{
			//printf("string between quotes\n");
			return (1);
		}
		i++;
	}
	return (0);
}*/

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
		/*if (string_between_quotes(current))
		{
			i++;
			continue ;
		}*/
		if (i > 0 && no_blanks_around_operator(current[i], current[i + 1], current[i - 1]))
		{
			result = " ";
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
	//printf("before:%s|\n", cmd);
	cmd = resolve_space_issue(cmd);
	cmd = check_if_quotes(cmd);
	shell->command_line_clean = cmd;
	printf("shell->command_line_clean:%s\n", shell->command_line_clean);
	//printf("after:%s|\n", cmd);
	init_token(shell, cmd);
	print_all_token(shell);
}
