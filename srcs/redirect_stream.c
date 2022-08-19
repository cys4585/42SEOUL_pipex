/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_stream.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:06:52 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/19 13:09:14 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect_stream.h"
#include "error.h"


void	redirect_stream(int argc, char *argv[], int *fd_infile_p, int *fd_outfile_p)
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