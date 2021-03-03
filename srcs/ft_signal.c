/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 05:15:07 by user42            #+#    #+#             */
/*   Updated: 2021/03/01 04:58:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		if (g_in_child == 0)
		{
			if (g_in_loop == 1)
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
			g_ctrl_c_called = 1;
		}
	}
}

void	ft_signal_register(int *signaltab)
{
	int i;

	i = 0;
	while (signaltab[i])
	{
		signal(signaltab[i], ft_signal_handler);
		i++;
	}
}

void	ft_signal_init(void)
{
	int signaltab[3];

	signaltab[0] = SIGINT;
	signaltab[1] = SIGQUIT;
	signaltab[2] = 0;
	ft_signal_register(signaltab);
}
