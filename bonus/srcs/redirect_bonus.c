/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:06:52 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/20 16:55:52 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect_bonus.h"
#include "error_bonus.h"
#include "libft.h"

static int	check_heredoc_mode(char *infile)
{
	if (ft_strncmp(infile, ".heredoc_tmp", 13) == 0)
		return (1);
	return (0);
}

void	redirect(char *infile, char *outfile, \
						int *fd_infile_p, int *fd_outfile_p)
{
	check_error(ACCESS, infile, access(infile, R_OK));
	*fd_infile_p = open(infile, O_RDONLY);
	if (check_heredoc_mode(infile))
	{
		check_error(OPEN_HEREDOC, infile, *fd_infile_p);
		*fd_outfile_p = open(outfile, \
							O_CREAT | O_WRONLY | O_APPEND, \
							S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	else
	{
		check_error(OPEN, infile, *fd_infile_p);
		*fd_outfile_p = open(outfile, \
						O_CREAT | O_WRONLY | O_TRUNC, \
						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	check_error(OPEN, outfile, *fd_outfile_p);
	check_error(DUP, "dup2", dup2(*fd_infile_p, STDIN_FILENO));
	if (check_heredoc_mode(infile))
		check_error(UNLINK, "unlink", unlink(infile));
	check_error(DUP, "dup2", dup2(*fd_outfile_p, STDOUT_FILENO));
}
