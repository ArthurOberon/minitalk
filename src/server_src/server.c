/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:42:20 by aoberon           #+#    #+#             */
/*   Updated: 2023/02/24 17:55:25 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk.h"

char	*g_result;

void	ft_step_one(int *status, siginfo_t *info)
{
	g_result = malloc(sizeof(char) * 33);
	if (!g_result)
	{
		ft_putstr("An error occurred while receive the message.\n");
		if (kill(info->si_pid, SIGUSR2) == -1)
			ft_putstr("Unable to send error to the client.\n");
		exit(EXIT_FAILURE);
	}
	ft_bzero(g_result, 33);
	*status = 0;
}

void	ft_step_two(int *status, int sig, siginfo_t *info)
{
	int			size;

	if (sig == SIGUSR1)
		ft_strcat_without_end(g_result, "0");
	if (sig == SIGUSR2)
		ft_strcat_without_end(g_result, "1");
	if (g_result[31] != '\0')
	{
		*status = 1;
		size = ft_malloc(&g_result, info);
		ft_bzero(g_result, size + 1);
	}
}

void	ft_step_three(int *status, int sig, siginfo_t *info)
{
	static char	octet[9] = {0};

	if (sig == SIGUSR1)
		ft_strcat(octet, "0");
	if (sig == SIGUSR2)
		ft_strcat(octet, "1");
	if (ft_strlen(octet) == 8)
	{
		if (ft_strcat_int(g_result, ft_atoi_base(octet, "01")) == '\0')
			ft_print_and_reset(g_result, info, status);
		ft_bzero(octet, 9);
	}
}

void	handle_sig(int sig, siginfo_t *info, void *ucontext)
{
	static int	status = 0;

	(void)ucontext;
	if (status == 2)
		ft_step_one(&status, info);
	if (status == 0)
		ft_step_two(&status, sig, info);
	else
		ft_step_three(&status, sig, info);
	if (kill(info->si_pid, SIGUSR1) == -1)
	{
		ft_putstr("Unable to send signal to the client.\n");
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr("Welcome to the Minitalk server. Starting...\n");
	g_result = malloc(sizeof(char) * 33);
	if (!g_result)
		return (1);
	ft_bzero(g_result, 33);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handle_sig;
	ft_get_pid();
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		;
}
