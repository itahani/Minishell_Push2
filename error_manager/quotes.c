/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:18:29 by itahani           #+#    #+#             */
/*   Updated: 2023/09/21 16:46:18 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quote_ends(char *str)
{
	int		i;
	t_quote	quote;

	quote.quote_bool = 0;
	quote.quote = 0;
	i = 0;
	while (str[i])
	{
		if ((is_quote(str[i]) && quote.quote_bool == 0))
		{
			quote.quote = str[i];
			quote.quote_bool++;
		}
		else if (str[i] == quote.quote && quote.quote_bool == 1)
		{
			quote.quote_bool = 0;
			quote.quote = 0;
		}
		i++;
	}
	if (quote.quote_bool != 0)
		return (ft_print_fd("Subject syntax error", 2), 1);
	return (0);
}

int	syntax_error(int count, t_init *init)
{
	if (count >= 2)
	{
		change_env_value("?", "2", init);
		ft_print_fd("syntax error near unexpected token `||'", 2);
		g_status_exit_code = 2;
		return (1);
	}
	if (count == 1)
	{
		change_env_value("?", "2", init);
		ft_print_fd("syntax error near unexpected token `|'", 2);
		g_status_exit_code = 2;
		return (1);
	}
	return (0);
}
