/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:59:26 by user42            #+#    #+#             */
/*   Updated: 2021/01/31 19:20:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_env(char **av, t_envir *envir)
{
	int	i;

	i = 0;
	if (av[1] != NULL)
	{
		ft_putstr("Invalid arg or option for env");
		ft_putchar('\n');
		return (1);
	}
	while (envir->envp[i] != NULL)
	{
		ft_putstr(envir->envp[i]);
		ft_putchar('\n');
		i++;
	}
	return (0);
}
