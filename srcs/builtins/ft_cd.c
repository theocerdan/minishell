/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaurin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:46:13 by mbaurin           #+#    #+#             */
/*   Updated: 2021/11/14 13:46:15 by mbaurin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_pwd_var(t_shell *shell)
{
	char	*pwd;

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

void    ft_cd(t_shell *shell, char *each_cmd)
{
    int     arg_len;
    char    **arg;
    char    *old_pwdv;
    char    *target_pwdv;
    int     ret;
    (void)(each_cmd);
    (void)(shell);
    arg_len = 0;
    arg = ft_split(shell->command_line_clean, ' ');
    old_pwdv = get_env_object("PWD", shell)->value;
    while (arg[arg_len])
        arg_len++;
    if (arg_len == 1)
        target_pwdv = get_env_object("HOME", shell)->value;
    else
        target_pwdv = arg[1];
    ret = chdir(target_pwdv);
    if (ret == 0)
        update_oldpwd_pwd_vars(shell, old_pwdv);
    else
        printf("cd: %s: No such file or directory\n", target_pwdv);
}
