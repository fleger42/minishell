/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 07:41:36 by user42            #+#    #+#             */
/*   Updated: 2021/02/11 07:47:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_cdhome(char *pwd[4])
{
	write(2, pwd[0], ft_strlen(pwd[0]));
	write(2, "\n", 1);
	if (chdir(pwd[0]) != 0)
	{
		free(pwd[0]);
		free(pwd[1]);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}
