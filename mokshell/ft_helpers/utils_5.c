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

char	*ft_itoa(int n)
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

void	init_pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("/");
	*get_pwd_storage() = cwd;
}

int	ft_is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_atoi_with_overflow(const char *str, int *overflow)
{
	long long	num = 0;
	int			sign = 1;

	*overflow = 0;
	while (ft_is_space(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while (ft_isdigit(*str))
	{
		if (num > (LLONG_MAX - (*str - '0')) / 10)
		{
			*overflow = 1;
			return (0);
		}
		num = num * 10 + (*str - '0');
		str++;
	}
	if (*str)
	{
		*overflow = 1;
		return (0);
	}
	return ((int)(num * sign));
}
