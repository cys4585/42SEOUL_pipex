/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:44:13 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/20 13:18:23 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "redirect.h"
#include "execute_command.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	fd_infile;
	int	fd_outfile;
	int	i;

	check_custom_error(CUS_REQ_ARG, "Requires at least 4 arguments.\n", &argc);
	redirect(argv[1], argv[argc -1], &fd_infile, &fd_outfile);
	i = 1;
	while (++i < argc - 2)
		execute_cmd_and_pass_output(argv[i], envp);
	execute_last_cmd(argv[i], envp);
	return (0);
}
