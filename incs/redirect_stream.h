/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_stream.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:08:18 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/19 15:37:18 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_STREAM_H
# define REDIRECT_STREAM_H

# include <unistd.h>
# include <fcntl.h>

void	redirect_stream(int argc, char *argv[], \
						int *fd_infile_p, int *fd_outfile_p);

#endif