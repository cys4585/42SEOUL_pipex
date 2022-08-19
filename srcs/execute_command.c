/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:59:52 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/19 15:35:05 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_command.h"
#include "error.h"
#include "libft.h"

static char	**get_dir_name_arr(char *envp[])
{
	char	**dir_name_arr;
	int		i;

	dir_name_arr = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			dir_name_arr = ft_split(envp[i] + 5, ':');
			check_custom_error(CUS_SPLIT, "Split failed.\n", dir_name_arr);
			break ;
		}
		i++;
	}
	check_custom_error(CUS_NO_PATH, "No 'PATH=' in envp.\n", dir_name_arr);
	return (dir_name_arr);
}

static char	*get_bin_path(char *envp[], char *file_name)
{
	char	**dir_name_arr;
	char	*tmp;
	char	*bin_path;
	int		i;

	bin_path = NULL;
	dir_name_arr = get_dir_name_arr(envp);
	i = 0;
	while (dir_name_arr[i])
	{
		tmp = ft_strjoin(dir_name_arr[i], "/");
		check_custom_error(CUS_JOIN, "Join failed.\n", tmp);
		bin_path = ft_strjoin(tmp, file_name);
		check_custom_error(CUS_JOIN, "Join failed.\n", bin_path);
		free(tmp);
		if (access(bin_path, X_OK) == 0)
			break ;
		free(bin_path);
		bin_path = NULL;
		i++;
	}
	ft_free_splited_arr(dir_name_arr);
	return (bin_path);
}

void	exec_cmd(char *cmd, char *envp[])
{
	char	*bin_path;
	char	**argv;

	// free 해야함
	argv = ft_split(cmd, ' ');
	check_custom_error(CUS_SPLIT, "exec_cmd(): Split failed.\n", argv);
	// free 해야함
	bin_path = get_bin_path(envp, argv[0]);
	check_custom_error(CUS_NO_BIN, "exec_cmd(): No bin file.\n", bin_path);
	check_error(EXECVE, "execve(): ", execve(bin_path, argv, envp));
}
