#include "../includes/minishell.h"

int process_export(char *cmd)
{
    (void)(cmd);
    printf("process_export\n");
    return (1);
}

//////////////////////////////////////////////////////////

void		ft_swap_env(t_env *a, t_env *b)
{
	char	*tmp;
	int		visible;

	tmp = a->key;
	a->key = b->key;
	b->key = tmp;
	tmp = a->value;
	a->value = b->value;
	b->value = tmp;
	visible = a->visible;
	a->visible = b->visible;
	b->visible = visible;
}

void	ft_sort_export_env(t_shell *shell)
{
    t_list  *lst = shell->env_vars;
	t_env	*env;
	t_env	*next_env;

    while (lst && lst->next)
	{
		env = (t_env*)lst->content;
		next_env = (t_env*)lst->next->content;
		if (ft_strcmp(env->key, next_env->key) > 0)
        {
            ft_swap_env(env, next_env);
            lst = shell->env_vars;
        }
        else
		    lst = lst->next;
	}
}

void	export(t_shell *shell, char *each_cmd)
{
	t_env 	*env;
    char	*first_arg;
	int		i;

    first_arg = get_first_arg(each_cmd);
	env = NULL;
	if (ft_strlen(first_arg) > 0)
	{
		i = 0;
		while (first_arg[i])
		{
			if (first_arg[i] == '=')
				break ;
			i++;
		}
		env = ft_safe_malloc(sizeof(t_env), shell);
		env->key = ft_substr(first_arg, 0, i);
		env->value = ft_substr(first_arg, i + 1, ft_strlen(first_arg) - ft_strlen(env->key));
		env->visible = 1;
		ft_lstadd_front(&(shell->env_vars), ft_lstnew(env));
	}
	else
	{
		ft_sort_export_env(shell);
		print_all_env(shell);
	}
}
