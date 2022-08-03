/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:31:36 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/03 12:37:40 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	check_args(int argc, char **argv, t_pipex *data)
{
	if (argc != 5)
		msg_error("Invalid number of arguments.\n", 1);
	get_file(argv[1], argv[argc - 1], data);
}

void	close_pipes(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < (data->pipe_nmbs))
	{
		close(data->pipe[i]);
		i++;
	}
	data->success = 1;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		rtn;

	check_args(argc, argv, &data);
	init_data(&data, argc, envp);
	while (data.idx < data.cmd_nmbs)
	{
		child(data, argv, envp);
		data.idx++;
	}
	close_pipes(&data);
	waitpid(-1, &rtn, 0);
	parent_close(&data, "success", 0);
	if (WEXITSTATUS(rtn) == 127)
		return (127);
	return (0);
}
