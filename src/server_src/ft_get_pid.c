/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:56:40 by aoberon           #+#    #+#             */
/*   Updated: 2023/02/24 17:55:25 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"

void	ft_get_pid(void)
{
	int	pid;

	pid = getpid();
	ft_putstr("Server Started ! You can send a message with the PID ");
	ft_putnbr(pid);
	ft_putstr(" !\n");
}
