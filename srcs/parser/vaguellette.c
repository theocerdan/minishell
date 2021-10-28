#include "../includes/minishell.h"

int		have_vaguellette(t_shell *shell)
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

	str = shell->command_line_clean;
	pwd = get_home(shell);
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
	} while (have_vaguellette(shell));
}
