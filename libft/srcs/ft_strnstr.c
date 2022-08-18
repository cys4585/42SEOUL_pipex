/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:17:43 by youngcho          #+#    #+#             */
/*   Updated: 2022/05/17 16:46:10 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_h;
	size_t	len_n;
	size_t	i;

	if (needle[0] == '\0')
		return ((char *)haystack);
	len_h = ft_strlen(haystack);
	len_n = ft_strlen(needle);
	i = 0;
	while ((i + len_n <= len) && (i + len_n <= len_h))
	{
		if (haystack[i] == needle[0]
			&& ft_strncmp(&haystack[i], needle, len_n) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
