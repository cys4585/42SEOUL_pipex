/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:08:18 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/20 11:36:04 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# include <unistd.h>
# include <fcntl.h>

void	redirect(char *infile, char *outfile, \
						int *fd_infile_p, int *fd_outfile_p);

#endif