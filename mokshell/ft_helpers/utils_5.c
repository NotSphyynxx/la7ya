#include "../minishell.h"

static int  get_num_len(int n)
{
    int len = 0;
    long num = n;

    if (num <= 0)
    {
        len++;  // For '-' sign or '0'
        num = -num;
    }
    while (num > 0)
    {
        num /= 10;
        len++;
    }
    return (len);
}

char    *ft_itoa(int n)
{
    int     len;
    long    num;
    char    *str;

    len = get_num_len(n);
    str = (char *)malloc(len + 1);
    if (!str)
        return (NULL);
    str[len] = '\0';
    num = n;
    if (num < 0)
        num = -num;
    if (num == 0)
        str[0] = '0';
    while (num > 0)
    {
        str[--len] = (num % 10) + '0';
        num /= 10;
    }
    if (n < 0)
        str[0] = '-';
    return (str);
}
