#include "libft/libft.h"
#include "minishell.h"

void	free_and_close_all(t_data *data, int opt)
{
	if (opt == 2)
		free_lst(data->env);
	if (data->line)
	{	
		free (data->line);
		data->line = NULL;
	}
	if (data->argz)
	{	
		free_loop(data->argz);
		data->argz = NULL;
	}
	close_all(data);
	data->exec_stat = 1;
	unlinkz(NULL);
}

void	close_all(t_data *data)
{
	if (data->nb_cmds > 1 && data->exec_stat == 1)
		close_pipes(data->pipes, data->nb_cmds);
	if (data->infile != -1)
	{	
		close (data->infile);
		data->infile = -1;
	}
	if (data->outfile != -1)
	{	
		close (data->outfile);
		data->outfile = -1;
	}
	if (data->prev_outfile != -1)
	{	
		close (data->prev_outfile);
		data->prev_outfile = -1;
	}
}

void	close_pipes(int **pipes, int nb)
{
	int	z;
	
	z = 0;
	while (z < nb)
	{
		close (pipes[z][0]);
		close (pipes[z][1]);
		//free (pipes[z]);
		z++;
	}
	//free (pipes);
}

void	free_lst(t_list *lst)
{
	t_list	*tmp;
	
	tmp = lst->next;
	while (tmp)
	{
		free (lst);
		lst = tmp;
		tmp = tmp->next;
	}
	free (lst);
}

char	*env_search(t_list *env, char *var)
{
	t_list	*tmp;
	char	*value;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(var, tmp->env_copy, ft_strlen(var)) == 0)
		{
			value = ft_substr(tmp->env_copy, ft_strlen(var) + 1, 
					ft_strlen(tmp->env_copy) - ft_strlen(var));
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
