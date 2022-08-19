/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:00:42 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/19 16:41:35 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_COMMAND_H
# define EXECUTE_COMMAND_H

# include <unistd.h>
# include <stdlib.h>

void	execute_first_cmd(char *cmd, char *envp[]);
void	execute_second_cmd(char *cmd, char *envp[]);

#endif