/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 18:58:54 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 18:49:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_get_shlv(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (envp[i][0] == 'S' && envp[i][1] == 'H' && envp[i][2] == 'L' &&
		envp[i][3] == 'V' && envp[i][4] == 'L')
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
			return (envp[i] + ft_strlen(str) + 1);
		i++;
	}
	return (NULL);
}

char	*ft_get_path(t_envir *envir, char *cmd)
{
	int		i;
	char	**all_bin;
	char	*path;

	i = -1;
	path = NULL;
	all_bin = ft_split(ft_get(envir->envp, "PATH"), ":");
	if (all_bin == NULL)
		return (ft_strdup(cmd));
	while (all_bin[++i] != NULL && path == NULL)
	{
		path = ft_search_dir(all_bin[i], cmd);
	}
	i = -1;
	while (all_bin[++i])
		free(all_bin[i]);
	free(all_bin);
	return (path);
}

char	*ft_walk_until_equal(char *str, int *length)
{
	int i;

	i = 0;
	if (str[0] == '\0' || str == NULL)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	*length = i;
	return (str + i + 1);
}
