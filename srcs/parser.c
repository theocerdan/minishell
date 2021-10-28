#include "../includes/minishell.h"

int		get_number_of_commands(t_shell *shell)
{
	t_token *cmd;
	t_list 	*start;
	int		nbr_cmd;

	nbr_cmd = 1;
	start = shell->token_list;
	while (shell->token_list)
	{
		cmd = (t_token*)shell->token_list->content;
		if (cmd->type == PIPE)
			nbr_cmd++;
		shell->token_list = shell->token_list->next;
	}
	shell->token_list = start;
	return (nbr_cmd);
}

int	*get_each_cmd_lenght(t_shell *shell, int nbr_cmd)
{
	int		i;
	int		j;
	int		count;
	int		*each_cmd_lenght;

	i = 0;
	j = 0;
	count = 1;
	each_cmd_lenght = (int *)malloc((nbr_cmd + 1) * sizeof(int));
	while (shell->command_line_clean[i])
	{
		if (((shell->command_line_clean[i + 1] == ' ') && (shell->command_line_clean[i + 2] == '|')) || shell->command_line_clean[i + 1] == '\0')
		{
			each_cmd_lenght[j] = count;
			count = 0;
			j++;
		}
		if (shell->command_line_clean[i] == ' ' && shell->command_line_clean[i + 1] == '|' && shell->command_line_clean[i + 2] == ' ')
			i = i + 3;
		count++;
		i++;
	}
	return (each_cmd_lenght);
}

void	fill_cmd_array(t_shell *shell, int *each_cmd_lenght)
{
	int		i;
	int		j;
	int		milestone;

	i = 0;
	j = 0;
	milestone = 0;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i + 1] == '|' || shell->command_line_clean[i + 1] == '\0')
		{
			shell->tab_cmd[j] = ft_substr(shell->command_line_clean, milestone, each_cmd_lenght[j]);
			milestone = i + 3;
			j++;
		}
		i++;
	}
}

char	*get_env_key(t_shell *shell)
{
	int		i;
	int		j;
	int		count;
	int		milestone;
	char	*tmp;

	i = 0;
	count = 0;
	milestone = 0;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i] == '$')
		{
			j = i + 1;
			milestone = i + 1;
			while (ft_is_uppercase(shell->command_line_clean[j]) || shell->command_line_clean[j] == '_')
			{
				count++;
				j++;
			}
			break ;
		}
		i++;
	}
	tmp = ft_substr(shell->command_line_clean, milestone, count);
	return (tmp);
}

int		next_word_env_key(t_shell *shell)
{
	char	*tmp;
	t_list  *lst;
	t_env	*env;

	tmp = get_env_key(shell);
	lst = shell->env_vars;
    while (lst)
	{
		env = (t_env*)lst->content;
		if (ft_strcmp(env->key, tmp) == 0)
            return (1);
		lst = lst->next;
	}
	return (0);
}

int		have_env_variables(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i] == '$' && next_word_env_key(shell))
			return (1);
		i++;
	}
	return (0);
}

char	*get_replacement_env_key(t_shell *shell)
{
	char	*tmp;
	t_list  *lst;
	t_env	*env;

	tmp = get_env_key(shell);
	lst = shell->env_vars;
    while (lst)
	{
		env = (t_env*)lst->content;
		if (ft_strcmp(env->key, tmp) == 0)
            return (env->value);
		lst = lst->next;
	}
	return (NULL);
}

char	*replace_key_to_value_env(t_shell *shell)
{
	int		i;
	int		pos;
	int		lenght_rest;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*result;
	char	*to_replace;

	i = 0;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i] == '$')
			break ;
		i++;
	}
	tmp1 = ft_substr(shell->command_line_clean, 0, i);
	to_replace = get_replacement_env_key(shell);
	tmp2 = ft_strjoin(tmp1, to_replace);
	i = 0;
	while (shell->command_line_clean[i])
	{
		if (ft_is_uppercase(shell->command_line_clean[i]) && !ft_isalpha(shell->command_line_clean[i + 1]))
			break ;
		i++;
	}
	pos = i + 1;
	lenght_rest = 0;
	while (shell->command_line_clean[i])
	{
		lenght_rest++;
		i++;
	}
	tmp3 = ft_substr(shell->command_line_clean, pos, lenght_rest);
	result = ft_strjoin(tmp2, tmp3);
	return (result);
}

void	resolve_replace_key_to_value_env(t_shell *shell)
{
	do
	{
		shell->command_line_clean = replace_key_to_value_env(shell);
	} while (have_env_variables(shell));
}

int		vaguellette(t_shell *shell)
{
	int		i;
	char	*str;

	i = 0;
	str = shell->command_line_clean;
	while (str[i])
	{
		if (str[i] == '~' && !is_quote(str[i - 1]) && !is_quote(str[i + 1]) && !ft_isdigit(str[i - 1]) && !ft_isdigit(str[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

char	*get_home(t_shell *shell)
{
	t_list  *lst;
	t_env	*env;

	lst = shell->env_vars;
    while (lst)
	{
		env = (t_env*)lst->content;
		if (ft_strcmp(env->key, "HOME") == 0)
            return (env->value);
		lst = lst->next;
	}
	return (NULL);
}

char	*treat_each_vaguellette(t_shell *shell)
{
	char	*pwd;
	char	*str;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*result;
	int		lenght_rest;
	int		pos;
	int		i;

	pwd = get_home(shell);
	str = shell->command_line_clean;
	i = 0;
	while (str[i] != '~')
		i++;
	tmp1 = ft_substr(str, 0, i);
	tmp2 = ft_strjoin(tmp1, pwd);
	i++;
	pos = i;
	lenght_rest = 0;
	while (str[i++])
		lenght_rest++;
	tmp3 = ft_substr(str, pos, lenght_rest);
	result = ft_strjoin(tmp2, tmp3);
	return (result);
}

void	resolve_vaguellette(t_shell *shell)
{
	do
	{
		shell->command_line_clean = treat_each_vaguellette(shell);
	} while (vaguellette(shell));
}

void	parse_command(t_shell *shell)
{
	int		*each_cmd_lenght;

	if (shell->command_line_clean == NULL)
		return ;
	if (vaguellette(shell))
		resolve_vaguellette(shell);
	shell->command_line_clean = check_if_quotes(shell->command_line_clean);
	if (have_env_variables(shell))
		resolve_replace_key_to_value_env(shell);
	shell->nbr_cmd = get_number_of_commands(shell);
	each_cmd_lenght = get_each_cmd_lenght(shell, shell->nbr_cmd);
	shell->tab_cmd = (char **)malloc((shell->nbr_cmd + 1) * sizeof(char *));
	fill_cmd_array(shell, each_cmd_lenght);
	execute(shell);
}

void	parser(t_shell *shell)
{
	shell->fd = 0;
	parse_command(shell);
	if (shell->fd != 0)
		close(shell->fd);
}
