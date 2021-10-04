#include "../includes/minishell.h"

char	*join_prompt_element(char *begin, char *pwd, char *end)
{
	char	*tmp;
	char	*prompt;

	tmp = ft_strjoin(begin, pwd);
	prompt = ft_strjoin(tmp, end);
	free(tmp);
	free(begin);
	free(pwd);
	free(end);
	return (prompt);
}

char	*create_prompt(t_shell *shell)
{
	char	*pwd;
	char	*result;
	char	*buffer;
	char	*home_path;

	buffer = NULL;
	home_path = get_env_object("HOME", shell)->value;
	pwd = getcwd(buffer, 0);
	result = join_prompt_element(ft_strdup("~"), ft_strdup(pwd + ft_strlen(home_path)), ft_strdup("$ "));
	return (result);
}

char	*start_prompt(t_shell *shell, char *cmd)
{
	char	*prompt;

	prompt = create_prompt(shell);
	cmd = readline(prompt);
	free(prompt);
	return (cmd);
}
