/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 14:22:46 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/20 15:20:38 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_one_cycle(int fd, char **backup_str)
{
	char	buf[BUFFER_SIZE + 1];
	int		read_bytes;
	char	*str;
	int		i;

	*backup_str = NULL;
	str = NULL;
	i = 0;
	while (1)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes < 0)
			return (NULL);
		else if (read_bytes == 0)
			return (str);
		buf[read_bytes] = '\0';
		str = util_strjoin(str, buf);
		if (str == NULL)
			return (NULL);
		while (str[i])
			if (str[i++] == '\n')
				return (split_nl(str, backup_str));
	}
}

void	lstadd_back(t_gnl_list **tail_p, int fd, char *str, char **backup_str)
{
	t_gnl_list	*node;
	t_gnl_list	*new;
	char		*tmp_str;

	new = malloc(sizeof(t_gnl_list));
	if (new == NULL)
		return ;
	new->fd = fd;
	new->str = str;
	new->backup_str = NULL;
	new->prev = NULL;
	new->next = NULL;
	if (*tail_p == NULL)
		*tail_p = new;
	else
	{
		node = *tail_p;
		node->next = new;
		new->prev = node;
	}
	tmp_str = split_nl(*backup_str, backup_str);
	if (tmp_str == NULL)
		new->backup_str = *backup_str;
	else
		lstadd_back(&new, fd, tmp_str, backup_str);
}

char	*get_backup_str_from_lst(t_gnl_list **lst, int fd)
{
	t_gnl_list	*node;
	char		*backup_str;

	backup_str = NULL;
	node = *lst;
	while (node)
	{
		if (node->fd == fd && node->str == NULL && node->backup_str)
		{
			backup_str = util_strdup(node->backup_str);
			free(node->backup_str);
			node->backup_str = NULL;
			if (node == *lst)
				*lst = node->next;
			else
				node->prev->next = node->next;
			if (node->next)
				node->next->prev = node->prev;
			free(node);
			break ;
		}
		node = node->next;
	}
	return (backup_str);
}

char	*get_str_from_lst(t_gnl_list **lst, int fd, t_gnl_list *node)
{
	char	*str;

	str = NULL;
	while (node)
	{
		if (node->fd == fd && node->str)
		{
			str = util_strdup(node->str);
			free(node->str);
			node->str = NULL;
			if (node->backup_str == NULL)
			{
				if (node == *lst)
					*lst = node->next;
				else
					node->prev->next = node->next;
				if (node->next)
					node->next->prev = node->prev;
				free(node);
			}
			break ;
		}
		node = node->next;
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static t_gnl_list	*head;
	t_gnl_list			*tail;
	char				*str;
	char				*backup_str;
	char				*final_str;

	str = read_one_cycle(fd, &backup_str);
	if (str != NULL)
	{
		tail = head;
		while (tail && tail->next)
			tail = tail->next;
		if (head == NULL)
			lstadd_back(&head, fd, str, &backup_str);
		else
			lstadd_back(&tail, fd, str, &backup_str);
	}
	backup_str = get_backup_str_from_lst(&head, fd);
	str = get_str_from_lst(&head, fd, head);
	final_str = util_strjoin(backup_str, str);
	if (str)
		free(str);
	else if (backup_str && !str)
		free(backup_str);
	return (final_str);
}
