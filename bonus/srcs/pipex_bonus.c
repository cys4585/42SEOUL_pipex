/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:44:13 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/20 16:55:43 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_bonus.h"
#include "redirect_bonus.h"
#include "execute_command_bonus.h"
#include "heredoc_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	fd_infile;
	int	fd_outfile;
	int	i;

	if (check_heredoc_mode(argv[1]))
	{
		check_custom_error(CUS_HEREDOC_ARGC, \
							"Requires at least 5 arguments.\n", &argc);
		heredoc(argv[2], argc - 5);
		redirect(".heredoc_tmp", argv[argc -1], &fd_infile, &fd_outfile);
		i = 2;
	}
	else
	{
		check_custom_error(CUS_ARGC, \
							"Requires at least 4 arguments.\n", &argc);
		redirect(argv[1], argv[argc -1], &fd_infile, &fd_outfile);
		i = 1;
	}
	while (++i < argc - 2)
		execute_cmd_and_pass_output(argv[i], envp);
	execute_last_cmd(argv[i], envp);
	return (0);
}
