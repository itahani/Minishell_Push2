/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:52:38 by nklingsh          #+#    #+#             */
/*   Updated: 2023/09/19 14:24:58 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_wait_pid(t_exec_init exec_init)
{
	pid_t	tmp;
	int		status;

	(void)exec_init;
	while (1)
	{
		tmp = wait(&status);
		if (WIFEXITED(status))
			g_status_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			g_status_exit_code = 128 + WTERMSIG(status);
			if (g_status_exit_code == 130 || g_status_exit_code == 131)
				printf("\n");
		}
		if (tmp == -1)
			break ;
	}
}

int	here_doc_exist(t_init *init)
{
	t_token_list	*tmp;
	t_str_list		*tmp2;
	int			i;

	i = 0;
	tmp = init->lst_token;
	tmp2 = NULL;
	print_all_token(init->lst_token);
	while (tmp)
	{
		tmp2 = tmp->delimeter;
		while(tmp2)
		{
			if (tmp2->str_list)
				i++;
			tmp2 = tmp2->next;
			printf("----xxxx------- \n");
		}
		printf("i :  ---   %d\n", i);
		tmp = tmp->next;
	}
	return (i);
}

void	exec_child_process(t_init *init, int i, t_exec_init exec_init)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	exec_all_pid(init, i, exec_init);
}

void	exec_parent_process(t_exec_init *exec_init)
{
	if (signal(SIGINT, SIG_IGN) != SIG_ERR)
		g_status_exit_code = 131;
	if (exec_init->pipetmp)
		close(exec_init->pipetmp);
	exec_init->pipetmp = exec_init->mypipe[0];
	close(exec_init->mypipe[1]);
}

void	initialize_exec(t_init *init, int *i, t_exec_init *exec_init)
{
	if (ft_size_token(init->lst_token) == 0)
		return ;
	*exec_init = init_exec_struct(init);
	*i = 0;
}
