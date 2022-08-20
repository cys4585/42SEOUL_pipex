/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 19:20:15 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/20 13:48:07 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"

static void	exit_with_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

static void	exit_with_custom_perror(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}

void	check_custom_error(t_error err, char *str, void *ret)
{
	if (err == CUS_ARGC && *(int *)ret != 5)
		exit_with_custom_perror(str);
	if (err == CUS_SPLIT && ret == NULL)
		exit_with_custom_perror(str);
	if (err == CUS_NO_PATH && ret == NULL)
		exit_with_custom_perror(str);
	if (err == CUS_JOIN && ret == NULL)
		exit_with_custom_perror(str);
	if (err == CUS_NO_BIN && ret == NULL)
		exit_with_custom_perror(str);
}

void	check_error(t_error err, char *str, int ret)
{
	if (err == PIPE && ret == -1)
		exit_with_perror(str);
	if (err == FORK && ret == -1)
		exit_with_perror(str);
	if (err == ACCESS && ret == -1)
		exit_with_perror(str);
	if (err == OPEN && ret == -1)
		exit_with_perror(str);
	if (err == DUP && ret == -1)
		exit_with_perror(str);
	if (err == EXECVE && ret == -1)
		exit_with_perror(str);
}
