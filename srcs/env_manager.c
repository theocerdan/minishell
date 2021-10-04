#include "../includes/minishell.h"

void print_env(void *ptr){
	t_env *env = (t_env*)ptr;
	if (env->visible == 1){
		printf("%s=%s %d\n", env->key, env->value, env->visible);
	}
}

void	print_all_env(t_shell *shell)
{
	ft_lstiter((shell->env_vars), &print_env);
}

t_env	*get_env_object(char *target_key, t_shell *shell){
	t_list *lst = shell->env_vars;
	t_env *env;

	if (!lst)
		return NULL;
	while (lst)
	{
		env = (t_env*)lst->content;
		if (env->visible == 1 && ft_strcmp(env->key, target_key) == 0){
			return env;
		}
		lst = lst->next;
	}
	return NULL;
}

int	env_key_exist(char *target_key, t_shell *shell){
	t_list *lst = shell->env_vars;
	t_env *env;

	if (!lst)
		return 0;
	while (lst)
	{
		env = (t_env*)lst->content;
		if (env->visible == 1 && ft_strcmp(env->key, target_key) == 0){
			return 1;
		}
		lst = lst->next;
	}
	return 0;
}

void	ft_delete_var(char *target_key, t_shell *shell){
	t_list *lst = shell->env_vars;
	t_env *env;
	//t_env *deleted;

	if (!lst)
		return ;
	while (lst)
	{
		env = (t_env*)lst->content;
		if (ft_strcmp(env->key, target_key) == 0){
			env->visible = 0;
		}
		lst = lst->next;
	}
}

void	ft_create_var(char *key, char *value, t_shell *shell)
{
	t_env *env;

	env = get_env_object(key, shell);
	if (env != NULL){
		env->value = value;
		env->visible = 1;
		return ;
	}
	env = ft_safe_malloc(sizeof(t_env), shell);

	env->key = key;
	env->value = value;
	env->visible = 1;

	ft_lstadd_back(&(shell->env_vars), ft_lstnew(env));
}
