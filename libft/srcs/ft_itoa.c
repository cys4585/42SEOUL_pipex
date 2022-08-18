/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 11:54:44 by youngcho          #+#    #+#             */
/*   Updated: 2022/03/26 13:36:18 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	count_size_to_allocate(int n)
{
	int	cnt;

	if (n == 0)
		return (2);
	cnt = 0;
	if (n < 0)
		cnt++;
	while (n != 0)
	{
		n /= 10;
		cnt++;
	}
	return (cnt + 1);
}

void	recursion_convert(char *str, int idx, int n)
{
	if (n < 0)
	{
		str[0] = '-';
		recursion_convert(str, idx - 1, -(n / 10));
		str[idx] = -(n % 10) + '0';
	}
	else if (n > 0)
	{
		recursion_convert(str, idx - 1, n / 10);
		str[idx] = (n % 10) + '0';
	}
}

char	*ft_itoa(int n)
{
	int		size;
	char	*str;

	size = count_size_to_allocate(n);
	str = (char *)malloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);
	str[size - 1] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	recursion_convert(str, size - 2, n);
	return (str);
}
