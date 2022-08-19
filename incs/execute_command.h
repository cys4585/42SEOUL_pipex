/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:00:42 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/19 13:14:47 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_COMMAND_H
# define EXECUTE_COMMAND_H

#include <unistd.h>
// execve access
#include <stdlib.h>
// free

void	exec_cmd(char *cmd, char *envp[]);

#endif