/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:11:22 by youngcho          #+#    #+#             */
/*   Updated: 2022/05/19 14:50:15 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

char	*pass_space(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	return ((char *)str + i);
}

int	check_sign(char **str_p)
{
	if (**str_p == '-')
	{
		(*str_p)++;
		return (-1);
	}
	else if (**str_p == '+')
		(*str_p)++;
	return (1);
}

int	convert_to_int(char *str, int sign)
{
	unsigned long	cutoff;
	unsigned long	cutlim;
	unsigned long	num;
	int				over;

	cutoff = LONG_MAX / 10;
	cutlim = LONG_MAX % 10;
	if (sign == -1)
		cutlim = -(LONG_MIN % 10);
	num = 0;
	over = 0;
	while ('0' <= *str && *str <= '9' && *str)
	{
		if (over == 1 || num > cutoff \
				|| (num == cutoff && (unsigned long)*str - '0' > cutlim))
			over = 1;
		else
			num = num * 10 + (*str - '0');
		str++;
	}
	if (over && sign == 1)
		num = LONG_MAX;
	else if (over && sign == -1)
		num = LONG_MIN;
	return (sign * (int)num);
}

int	ft_atoi(const char *str)
{
	char	*tmp_str;
	int		sign;

	tmp_str = pass_space(str);
	sign = check_sign(&tmp_str);
	return (convert_to_int(tmp_str, sign));
}
