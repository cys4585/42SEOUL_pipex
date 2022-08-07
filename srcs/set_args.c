/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 19:05:35 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/07 20:20:24 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
// static void	check_mode(t_args *args_p, char *first_arg)
// {
// 	if (first_arg == "here_doc")
// 		args_p->mode = HERE_DOC;
// 	else
// 		args_p->mode = NORMAL;
// }

static void	set_args_normal_mode(t_args *args_p, int argc, char *argv[])
{
	args_p->infile_p = argv + 1;
	args_p->outfile_p = argv + argc - 1;
	args_p->first_cmd_p = argv + 2;
	args_p->last_cmd_p = argv + argc - 2;
}

void	set_args(t_args *args_p, int argc, char *argv[])
{
	// check_mode(args_p, argv[1]);
	// if (args_p->mode == NORMAL)
	set_args_normal_mode(args_p, argc, argv);
}