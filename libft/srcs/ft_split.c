/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:32:34 by youngcho          #+#    #+#             */
/*   Updated: 2022/04/07 19:05:02 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	count_size(char const *s, char c)
{
	int	cnt;
	int	flag;
	int	i;

	cnt = 0;
	flag = 0;
	i = 0;
	while (s[i])
	{
		if (flag == 0 && s[i] != c)
			flag = 1;
		else if (flag == 1 && s[i] == c)
		{
			cnt++;
			flag = 0;
		}
		i++;
	}
	if (flag == 1)
		cnt++;
	return (cnt);
}

int	split_str(char **dst_arr, char const *s, char c, int s_len)
{
	int		start;
	int		flag;
	int		i;

	start = 0;
	flag = 0;
	i = 0;
	while (i <= s_len)
	{
		if (flag == 0 && s[i] != c)
		{
			start = i;
			flag = 1;
		}
		else if (flag == 1 && (s[i] == c || s[i] == '\0'))
		{
			*dst_arr = ft_substr(s, start, i - start);
			if (*dst_arr == NULL)
				return (0);
			dst_arr++;
			flag = 0;
		}
		i++;
	}
	return (1);
}

void	array_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	int		size;
	char	**dst_arr;

	if (s == NULL)
		return (NULL);
	size = count_size(s, c);
	dst_arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (dst_arr == NULL)
		return (NULL);
	dst_arr[size] = NULL;
	if (split_str(dst_arr, s, c, ft_strlen(s)) == 0)
	{
		array_free(dst_arr);
		return (NULL);
	}
	return (dst_arr);
}
