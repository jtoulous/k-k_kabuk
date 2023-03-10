/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoichon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 09:29:04 by agoichon          #+#    #+#             */
/*   Updated: 2023/03/09 15:04:49 by agoichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	built_in_exit_utils(t_data *data)
{
	int	i;

	i = 0;
	while (data->argz[1][i])
	{	
		if (ft_isdigit(data->argz[1][i]) == 0)
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("exit: numeric argument required\n", 2);
			free_and_close_all(data, 3);
			free_loop(data->envp);
			exit(2);
		}					
		i++;
	}
}

static void	error_exit(void)
{
	g_err_code = 2;
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd(" numeric argument required\n", 2);
}

static void	error_many_arg(void)
{
	printf("exit\n");
	ft_putstr_fd(" exit: too many arguments\n", 2);
	g_err_code = 1;
}	

int	built_in_exit(t_data *data)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	if (data->argz[1] != NULL && data->argz[2] == NULL)
	{	
		built_in_exit_utils(data);
		if (ft_atol_check(data->argz[1]) == 1)
		{
			error_exit();
			return (1);
		}	
		n = ft_atol(data->argz[1]);
	}
	if (data->argz[2] != NULL)
	{	
		error_many_arg();
		return (0);
	}
	ft_putstr_fd("exit\n", 1);
	free_and_close_all(data, 3);
	free_loop(data->envp);
	g_err_code = n % 256;
	exit (n % 256);
}
