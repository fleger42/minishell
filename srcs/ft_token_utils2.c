/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 02:50:37 by user42            #+#    #+#             */
/*   Updated: 2021/03/01 02:51:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token		*ft_previous_sep(t_token *token)
{
	while (token && (token->type == CMD || token->type == ARG))
		token = token->prev;
	return (token);
}

int			ft_get_type_token(t_token *token)
{
	if (ft_strcmp(token->string, "|") == 0)
		return (PIPE);
	if (ft_strcmp(token->string, ";") == 0)
		return (NEXT);
	if (ft_strcmp(token->string, "<") == 0)
		return (LEFT);
	if (ft_strcmp(token->string, ">>") == 0)
		return (DOUBLERIGHT);
	if (ft_strcmp(token->string, ">") == 0)
		return (RIGHT);
	if (token->prev == NULL ||
	(token->prev->type != ARG && token->prev->type != CMD))
		return (CMD);
	else
		return (ARG);
	return (0);
}

t_token		*ft_get_actual_token(char *line, int *i)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	token->string = ft_get_string_token(line, i);
	return (token);
}

t_token		*ft_tokenize(char *line)
{
	t_token		*elem2;
	t_token		*elem1;
	int			i;

	i = 0;
	elem2 = NULL;
	elem1 = NULL;
	while (line[i])
	{
		elem1 = ft_get_actual_token(line, &i);
		elem1->prev = elem2;
		if (elem2)
			elem2->next = elem1;
		elem2 = elem1;
		elem2->type = ft_get_type_token(elem2);
		i += ft_char_tono_space(line + i);
	}
	if (elem1)
		elem1->next = NULL;
	if (elem1)
	{
		while (elem1 && elem1->prev)
			elem1 = elem1->prev;
	}
	return (elem1);
}

void		ft_free_token(t_token *token)
{
	t_token *temp;

	while (token)
	{
		temp = token->next;
		free(token->string);
		free(token);
		token = temp;
	}
}
