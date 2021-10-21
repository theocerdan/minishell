#include "../includes/minishell.h"

void	print_env(void *ptr)
{
	t_env *env;

	env = (t_env*)ptr;
	if (env->visible == 1)
		printf("%s=%s\n", env->key, env->value);
}

void	print_all_env(t_list *lst)
{
	ft_lstiter((lst), &print_env);
}
