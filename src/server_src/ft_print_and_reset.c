/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_and_reset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:41:48 by aoberon           #+#    #+#             */
/*   Updated: 2023/02/28 13:24:25 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_print_and_reset(char *result, siginfo_t *info, int *status)
{
	ft_putstr("===== Receive a message from ");
	ft_putnbr(info->si_pid);
	ft_putstr(" ====== \n\n");
	ft_putstr(result);
	ft_putchar('\n');
	ft_putchar('\n');
	free(result);
	*status = INITIALIZE_MESSAGE;
}
