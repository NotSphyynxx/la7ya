/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 15:00:47 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/06/08 16:30:35 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_num_len(int n)
{
	int		len;
	long	num;

	num = n;
	len = 0;
	if (num <= 0)
	{
		len++;
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
	int		len;
	long	num;
	char	*str;

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

static int	parse_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '+' || **str == '-')
		if (*(*str)++ == '-')
			sign = -1;
	return (sign);
}

static int	parse_digits(const char **str, long long *num, int *overflow)
{
	while (ft_isdigit(**str))
	{
		if (*num > (LLONG_MAX - (**str - '0')) / 10)
		{
			*overflow = 1;
			return (0);
		}
		*num = *num * 10 + (**str - '0');
		(*str)++;
	}
	return (1);
}

int	ft_atoi_with_overflow(const char *str, int *overflow)
{
	long long	num;
	int			sign;

	num = 0;
	sign = 1;
	*overflow = 0;
	while (ft_is_space(*str))
		str++;
	sign = parse_sign(&str);
	if (!parse_digits(&str, &num, overflow))
		return (0);
	if (*str)
	{
		*overflow = 1;
		return (0);
	}
	return ((int)(num * sign));
}
