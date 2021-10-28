#include "../includes/minishell.h"

char	*get_env_key(t_shell *shell)
{
	char	*tmp;
	int		milestone;
	int		count;
	int		i;
	int		j;

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

	to_replace = get_replacement_env_key(shell);
	i = 0;
	while (shell->command_line_clean[i])
	{
		if (shell->command_line_clean[i] == '$')
			break ;
		i++;
	}
	tmp1 = ft_substr(shell->command_line_clean, 0, i);
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
	while (shell->command_line_clean[i++])
		lenght_rest++;
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
