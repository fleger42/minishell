/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 19:06:22 by user42            #+#    #+#             */
/*   Updated: 2021/02/23 02:14:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ft_qo2(char *line, int i, int quote_open)
{
	if (((line[i] == '\'' || line[i] == '\"') &&
	(line == 0 || line[i - 1] != '\\')) && quote_open == 0)
		quote_open = 1;
	else if (((line[i] == '\'' || line[i] == '\"') &&
	(line == 0 || line[i - 1] != '\\')) && quote_open == 1)
		quote_open = 0;
	return (quote_open);
}

char	*ft_malloc_new_line(char *line)
{
	int		i;
	int		count;
	char	*new_line;
	int		quote_open;

	quote_open = 0;
	i = 0;
	count = 0;
	while (line[i])
	{
		quote_open = ft_qo2(line, i, quote_open);
		if (quote_open == 0 && ((i > 0 && ft_issep(line[i]) &&
		line[i - 1] != ' ') || (i > 0 && ft_issep(line[i - 1]) &&
		line[i] != ' ')))
		{
			count++;
		}
		count++;
		i++;
	}
	new_line = malloc(sizeof(char) * (count + 1));
	return (new_line);
}

int		t_str_removecount(char *str)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] != '\'' && str[i] != '\"') || (i > 0 && str[i - 1] == '\\'))
			count++;
		i++;
	}
	return (count);
}

char	*ft_str_remove(char *str)
{
	char	*new;
	int		i;
	int		count;
	int		j;

	count = 0;
	i = 0;
	if (ft_strcmp(str, "\"\"") == 0 || ft_strcmp(str, "\'\'") == 0)
	{
		free(str);
		return (ft_strdup("\'\'"));
	}
	count = t_str_removecount(str);
	new = malloc(sizeof(char) * (count + 1));
	j = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] != '\'' && str[i] != '\"') || (i > 0 && str[i - 1] == '\\'))
			new[j++] = str[i];
		i++;
	}
	free(str);
	new[j] = '\0';
	return (new);
}

char	*ft_add_spacesep(char *line)
{
	int		i;
	int		j;
	char	*new_line;
	int		quote_open;

	i = 0;
	j = 0;
	quote_open = 0;
	new_line = ft_malloc_new_line(line);
	while (line[i])
	{
		quote_open = ft_qo2(line, i, quote_open);
		if (quote_open == 0 && ((i > 0 && ft_issep(line[i]) &&
		line[i - 1] != ' ') || (i > 0 && ft_issep(line[i - 1])
		&& line[i] != ' ')))
		{
			if (!(line[i] == '>' && line[i - 1] == '>'))
				new_line[j++] = ' ';
		}
		new_line[j++] = line[i];
		i++;
	}
	new_line[j] = '\0';
	free(line);
	return (new_line);
}
