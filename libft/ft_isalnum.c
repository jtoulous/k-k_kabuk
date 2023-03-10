/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoulous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:41:37 by jtoulous          #+#    #+#             */
/*   Updated: 2022/09/28 14:09:37 by jtoulous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int z)
{
	if ((z >= 'A' && z <= 'Z') || (z >= 'a' && z <= 'z')
		|| (z >= '0' && z <= '9'))
		return (1);
	return (0);
}
