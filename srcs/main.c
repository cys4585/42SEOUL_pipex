/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:44:13 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/07 20:20:15 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <stdio.h>
int	main(int argc, char *argv[])
{
	t_args	args;
	
	set_args(&args, argc, argv);
	while (args.first_cmd_p <= args.last_cmd_p)
	{
		printf("%s\n", *args.first_cmd_p);
		args.first_cmd_p++;
	}
	// validation arg
	// run
	return (0);
}