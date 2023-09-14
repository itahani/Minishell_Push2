/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:51:43 by itahani           #+#    #+#             */
/*   Updated: 2023/09/07 19:51:39 by itahani          ###   ########.fr       */
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

t_env_list	*set_env_i()
{
	t_env_list	*env_list;
	char		*value;
	char		*name;

	env_list = NULL;
	name = ft_strdup("PWD");
	value = getcwd(NULL, 0);
	lstadd_back_env(&env_list, lstnew_env(name, value));
	env_list->i = 0;
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
	// printf("\n\n-=-=-=-=-=-=-=- DEBUT ATTRIBUTION ENV -=-=-=-=-=-=-=-\n\n");
	while (env[i])
	{
		// printf("Tour %i : ", i);
		name = env_name(env[i]);
		value = ft_strdup(getenv(name));
		lstadd_back_env(&env_list, lstnew_env(name, value));
		env_list->i = 0;
		// printf("env name = [%s] value = [%s]\n", name, value);
		i++;
	}
	if (i == 0) // signifie que env est vide
		return (set_env_i());
	// printf("\n\n-=-=-=-=-=-=-=- FIN ATTRIBUTION ENV -=-=-=-=-=-=-=-\n\n");
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

char	*get_env_value(char *name, t_init *init)
{
	t_env_list	*env_list;

	env_list = init->lst_env;
	while (env_list)
	{
		if (ft_strsame(name, env_list->name))
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}
