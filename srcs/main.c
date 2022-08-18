/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:44:13 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/18 16:24:36 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "error.h"

#include <stdio.h>
void	create_pipe(int pipefd[2])
{
	check_error(PIPE, "pipe", pipe(pipefd));
}

void	redirect(int argc, char *argv[], int *fd_infile_p, int *fd_outfile_p)
{
	check_error(ACCESS, argv[1], access(argv[1], R_OK));
	*fd_infile_p = open(argv[1], O_RDONLY);
	check_error(OPEN, argv[1], *fd_infile_p);
	*fd_outfile_p = open(argv[argc - 1], \
		O_CREAT | O_WRONLY | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	check_error(OPEN, argv[argc - 1], *fd_outfile_p);
	check_error(DUP, "dup2():", dup2(*fd_infile_p, STDIN_FILENO));
	check_error(DUP, "dup2():", dup2(*fd_outfile_p, STDOUT_FILENO));
}

int	main(int argc, char *argv[])
{
	int		fd_infile;
	int		fd_outfile;
	int		pipefd[2];

	check_error(CUS_REQ_ARG, "pipex: Requires 4 arguments.\n", argc);
	redirect(argc, argv, &fd_infile, &fd_outfile);
	create_pipe(pipefd);
	return (0);
}
