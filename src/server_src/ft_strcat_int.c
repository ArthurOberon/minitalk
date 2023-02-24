/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:09:03 by aoberon           #+#    #+#             */
/*   Updated: 2023/02/24 20:43:36 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#include <stdio.h>

char	ft_strcat_int(char *dst, const char c)
{
	size_t			length;

	if (c == '\0')
		return (c);
	length = ft_strlen(dst);
	dst[length++] = c;
	dst[length] = '\0';
	return (c);
}
