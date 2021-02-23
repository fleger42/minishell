/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 19:14:31 by user42            #+#    #+#             */
/*   Updated: 2021/02/12 07:33:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void				ft_putstr(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		ft_putchar(str[i]);
}

char				*ft_catpy(char *first, char *second)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(first) + ft_strlen(second) + 1));
	while (first[++i] != '\0')
		new[i] = first[i];
	while (second[j] != '\0')
	{
		new[i] = second[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}

long long int		ft_llatoi(const char *nptr)
{
	int						i;
	unsigned long long int	result;
	int						signe;

	signe = 1;
	i = 0;
	result = 0;
	while ((nptr[i] >= 8 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i++] - 48);
	}
	result = result * signe;
	return (result);
}

int					ft_atoi(const char *nptr)
{
	int				i;
	int				result;
	int				signe;

	signe = 1;
	i = 0;
	result = 0;
	while ((nptr[i] >= 8 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i++] - 48);
	}
	result = result * signe;
	return (result);
}
