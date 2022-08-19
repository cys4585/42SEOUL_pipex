/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 18:44:13 by youngcho          #+#    #+#             */
/*   Updated: 2022/08/19 12:58:06 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "error.h"
#include "libft.h"

void	create_pipe(int pipefd[2])
{
	check_error(PIPE, "pipe", pipe(pipefd));
}

void	redirect(int argc, char *argv[], int *fd_infile_p, int *fd_outfile_p)
{
	check_error(ACCESS, argv[1], access(argv[1], R_OK));
	*fd_infile_p = open(argv[1], O_RDONLY);
	check_error(OPEN, argv[1], *fd_infile_p);
	*fd_outfile_p = open(argv[argc - 1], \
		O_CREAT | O_WRONLY | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	check_error(OPEN, argv[argc - 1], *fd_outfile_p);
	check_error(DUP, "dup2():", dup2(*fd_infile_p, STDIN_FILENO));
	check_error(DUP, "dup2():", dup2(*fd_outfile_p, STDOUT_FILENO));
}

char	**get_dir_name_arr(char *envp[])
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
			check_error_pointer(CUS_SPLIT, "get_envp(): Split failed.\n", dir_name_arr);
			break ;
		}
		i++;
	}
	check_error_pointer(CUS_NO_PATH, "get_envp(): No 'PATH=' in envp.\n", dir_name_arr);
	return (dir_name_arr);
}

char	*get_bin_path(char *envp[], char *file_name)
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
		check_error_pointer(CUS_JOIN, "get_bin_path(): Join failed.\n", tmp);
		bin_path = ft_strjoin(tmp, file_name);
		check_error_pointer(CUS_JOIN, "get_bin_path(): Join failed.\n", bin_path);
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
	check_error_pointer(CUS_SPLIT, "exec_cmd(): Split failed.\n", argv);
	// free 해야함
	bin_path = get_bin_path(envp, argv[0]);
	check_error_pointer(CUS_NO_BIN, "exec_cmd(): No bin file.\n", bin_path);
	execve(bin_path, argv, envp);
}

#include <stdio.h>
int	main(int argc, char *argv[], char *envp[])
{
	int		fd_infile;
	int		fd_outfile;
	
	check_error(CUS_REQ_ARG, "pipex: Requires 4 arguments.\n", argc);
	redirect(argc, argv, &fd_infile, &fd_outfile);
	exec_cmd(argv[2], envp);
	return (0);
}
