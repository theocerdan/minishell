#include "../includes/minishell.h"

int process_export(char *cmd)
{
    (void)(cmd);
    printf("process_export\n");
    return (1);
}

//////////////////////////////////////////////////////////

void	ft_swap_env(t_env *a, t_env *b)
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

void	ft_sort_export_env(t_list *new)
{
    t_list  *lst = new;
	t_env	*env;
	t_env	*next_env;

    while (lst && lst->next)
	{
		env = (t_env*)lst->content;
		next_env = (t_env*)lst->next->content;
		if (ft_strcmp(env->key, next_env->key) > 0)
        {
            ft_swap_env(env, next_env);
            lst = new;
        }
        else
		    lst = lst->next;
	}
}

t_list	*clone_env(t_shell *shell)
{
	t_list  *lst = shell->env_vars;
	t_list	*new_lst;
	t_env	*new;
	t_env	*old;

	new_lst = NULL;
    while (lst && lst->next)
	{
		old = (t_env*)lst->content;
		new = ft_safe_malloc(sizeof(t_env), shell);
		new->key = old->key;
		new->value = old->value;
		new->visible = old->visible;
		ft_lstadd_front(&(new_lst), ft_lstnew(new));
		lst = lst->next;
	}
	return (new_lst);
}

void	ft_export(t_shell *shell, char *each_cmd)
{
	t_env 	*env;
	t_list 	*new;
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
		new = clone_env(shell);
		ft_sort_export_env(new);
		print_all_env(new);
	}
}
