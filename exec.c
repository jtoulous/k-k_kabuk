/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoichon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:33:20 by agoichon          #+#    #+#             */
/*   Updated: 2023/02/05 10:31:08 by agoichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_multiple(t_data *data)
{
	int 	pid;
		
	data->exp->envp = convert_env(data->env);
	pid = fork();
	if (pid == 0)
	{
		if (data->infile != -1)
			dup2(data->infile, STDIN_FILENO);
		if (data->outfile != -1)
			dup2(data->outfile, STDOUT_FILENO);
		else
			dup2(data->pipes[0][1], STDOUT_FILENO);
		close_all(data);
		if (built_in(data))
			execve(data->argz[0], data->argz, data->exp->envp);	
	}
	free_loop(data->exp->envp);
}

void	last_multiple(t_data *data, int z)
{
	int 	pid;
		
	data->exp->envp = convert_env(data->env);
	pid = fork();
	if (pid == 0)
	{
		if (data->prev_outfile != -1)
			dup2(data->prev_outfile, STDIN_FILENO);	
		else if (data->infile != -1)
			dup2(data->infile, STDIN_FILENO);
		else
			dup2(data->pipes[z - 1][0], STDIN_FILENO);
		if (data->outfile != -1)
			dup2(data->outfile, STDOUT_FILENO);
		close_all(data);
		if (built_in(data))	
			execve(data->argz[0], data->argz, data->exp->envp);
	}
	free_loop(data->exp->envp);
}

void	multiple_exec(t_data *data, int z)
{
	int 	pid;
		
	data->exp->envp = convert_env(data->env);
	pid = fork();
	if (pid == 0)
	{
		if (data->prev_outfile != -1)
			dup2(data->prev_outfile, STDIN_FILENO);	
		else if (data->infile != -1)
			dup2(data->infile, STDIN_FILENO);
		else
			dup2(data->pipes[z - 1][0], STDIN_FILENO);
		if (data->outfile != -1)
			dup2(data->outfile, STDOUT_FILENO);
		else 
			dup2(data->pipes[z][1], STDOUT_FILENO);
		close_all(data);
		if (built_in(data))
			execve(data->argz[0], data->argz, data->exp->envp);
	}
	free_loop(data->exp->envp);
}

/*void	builtinz_multi_first(t_data *data)
{
	int	pid;
	
	pid = fork();
	if (pid == 0)
	{
		if (data->infile != -1)
			dup2(data->infile, STDIN_FILENO);
		if (data->outfile != -1)
			dup2(data->outfile, STDOUT_FILENO);
		else 
			dup2(data->pipe[0][1], STDOUT_FILENO);
		close_all(data);
		execbd(data);
	}
	wait (0);
}

void	builtinz_multi(t_data *data, int z)
{
	int	pid;
	
	pid = fork();
	if (pid == 0)
	{	
		if (data->infile != -1)
			dup2(data->infile, STDIN);
		else
			dup2(data->pipes[z - 1][], STDIN)
		execbd(data->argz[0], data->argz, data->env);
}*/

/*void	multi_exec(t_data *data, int z)
{
	if (built_in(data) >= 0)
	{
		if (z == 0)
			builtinz_multi_first(data);
		else
			builtinz_multi(data, z);
	}
	else
	{	
		if (z == 0)
			regular_multi_first(data, z);
		else
			regular_multi(data, z);
	}
}*/
