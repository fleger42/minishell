/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 01:57:48 by user42            #+#    #+#             */
/*   Updated: 2021/02/24 02:16:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_ctrld(t_envir *envir, char *line)
{
	int		exit_value;

	free(line);
	exit_value = envir->exit_code;
	ft_free_t_envir(envir);
	exit(exit_value);
}
