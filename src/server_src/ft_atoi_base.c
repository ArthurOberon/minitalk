/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:12:52 by aoberon           #+#    #+#             */
/*   Updated: 2023/02/24 20:43:36 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_inbase(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (i);
}

int	ft_atoi_base(char *nbr, char *base_from)
{
	int	sign;
	int	result;
	int	base_length;

	sign = 1;
	result = 0;
	base_length = ft_strlen(base_from);
	while (ft_isspace(*nbr))
		nbr++;
	if (*nbr == '-' || *nbr == '+')
	{
		if (*nbr == '-')
			sign *= -1;
		nbr++;
	}
	while (*nbr >= '0' && *nbr <= '9')
	{
		result = result * base_length + ft_inbase(*nbr, base_from);
		nbr++;
	}
	return (result * sign);
}
