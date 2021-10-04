#include "../includes/minishell.h"

int get_size(char **array)
{
    int i;

    i = 0;
    while (array[i])
        i++;
    return i;
}
