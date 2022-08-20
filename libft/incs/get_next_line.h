/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:18:02 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/20 15:20:15 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_gnl_list
{
	int					fd;
	char				*str;
	char				*backup_str;
	struct s_gnl_list	*prev;
	struct s_gnl_list	*next;
}	t_gnl_list;

size_t	util_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	util_strlen(const char *s);
char	*util_strdup(const char *s1);
char	*util_strjoin(char const *old_str, char const *buf);
char	*split_nl(char *str, char **backup_str);

char	*read_one_cycle(int fd, char **backup_str);
void	lstadd_back(t_gnl_list **tail_p, int fd, char *str, char **backup_str);
char	*get_backup_str_from_lst(t_gnl_list **lst, int fd);
char	*get_str_from_lst(t_gnl_list **lst, int fd, t_gnl_list *node);
char	*get_next_line(int fd);

#endif