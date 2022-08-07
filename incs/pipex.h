/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:49:21 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/07 20:19:51 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef enum e_mode
{
	NORMAL,
	HERE_DOC
}	t_mode;

typedef struct s_args
{
	t_mode	mode;
	char	**infile_p;
	char	**first_cmd_p;
	char	**last_cmd_p;
	char	**outfile_p;
}	t_args;

void	set_args(t_args *args_p, int argc, char *argv[]);

#endif