/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 19:20:15 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/18 16:22:53 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"

void	exit_with_perror(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	exit_with_custom_perror(char *str)
{
	write(STDERR_FILENO, str , ft_strlen(str));
	exit(EXIT_FAILURE);
}

void	check_error(t_error err, char *str, int ret)
{
	if (err == CUS_REQ_ARG && ret != 5)
		exit_with_custom_perror(str);
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
}
