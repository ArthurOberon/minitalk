/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoberon <aoberon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:42:31 by aoberon           #+#    #+#             */
/*   Updated: 2023/02/28 13:57:10 by aoberon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _XOPEN_SOURCE 700
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

# define INITIALIZE_MESSAGE 0
# define RECEIVE_SIZE 1
# define RECEIVE_CHARACTER 2

int		ft_nbrlen(long nb);
int		ft_isspace(char c);
int		ft_atoi(const char *nptr);
int		ft_malloc(char **str, siginfo_t *info);
int		ft_atoi_base(char *nbr, char *base_from);

char	ft_strcat_character(char *dst, const char c);

void	ft_error(void);
void	ft_get_pid(void);
void	ft_putnbr(int nb);
void	ft_putchar(char c);
void	ft_putstr(char	*s);
void	ft_bzero(void *s, size_t n);
void	ft_print_and_reset(char *message, siginfo_t *info, int *status);

char	*ft_itoa(long n);
char	*ft_strcat(char *dst, const char *src);
char	*ft_strcat_without_end(char *dst, const char *str);

void	*ft_memset(void *s, int c, size_t n);

size_t	ft_strlen(const char *s);

#endif
