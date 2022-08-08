/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:49:21 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/08 11:35:41 by youngcho         ###   ########.fr       */
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
	char	*infile;
	char	*outfile;
	char	**first_cmd_p;
	char	**last_cmd_p;
}	t_args;

void	set_args(t_args *args_p, int argc, char *argv[]);

#endif