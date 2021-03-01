/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 02:50:14 by user42            #+#    #+#             */
/*   Updated: 2021/03/01 02:51:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char		*ft_malloc_string_token(char *line, int i)
{
	int		count;
	int		allow;
	char	*ret;

	allow = 0;
	count = 0;
	while (line[i] != '\0' && (line[i] != ' ' || allow == 1))
	{
		if ((line[i] == '\'' || line[i] == '\"') && allow == 0)
		{
			count++;
			allow = 1;
		}
		else if ((line[i] == '\'' || line[i] == '\"') && allow == 1)
		{
			count++;
			allow = 0;
		}
		else
			count++;
		i++;
	}
	return ((ret = malloc(sizeof(char) * (count + 1))));
}

char		*ft_gst_add(char *line, char *string, int *i)
{
	int		allow;
	int		j;

	j = 0;
	allow = 0;
	while (line[*i] && (line[*i] != ' ' || allow == 1))
	{
		if (((*i > 0 && line[*i - 1] != '\\') &&
		(line[*i] == '\'' || line[*i] == '\"')) && allow == 0)
		{
			string[j++] = line[*i];
			allow = 1;
		}
		else if (((*i > 0 && line[*i - 1] != '\\') &&
		(line[*i] == '\'' || line[*i] == '\"')) && allow == 1)
		{
			string[j++] = line[*i];
			allow = 0;
		}
		else
			string[j++] = line[*i];
		(*i)++;
	}
	string[j] = '\0';
	return (string);
}

char		*ft_get_string_token(char *line, int *i)
{
	char	*string;
	int		allow;
	int		j;

	j = 0;
	allow = 0;
	*i += ft_char_tono_space(line + *i);
	string = ft_malloc_string_token(line, *i);
	string = ft_gst_add(line, string, i);
	return (string);
}

t_token		*ft_token_to_cmd(t_token *token)
{
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD && token->prev->type < NEXT)
			token = token->next;
	}
	return (token);
}

t_token		*ft_next_sep(t_token *token)
{
	while (token && (token->type == CMD || token->type == ARG))
		token = token->next;
	return (token);
}
