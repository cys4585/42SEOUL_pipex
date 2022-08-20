/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 19:19:43 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/20 16:47:51 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_BONUS_H
# define ERROR_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_error
{
	CUS_ARGC,
	CUS_HEREDOC_ARGC,
	CUS_SPLIT,
	CUS_NO_PATH,
	CUS_JOIN,
	CUS_NO_BIN,
	ACCESS,
	OPEN,
	DUP,
	PIPE,
	FORK,
	EXECVE,
	OPEN_HEREDOC,
	UNLINK
}	t_error;

void	check_custom_error(t_error err, char *str, void *ret);
void	check_error(t_error err, char *str, int ret);

#endif