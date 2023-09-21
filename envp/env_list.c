/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:51:43 by itahani           #+#    #+#             */
/*   Updated: 2023/09/20 21:12:04 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_name_size(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (i > 0 && env[i - 1] == '+')
		i--;
	return (i);
}

char	*env_name(char *env)
{
	int		namelength;
	char	*name;

	if (env[0] == '=')
		return (NULL);
	namelength = env_name_size(env);
	if (namelength <= 0)
		return (NULL);
	name = malloc((namelength + 1) * sizeof(char));
	if (name == NULL)
		return (NULL);
	ft_strncpy(name, env, namelength);
	name[namelength] = '\0';
	return (name);
}

t_env_list	*set_env_i(void)
{
	t_env_list	*env_list;
	char		*value;
	char		*name;

	env_list = NULL;
	name = ft_strdup("OLDPWD");
	lstadd_back_env(&env_list, lstnew_env(name, NULL));
	env_list->i = 0;
	name = ft_strdup("PWD");
	value = getcwd(NULL, 0);
	lstadd_back_env(&env_list, lstnew_env(name, value));
	name = ft_strdup("SHLVL");
	value = ft_strdup("0");
	lstadd_back_env(&env_list, lstnew_env(name, value));
	name = ft_strdup("_");
	value = ft_strdup("/usr/bin/env");
	lstadd_back_env(&env_list, lstnew_env(name, value));
	return (env_list);
}

t_env_list	*init_env_list(char **env)
{
	t_env_list	*env_list;
	char		*value;
	char		*name;
	int			i;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		name = env_name(env[i]);
		value = ft_strdup(getenv(name));
		lstadd_back_env(&env_list, lstnew_env(name, value));
		env_list->i = 0;
		i++;
	}
	if (i == 0)
		return (set_env_i());
	return (env_list);
}

void	set_value(t_env_list *tmp, char *new_value)
{
	free(tmp->value);
	if (new_value)
		tmp->value = ft_strdup(new_value);
	else
		tmp->value = NULL;
}
