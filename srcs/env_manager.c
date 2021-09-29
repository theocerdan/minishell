#include "../includes/minishell.h"

void	ft_total_clean_env(t_shell *m)
{
	ft_lstclear(&(m->env_vars), &ft_clean);
	ft_clean(m->env_vars);
	ft_clean(m);
}

/*void	change_visibility(char *name, int visible, t_shell *s)
{
	
}*/

void	print_env(t_shell *s)
{
	t_list	*lst;
	t_env *obj;

	lst = s->env_vars;
	if (!lst)
		return ;
	while (lst)
	{
		obj = (t_env*)lst->content;
		printf("contenu: %s\n", obj->key);
		lst = lst->next;
	}
}

/*void	*get_env_value(char *name, t_shell *s)
{
	
}*/

void	*ft_create_var(char *key, char *value, t_shell *s)
{
	t_env	*ptr;

	ptr = ft_safe_malloc(sizeof(t_env), s);
	ptr->key = key;
	ptr->value = value;
	ptr->visible = 1;
	printf("created var %s %s %d\n", ptr->key, ptr->value, ptr->visible);
	ft_lstadd_front(&(s->env_vars), ft_lstnew(ptr));
	//print_env(s);
	return (ptr);
}
