/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 19:05:35 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/18 14:09:30 by youngcho         ###   ########.fr       */
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

#include <stdio.h>
static void	validation_arg_min(int argc)
{
	if (argc < 5)
	{
		printf("requires at least 4 arguments\n");
		exit(EXIT_FAILURE);
	}
}

static void	set_args_normal_mode(t_args *args_p, int argc, char *argv[])
{
	args_p->infile = *(argv + 1);
	args_p->outfile = *(argv + argc - 1);
	args_p->first_cmd_p = argv + 2;
	args_p->last_cmd_p = argv + argc - 2;
}

void	set_args(t_args *args_p, int argc, char *argv[])
{
	validation_arg_min(argc);
	// check_mode(args_p, argv[1]);
	// if (args_p->mode == NORMAL)
	set_args_normal_mode(args_p, argc, argv);
}