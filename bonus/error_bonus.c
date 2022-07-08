/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:14:57 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/07/07 22:59:21 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	msg_error(char *error, int exit_code)
{
	write(2, error, ft_strlen(error));
	exit(exit_code);
}

void	close_io_exit(t_pipex *data, char *error, int exit_code)
{
	close(data->infile);
	close(data->outfile);
	if (data->here_doc)
		unlink(".heredoc_tmp");
	if (!data->success)
		msg_error(error, exit_code);
}

void	pipe_free(t_pipex *data, char *error, int exit_code)
{
	free(data->pipe);
	close_io_exit(data, error, exit_code);
}

void	parent_close(t_pipex *data, char *error, int exit_code)
{
	int	i;

	i = 0;
	while (data->cmd_paths[i])
	{
		free(data->cmd_paths[i]);
		i++;
	}
	free(data->cmd_paths);
	pipe_free(data, error, exit_code);
}

void	free_cmd(t_pipex *data)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin("Unable to locate command: ", data->cmd_args[0]);
	while (data->cmd_args[i])
	{
		free(data->cmd_args[i]);
		i++;
	}
	free(data->cmd_args);
	free(data->cmd);
	write(2, tmp, ft_strlen(tmp));
	write(2, "\n", 1);
	free(tmp);
	exit(6);
}
