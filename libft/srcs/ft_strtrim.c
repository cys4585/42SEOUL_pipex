/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 17:34:12 by youngcho          #+#    #+#             */
/*   Updated: 2022/05/17 17:16:56 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		begin_idx;
	int		end_idx;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	begin_idx = 0;
	while (s1[begin_idx] && ft_strchr(set, s1[begin_idx]))
		begin_idx++;
	end_idx = ft_strlen(s1) - 1;
	while (0 <= end_idx && ft_strchr(set, s1[end_idx]))
		end_idx--;
	if (end_idx < begin_idx)
		return (ft_strdup(""));
	return (ft_substr(s1, begin_idx, end_idx - begin_idx + 1));
}
