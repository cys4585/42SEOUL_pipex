/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:05:51 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/20 15:57:57 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_BONUS_H
# define HEREDOC_BONUS_H

# include <unistd.h>
# include <fcntl.h>

void	heredoc(char *limiter, int pipe_cnt);
int		check_heredoc_mode(char *first_arg);

#endif