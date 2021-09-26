#include "../includes/minishell.h"

t_built	built[] = {
	{CD,  {"cd"}, &process_cd},
	{ENV, {"env"}, &process_env},
	{PWD, {"pwd"}, &process_pwd},
	{EXPORT, {"export"}, &process_export},
	{UNSET, {"unset"}, &process_unset},
	{EXIT, {"exit"}, &process_exit},
	{ECHO, {"echo"}, &process_echo}
};

int get_correct_built(char *text, int (**process_ft)(t_shell *shell, char* cmd))
{
    int i;
	int a;

    i = 0; 
	if (text == NULL)
		return (-1); 
    while (i < 7) //nombre de built
	{
		a = 0;
		while (built[i].cmd[a])
		{
			if (equals_ignore_case(text, built[i].cmd[a])){
				*process_ft = built[i].process_ft;
				return built[i].id;
			}
			a++;
		}
		i++;
    }
	return (-1);
}