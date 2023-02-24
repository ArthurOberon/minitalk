/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:42:16 by aoberon           #+#    #+#             */
/*   Updated: 2023/02/24 22:17:10 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_discuss = 0;

void	handle_sig_receive(int sig)
{
	if (sig == SIGUSR1)
		g_discuss = 1;
	if (sig == SIGUSR2)
	{
		ft_putstr("The server detected an error during message's reception.\n");
		exit(EXIT_FAILURE);
	}
}

void	client(char *pid_char, char character)
{
	int		i;
	int		pid;

	i = 0;
	pid = ft_atoi(pid_char);
	while (i <= 7)
	{
		g_discuss = 0;
		if (character & (0b10000000 >> i++))
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_error();
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_error();
		}
		while (g_discuss == 0)
			pause();
	}
}

void	client_int(char *pid_char, int size)
{
	int		i;
	int		pid;

	i = 0;
	pid = ft_atoi(pid_char);
	if (pid <= 0)
		return (ft_putstr("Error: pid must be positive.\n"), exit(EXIT_FAILURE));
	while (i < 32)
	{
		g_discuss = 0;
		if (size & (0b10000000000000000000000000000000 >> i++))
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_error();
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_error();
		}
		while (g_discuss == 0)
		{
			pause();
		}
	}
}

void	ft_simplified_print(char *str, char *pid)
{
	ft_putstr(str);
	ft_putstr(pid);
	ft_putstr("...\n");
}

//SIGUSR1 = 0;
//SIGUSR2 = 1;

int	main(int argc, char **argv)
{
	size_t				i;
	size_t				length;
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handle_sig_receive;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	i = 0;
	if (argc != 3)
		return (ft_putstr("Too few or too many arguments\n"), 1);
	ft_simplified_print("Sending the size of the message to ", argv[1]);
	length = ft_strlen(argv[2]);
	client_int(argv[1], length);
	ft_simplified_print("Sending the message to ", argv[1]);
	while (i <= length)
	{
		client(argv[1], argv[2][i++]);
		while (g_discuss == 0)
			pause();
	}
	ft_putstr("The whole message was received by the server !\n");
	return (0);
}
