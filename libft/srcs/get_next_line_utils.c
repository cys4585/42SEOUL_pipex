/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:17:09 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/20 14:49:37 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	util_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (i + 1 < dstsize && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

size_t	util_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (s[size])
		size++;
	return (size);
}

char	*util_strdup(const char *s1)
{
	int		len;
	char	*dst;
	int		i;

	len = util_strlen(s1);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*util_strjoin(char const *old_str, char const *buf)
{
	char	*new_str;
	size_t	len_old;
	size_t	len_buf;

	if (old_str == NULL && buf == NULL)
		return (NULL);
	if (old_str == NULL)
		return (util_strdup(buf));
	if (buf == NULL)
		return (util_strdup(old_str));
	len_old = util_strlen(old_str);
	len_buf = util_strlen(buf);
	new_str = (char *)malloc(sizeof(char) * (len_old + len_buf + 1));
	if (new_str == NULL)
		return (NULL);
	util_strlcpy(new_str, old_str, len_old + 1);
	util_strlcpy(new_str + len_old, buf, len_buf + 1);
	free((void *)old_str);
	return (new_str);
}

char	*split_nl(char *str, char **backup_str)
{
	char	*tmp_str;
	int		i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			break ;
		i++;
	}
	if (str[i] == '\0')
		return (NULL);
	tmp_str = str;
	if (str[i + 1] == '\0')
		*backup_str = NULL;
	else
		*backup_str = util_strdup(&str[i + 1]);
	str[i + 1] = '\0';
	str = util_strdup(str);
	free(tmp_str);
	return (str);
}
