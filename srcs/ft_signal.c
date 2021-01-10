/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:31:05 by marvin            #+#    #+#             */
/*   Updated: 2020/12/21 17:31:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_signal_handler(int signal)
{
	if(signal == SIGINT)
	{
		write(2, "\b\b  ", 4);
		write(2, "\n", 1);
		ft_putstr(BLUE"=> Minishell:"NORMAL);
	}
}

void	ft_signal_register(int *signaltab)
{
	int i;

	i = 0;
	while(signaltab[i])
	{
		signal(signaltab[i], ft_signal_handler);
		i++;
	}
}

void    ft_signal_init()
{
    int signaltab[] = {SIGINT, SIGQUIT, 0};
    ft_signal_register(signaltab);
}
