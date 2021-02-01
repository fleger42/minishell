/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:58:54 by user42            #+#    #+#             */
/*   Updated: 2021/01/31 17:51:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_get_shlv(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (envp[i][0] == 'S' && envp[i][1] == 'H' && envp[i][2] == 'L' && envp[i][3] == 'V' && envp[i][4] == 'L')
			return (ft_atoi(envp[i] + 6));
		i++;
	}
	return (0);
}

char	*ft_get(char **envp, char *str)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0)
			return(envp[i] + ft_strlen(str) + 1);
		i++;
	}
	return (NULL);	
}
