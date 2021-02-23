/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 18:57:54 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 19:05:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_isbuiltin(char *str)
{
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0 ||
	ft_strcmp(str, "env") == 0 || ft_strcmp(str, "export") == 0
	|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "pwd") == 0)
		return (1);
	return (0);
}

char	*ft_extract_builtin(char *str)
{
	int		i;
	char	*cmd;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return (NULL);
	str = char_walk(str);
	while (str[i] && str[i] != ' ')
		i++;
	cmd = (char*)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != ' ')
	{
		cmd[i] = str[i];
		i++;
	}
	cmd[i] = '\0';
	return (cmd);
}

int		ft_is_builtin(char *str)
{
	int		i;
	char	*arg[6];

	arg[0] = "pwd";
	arg[1] = "unset";
	arg[2] = "cd";
	arg[3] = "echo";
	arg[4] = "env";
	arg[5] = NULL;
	i = 0;
	while (arg[i] != NULL)
	{
		if (strcmp(arg[i], str) == 0)
			return (1);
		i++;
	}
	return (0);
}
