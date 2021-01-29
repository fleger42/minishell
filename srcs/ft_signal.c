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
		if(in_loop == 1)
		{
			write(STDERR_FILENO, "\b\b  ", 4);
			write(STDERR_FILENO, "\n", 1);
			write(STDERR_FILENO, RED"=> ", 10);
			write(STDERR_FILENO, BLUE"Minishell:"NORMAL, 22);
		}
		else
		{
			write(STDERR_FILENO, "\b\b  ", 4);
			write(STDERR_FILENO, "\n", 1);
			write(STDERR_FILENO, BLUE"=> Minishell:"NORMAL, 25);
		}
		ctrl_c_called = 1;
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
