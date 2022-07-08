/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:30:08 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/07/07 22:58:38 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

static void	init_pipes(t_pipex *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_nmbs - 1)
	{
		if (pipe(data->pipe + (2 * i)) < 0)
			parent_close(data, "Failed to pipe\n", 4);
		i++;
	}
}

void	init_data(t_pipex *data, int argc, char *envp[])
{
	data->cmd_nmbs = argc - 3 - data->here_doc;
	data->pipe_nmbs = 2 * (data->cmd_nmbs - 1);
	data->idx = 0;
	data->success = 0;
	data->pipe = (int *)malloc(sizeof(int) * data->pipe_nmbs);
	if (!data->pipe)
		close_io_exit(data, "Failed to malloc\n", 2);
	data->cmd_paths = ft_split(find_path(envp), ':');
	if (!data->cmd_paths)
		pipe_free(data, "failed to malloc\n", 3);
	init_pipes(data);
}
