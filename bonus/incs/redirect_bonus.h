/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:08:18 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/20 15:56:38 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_BONUS_H
# define REDIRECT_BONUS_H

# include <unistd.h>
# include <fcntl.h>

void	redirect(char *infile, char *outfile, \
						int *fd_infile_p, int *fd_outfile_p);

#endif