/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:06:08 by nklingsh          #+#    #+#             */
/*   Updated: 2023/09/21 11:55:34 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// le 3eme argument doit avoir un t_quote qui a un .quote egal a 0
// le 4eme 
char	*expand_env_and_quote(char *str, t_init *init, int quote, char *result)
{
	while (*str)
	{
		if ((*str == '\'' || *str == '\"') && quote == 0)
		{
			quote = *str;
			str++;
		}
		else if (*str == quote && quote != 0)
		{
			quote = 0;
			str++;
		}
		else if (quote != '\'' && is_env(str))
		{
			expand_env(&str, &result, init);
			if (at_least_oneisspace(result))
				init->splittos = 1;
		}
		else
			result = ft_join_str_in_init(init, *str++, result);
	}
	if (ft_strlen(result) == 0)
		return (NULL);
	return (result);
}

void	expand_word_node(t_init *init, t_lex_list *l_list)
{
	char	**splittos;

	l_list->word = expand_env_and_quote(l_list->word, init, 0, "");
	if (init->splittos == 1)
	{
		splittos = split_for_expand(init, l_list->word);
		delete_last_node_lex(&init->lst_lex);
		while (*splittos)
		{
			lstadd_back_lex(&init->lst_lex,
				lstnew_lex(*splittos, WORD, init));
			splittos++;
		}
		init->splittos = 0;
	}
}

void	expander_expanding(t_init *init)
{
	t_lex_list	*l_list;

	l_list = init->lst_lex;
	while (l_list)
	{
		if (l_list->operator == HERE_DOC)
			l_list = l_list->next;
		else if (l_list->operator == WORD)
			expand_word_node(init, l_list);
		l_list = l_list->next;
	}
}
