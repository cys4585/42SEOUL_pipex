/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:44:13 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/19 13:11:49 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "error.h"
#include "redirect_stream.h"
#include "execute_command.h"

void	create_pipe(int pipefd[2])
{
	check_error(PIPE, "pipe", pipe(pipefd));
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd_infile;
	int		fd_outfile;
	
	check_error(CUS_REQ_ARG, "pipex: Requires 4 arguments.\n", argc);
	redirect_stream(argc, argv, &fd_infile, &fd_outfile);
	exec_cmd(argv[2], envp);
	return (0);
}
