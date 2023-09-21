/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 20:05:03 by nklingsh          #+#    #+#             */
/*   Updated: 2023/09/20 21:02:42 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_after_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1] != '=')
		i++;
	while (str[i])
		i++;
	return (1);
}

int	valid_export(char **arguments)
{
	int	i;

	i = 1;
	while (arguments[i])
	{
		if (valid_first_letter(arguments[i], 0) == 0)
			return (0);
		if (valid_until_equal(arguments[i]) == 0)
			return (0);
		else if (valid_after_equal(arguments[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
