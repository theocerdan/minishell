#include "../includes/minishell.h"

void	ft_total_clean_env(t_shell *m)
{
	ft_lstclear(&(m->env_vars), &ft_clean);
	ft_clean(m->env_vars);
	ft_clean(m);
}

void	change_visibility(char *name, int visible, t_shell *s)
{
	t_list *lst;
	t_env *obj;

	lst = s->env_vars;
	//printf("env: %s %s %d\n", obj->key, obj->value, obj->visible);
	if (!lst)
		return ;
	while (lst)
	{
		obj = (t_env*)lst->content;
		if (obj->key == name)
		{
			obj->visible = visible;
			return ;
		}
		lst = lst->next;
	}
}

void	print_env(t_shell *s)
{
	t_list *lst = s->env_vars;
	t_env *obj;

	if (!lst)
		return ;
	while (lst)
	{
		obj = (t_env*)lst->content;
		printf("env: %s %s %d\n", obj->key, obj->value, obj->visible);
		//change_visibility(obj->key, 0, s);
		lst = lst->next;
	}
}

void	*get_env_value(char *name, t_shell *s)
{
	t_list *lst;
	t_env *obj;

	lst = s->env_vars;
	if (!lst)
		return (NULL);
	while (lst)
	{
		obj = (t_env*)lst->content;
		printf("check %s - %s", obj->key, name);
		if (obj->key == name)
			return obj->value;
		lst = lst->next;
	}
	return (NULL);
}

void	ft_add_env(t_env *env, t_shell *s)
{
	ft_lstadd_front(&(s->env_vars), ft_lstnew(env));
}

void	*ft_create_var(char *key, char *value, t_shell *s)
{
	t_env	*ptr;

	ptr = malloc(sizeof(t_env));
	if (!ptr)
	{
		printf("Malloc error\n");
		exit(0);
		return (NULL);
	}
	ptr->key = key;
	ptr->visible = 1;
	ptr->value = value;
	printf("created var %s %s\n", ptr->key, ptr->value);
	ft_add_env(ptr, s);
	//ft_lstiter(s->env_vars, &print_env);
	//print_env(s);
	return (ptr);
}
