/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:32:59 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/07/12 20:12:27 by Ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**cmd_paths;
	char	*cmd;
	char	**cmd_args;
	pid_t	pid;
	int		cmd_nmbs;
	int		pipe_nmbs;
	int		*pipe;
	int		idx;
	int		success;
}				t_pipex;

//hadle_file.c
void	get_file(char *infile, char *outfile, t_pipex *data);

//error.c
void	msg_error(char *error, int exit_code);
void	parent_close(t_pipex *data, char *error, int exit_code);
void	pipe_free(t_pipex *data, char *error, int exit_code);
void	close_io_exit(t_pipex *data, char *error, int exit_code);
void	free_cmd(t_pipex *data);

//init_data.c
void	init_data(t_pipex *data, int argc, char *envp[]);

//child.c
int		child(t_pipex data, char **argv, char **envp);
void	close_pipes(t_pipex *data);

#endif