/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:44:13 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/20 11:37:51 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "redirect.h"
#include "execute_command.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	fd_infile;
	int	fd_outfile;

	check_custom_error(CUS_REQ_ARG, "pipex: Requires 4 arguments.\n", &argc);
	redirect(argv[1], argv[argc -1], &fd_infile, &fd_outfile);
	execute_first_cmd(argv[2], envp);
	execute_last_cmd(argv[argc -2], envp);
	return (0);
}
