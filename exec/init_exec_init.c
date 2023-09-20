/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:29:59 by nklingsh          #+#    #+#             */
/*   Updated: 2023/09/20 17:15:56 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void 	special_print(t_exec_init *exec_init, t_init *init, char *str)
{
	printf("%s \n", str);
	close(exec_init->mypipe[1]);
	close(exec_init->mypipe[0]);
	close(exec_init->pipetmp);
	free_env_list(init->lst_env);
	free_s_init(init);
	exit(0);
}

t_exec_init	init_exec_struct(t_init *init)
{
	t_exec_init	exec_init;

	exec_init.nb_command = ft_size_token(init->lst_token);
	exec_init.pipetmp = dup(STDIN_FILENO);
	exec_init.pid = malloc(sizeof(pid_t) * exec_init.nb_command);
	lstaddback_malloc(init, lstnew_malloc(exec_init.pid));
	return (exec_init);
}

void	exec_all_pid(t_init *init, int i, t_exec_init exec_init)
{
	const int	output_fd = init->lst_token->o_fd;
	const int	input_fd = init->lst_token->i_fd;

	if (check_infile_fd(init->lst_token,&exec_init, init) || check_outfile_fd(init->lst_token))
		exit(0);
	dup2(exec_init.pipetmp, STDIN_FILENO);
	if (i != exec_init.nb_command - 1)
	{
		dup2(exec_init.mypipe[1], STDOUT_FILENO);
	}
	if (output_fd == REDIR_OUT)
		redir_out_manager(init->lst_token);
	else if (output_fd == APP_OUT)
		app_out_manager(init->lst_token);
	if (input_fd == REDIR_IN)
		redir_in_manager(init->lst_token);
	else if (input_fd == HERE_DOC)
		redir_here_doc(init->lst_token);
	if (init->lst_token->arguments != NULL && \
		ft_strlen(init->lst_token->arguments->str_list) != 0)
			command_manager(init, &exec_init, i);
	else if (init->lst_token->arguments && init->lst_token->arguments->str_list == NULL)
		special_print(&exec_init, init, " : Command not found");
	special_print(&exec_init, init, "ciao Bello");
	exit(0);
}
