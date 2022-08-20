/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 19:19:43 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/20 13:48:07 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_error
{
	CUS_ARGC,
	CUS_SPLIT,
	CUS_NO_PATH,
	CUS_JOIN,
	CUS_NO_BIN,
	ACCESS,
	OPEN,
	DUP,
	PIPE,
	FORK,
	EXECVE
}	t_error;

void	check_custom_error(t_error err, char *str, void *ret);
void	check_error(t_error err, char *str, int ret);

#endif