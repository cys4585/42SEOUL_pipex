/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:05:16 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/20 16:55:24 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc_bonus.h"
#include "error_bonus.h"
#include "get_next_line.h"
#include "libft.h"

static void	display_heredoc(int pipe_cnt)
{
	while (pipe_cnt--)
		write(STDOUT_FILENO, "pipe ", 5);
	write(STDOUT_FILENO, "heredoc> ", 9);
}

static int	encouter_limiter(char *input_str, char *limiter, \
					int input_str_len, int limiter_len)
{
	if (input_str_len != limiter_len + 1)
		return (0);
	if (ft_strncmp(input_str, limiter, limiter_len) != 0)
		return (0);
	return (1);
}

static void	write_to_heredoc(char *limiter, int fd_heredoc, int pipe_cnt)
{
	char	*input_str;
	int		input_str_len;
	int		limiter_len;

	limiter_len = ft_strlen(limiter);
	while (1)
	{
		display_heredoc(pipe_cnt);
		input_str = get_next_line(STDIN_FILENO);
		input_str_len = ft_strlen(input_str);
		if (encouter_limiter(input_str, limiter, input_str_len, limiter_len))
			break ;
		write(fd_heredoc, input_str, input_str_len);
		free(input_str);
	}
	free(input_str);
}

void	heredoc(char *limiter, int pipe_cnt)
{
	char	*heredoc_tmp;
	int		fd_heredoc;

	heredoc_tmp = ".heredoc_tmp";
	fd_heredoc = open(heredoc_tmp, \
					O_CREAT | O_WRONLY | O_TRUNC, \
					S_IRUSR | S_IWUSR);
	check_error(OPEN, heredoc_tmp, fd_heredoc);
	write_to_heredoc(limiter, fd_heredoc, pipe_cnt);
	close(fd_heredoc);
}

int	check_heredoc_mode(char *first_arg)
{
	if (ft_strncmp(first_arg, "here_doc", 9) == 0)
		return (1);
	return (0);
}
