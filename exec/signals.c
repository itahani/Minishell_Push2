/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:49:10 by itahani           #+#    #+#             */
/*   Updated: 2023/09/06 20:31:31 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status_exit_code = 130;
	return ;
}

void	heredoc_sigint(int sig)
{
	(void)sig;
	if (write(1, "\n", 1) == -1)
		return ;
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
	close(0);
	g_status_exit_code = 130;
	// return ;
}
