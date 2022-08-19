/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:44:13 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/19 15:35:33 by youngcho         ###   ########.fr       */
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

void	execute_first_cmd(char *cmd, char *envp[])
{
	int		pipefd[2];
	pid_t	child;

	check_error(PIPE, "pipe", pipe(pipefd));
	child = fork();
	check_error(FORK, "first fork", child);
	if (child > 0)
	{
		close(pipefd[1]);
		waitpid(child, NULL, 0);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exec_cmd(cmd, envp);
	}
}

void	execute_second_cmd(char *cmd, char *envp[])
{
	pid_t	child;

	child = fork();
	check_error(FORK, "second fork", child);
	if (child > 0)
		waitpid(child, NULL, 0);
	else
		exec_cmd(cmd, envp);
}

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
