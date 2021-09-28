#include "../includes/minishell.h"

char	*join_prompt_element(char *name, char *pwd, char *end)
{
	char	*tmp;
	char	*prompt;

	tmp = ft_strjoin(name, pwd);
	prompt = ft_strjoin(tmp, end);
	free(tmp);
	free(name);
	free(pwd);
	free(end);
	return (prompt);
}

char	*get_pwd(void)
{
	char	*buffer;

	buffer = NULL;
	return (getcwd(buffer, 0));
}

char	*create_prompt(void)
{
	char	*pwd;
	char	*name;
	char	*end;
	char	*result;

	pwd = get_pwd();
	name = ft_strdup("Minishell");
	end = ft_strdup("$ ");
	result = join_prompt_element(name, pwd, end);
	return (result);
}

char	*start_prompt(char *cmd)
{
	char	*prompt;

	prompt = create_prompt();
	cmd = readline(prompt);
	free(prompt);
	return (cmd);
}
