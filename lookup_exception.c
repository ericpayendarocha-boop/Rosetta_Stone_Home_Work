/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_exception.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 09:00:45 by ericpayen         #+#    #+#             */
/*   Updated: 2026/10/18 10:56:45 by ericpayen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rosetta.h"

int	lookup_exception(t_dict *dict, int power, int value)
{
	int	i;

	i = 0;
	while (i < dict->loaded_exceptions_count)
	{
		if (dict->tab_powers[i] == power
			&& dict->tab_values[i] == value)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}
