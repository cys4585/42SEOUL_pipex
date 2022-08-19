/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:44:13 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/19 16:42:43 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "redirect_stream.h"
#include "execute_command.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	fd_infile;
	int	fd_outfile;

	check_custom_error(CUS_REQ_ARG, "pipex: Requires 4 arguments.\n", &argc);
	redirect_stream(argc, argv, &fd_infile, &fd_outfile);
	execute_first_cmd(argv[2], envp);
	execute_second_cmd(argv[3], envp);
	return (0);
}
