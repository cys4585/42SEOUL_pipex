/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 19:19:43 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/19 12:50:42 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>
// perror
# include <stdlib.h>
// exit
# include <unistd.h>
// write

typedef enum e_error
{
	CUS_REQ_ARG,
	CUS_SPLIT,
	CUS_NO_PATH,
	CUS_JOIN,
	CUS_NO_BIN,
	ACCESS,
	OPEN,
	DUP,
	PIPE,
	FORK
}	t_error;

void	check_error_pointer(t_error err, char *str, void *ret);
void	check_error(t_error err, char *str, int ret);

#endif