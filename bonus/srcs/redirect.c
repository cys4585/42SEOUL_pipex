/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:06:52 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/20 11:35:25 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"
#include "error.h"

void	redirect(char *infile, char *outfile, \
						int *fd_infile_p, int *fd_outfile_p)
{
	check_error(ACCESS, infile, access(infile, R_OK));
	*fd_infile_p = open(infile, O_RDONLY);
	check_error(OPEN, infile, *fd_infile_p);
	*fd_outfile_p = open(outfile, \
		O_CREAT | O_WRONLY | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	check_error(OPEN, outfile, *fd_outfile_p);
	check_error(DUP, "dup2():", dup2(*fd_infile_p, STDIN_FILENO));
	check_error(DUP, "dup2():", dup2(*fd_outfile_p, STDOUT_FILENO));
}
