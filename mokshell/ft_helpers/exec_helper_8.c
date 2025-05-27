#include "../minishell.h"



void ft_free_str_array(char **arr)
{
    int i = 0;
    while (arr && arr[i])
    {
        free(arr[i++]);
    }
    free(arr);
}