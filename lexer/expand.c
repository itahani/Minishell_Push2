/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 15:06:08 by nklingsh          #+#    #+#             */
/*   Updated: 2023/09/18 15:34:24 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	handle_quote(char **str, t_quote *quote)
// {	
// 	if ((*str[0] == '\'' || *str[0] == '\"') && quote->quote == 0)
// 	{
// 		quote->quote = *str[0];
// 		(*str)++;
// 	}
// 	if (*str[0] == quote->quote && quote->quote != 0)
// 	{
// 		quote->quote = 0;
// 		(*str)++;
// 	}
// }

// static void	handle_env(t_init *init, char **str, char **result, t_quote *quote)
// {
// 	if (quote->quote != '\'' && is_env(*str))
// 	{
// 		expand_env(str, result, init);
// 		if (at_least_oneisspace(*result))
// 			init->lst_lex->must_split = 1;
// 	}
// 	else
// 		*result = ft_join_str_in_init(init, *str[0]++, *result);
// }

char	*expand_env_and_quote(char *str, t_init *init)
{
	t_quote	quote;
	char	*result;

	result = "";
	quote.quote = 0;
	while (*str)
	{
		if ((*str == '\'' || *str == '\"') && quote.quote == 0)
		{
			quote.quote = *str;
			str++;
		}
		else if (*str == quote.quote && quote.quote != 0)
		{
			quote.quote = 0;
			str++;
		}
		else if (quote.quote != '\'' && is_env(str))
		{
			expand_env(&str, &result, init);
			if (at_least_oneisspace(result))
				init->lst_lex->must_split = 1;
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

	l_list->word = expand_env_and_quote(l_list->word, init);
	if (l_list->must_split == 1)
	{
		splittos = split_for_expand(init, l_list->word);
		delete_last_node_lex(&init->lst_lex);
		while (*splittos)
		{
			lstadd_back_lex(&init->lst_lex,
				lstnew_lex(*splittos, WORD, init));
			splittos++;
		}
		l_list->must_split = 0;
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
