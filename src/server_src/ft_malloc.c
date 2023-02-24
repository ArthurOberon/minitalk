/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:57:13 by aoberon           #+#    #+#             */
/*   Updated: 2023/02/24 20:43:36 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_malloc(char **str, siginfo_t *info)
{
	int	size;

	size = ft_atoi_base(*str, "01");
	free(*str);
	*str = malloc(sizeof(char) * (size + 1));
	if (!*str)
	{
		ft_putstr("An error occurred while receive the message.\n");
		if (kill(info->si_pid, SIGUSR2) == -1)
		{
			ft_putstr("Unable to send error to the client.\n");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_FAILURE);
	}
	return (size);
}
