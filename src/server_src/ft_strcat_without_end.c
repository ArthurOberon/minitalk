/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_without_end.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:09:03 by aoberon           #+#    #+#             */
/*   Updated: 2023/02/24 20:43:36 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_strcat_without_end(char *dst, const char *str)
{
	unsigned int	i;
	size_t			length;

	i = 0;
	length = ft_strlen(dst);
	while (str[i] != '\0')
		dst[length++] = str[i++];
	return (dst);
}
