#include "../includes/minishell.h"

void	update_pwd_var(t_shell *shell)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	get_env_object("PWD", shell)->value = pwd;
}

void	update_oldpwd_var(t_shell *shell, char *old_pwd_str)
{
	get_env_object("OLDPWD", shell)->value = old_pwd_str;
}

void	update_oldpwd_pwd_vars(t_shell *shell, char *old_pwd_str)
{
	update_oldpwd_var(shell, old_pwd_str);
	update_pwd_var(shell);
}

void	ft_cd(t_shell *shell, char *each_cmd)
{
	(void)(each_cmd);
	(void)(shell);
	int arg_len;
	char **arg;
	char *old_pwdv;
	char *target_pwdv;

	arg_len = 0;
	arg = ft_split(shell->command_line_clean, ' ');
	old_pwdv = get_env_object("PWD", shell)->value;
	while (arg[arg_len])
		arg_len++;
	if (arg_len > 2) //si + de 1 arg marche pas
		return;
	else
	{
		if (arg_len == 1)
			target_pwdv = get_env_object("HOME", shell)->value; //home
		else
			target_pwdv = arg[1];
		chdir(target_pwdv);
		update_oldpwd_pwd_vars(shell, old_pwdv);
	}
}