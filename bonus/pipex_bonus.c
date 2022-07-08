/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:31:36 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/07/07 22:59:35 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static int	args_in(char *arg, t_pipex *pipex)
{
	if (arg && !ft_strncmp("here_doc", arg, 9))
	{
		pipex->here_doc = 1;
		return (6);
	}
	else
	{
		pipex->here_doc = 0;
		return (5);
	}
}

static void	check_args(int argc, char **argv, t_pipex *data)
{
	if (argc < args_in(argv[1], data))
		msg_error("Invalid number of arguments.\n", 1);
	get_infile(argv, data);
	get_outfile(argv[argc - 1], data);
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

	check_args(argc, argv, &data);
	init_data(&data, argc, envp);
	while (data.idx < data.cmd_nmbs)
	{
		child(data, argv, envp);
		data.idx++;
	}
	close_pipes(&data);
	waitpid(-1, NULL, 0);
	parent_close(&data, "success", 0);
	return (0);
}
