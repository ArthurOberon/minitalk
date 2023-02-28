/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:42:20 by aoberon           #+#    #+#             */
/*   Updated: 2023/02/28 14:29:27 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*g_message;

static void	ft_initialize_g_message(int *status, siginfo_t *info)
{
	g_message = malloc(sizeof(char) * 33);
	if (!g_message)
	{
		ft_putstr("An error occurred while receive the message.\n");
		if (kill(info->si_pid, SIGUSR2) == -1)
			ft_putstr("Unable to send error to the client.\n");
		exit(EXIT_FAILURE);
	}
	ft_bzero(g_message, 33);
	*status = RECEIVE_SIZE;
}

static void	ft_receive_size(int *status, int sig, siginfo_t *info)
{
	int			size;

	if (sig == SIGUSR1)
		ft_strcat_without_end(g_message, "0");
	if (sig == SIGUSR2)
		ft_strcat_without_end(g_message, "1");
	if (g_message[31] != '\0')
	{
		size = ft_malloc(&g_message, info);
		ft_bzero(g_message, size + 1);
		*status = RECEIVE_CHARACTER;
	}
}

static void	ft_receive_character(int *status, int sig, siginfo_t *info)
{
	static char	octet[9] = {0};

	if (sig == SIGUSR1)
		ft_strcat(octet, "0");
	if (sig == SIGUSR2)
		ft_strcat(octet, "1");
	if (ft_strlen(octet) == 8)
	{
		if (ft_strcat_character(g_message, ft_atoi_base(octet, "01")) == '\0')
			ft_print_and_reset(g_message, info, status);
		ft_bzero(octet, 9);
	}
}

static void	handle_sig(int sig, siginfo_t *info, void *ucontext)
{
	static int	status = INITIALIZE_MESSAGE;

	(void)ucontext;
	if (status == INITIALIZE_MESSAGE)
		ft_initialize_g_message(&status, info);
	if (status == RECEIVE_SIZE)
		ft_receive_size(&status, sig, info);
	else
		ft_receive_character(&status, sig, info);
	if (kill(info->si_pid, SIGUSR1) == -1)
	{
		ft_putstr("Unable to send signal to the client.\n");
		exit(EXIT_FAILURE);
	}
}

//SIGUSR1 = 0;
//SIGUSR2 = 1;

int	main(void)
{
	struct sigaction	sa;

	ft_putstr("Welcome to the Minitalk server. Starting...\n");
	// g_message = malloc(sizeof(char) * 33);
	// if (!g_message)
	// 	return (1);
	// ft_bzero(g_message, 33);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handle_sig;
	ft_get_pid();
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		;
}
