/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:52:24 by nklingsh          #+#    #+#             */
/*   Updated: 2023/09/20 21:03:40 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_to_linked_list(t_init *init, char **str)
{
	if (str[1] == NULL)
		update_env_or_export(str[0], str[1], init, VALID);
	else
		update_env_or_export(str[0], str[1], init, 0);
}

char	**exportator(char *str)
{
	char	**splittos;

	splittos = ft_split(str, '=');
	return (splittos);
}

void	the_real_export(char **arguments, t_init *init)
{
	char	**str;
	int		i;

	i = 1;
	str = NULL;
	if (size_double_tab(arguments) == 1)
		print_lst_env(init->lst_env);
	else if (size_double_tab(arguments) >= 2)
	{
		if (valid_export(arguments) == 1)
		{
			while (arguments[i])
			{
				str = exportator(arguments[i]);
				export_to_linked_list(init, str);
				free_tab_tab(str);
				i++;
			}
		}
	}
	else
		printf("error too many arugments");
}
