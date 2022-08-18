/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngcho <youngcho@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:52:42 by youngcho          #+#    #+#             */
/*   Updated: 2022/03/28 17:19:59 by youngcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	recursion_write(int n, int fd)
{
	if (n > 0)
	{
		recursion_write(n / 10, fd);
		write(fd, &"0123456789"[n % 10], 1);
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		recursion_write(-(n / 10), fd);
		write(fd, &"0123456789"[-(n % 10)], 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == 0)
		write(fd, "0", 1);
	else
		recursion_write(n, fd);
}
