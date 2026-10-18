/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup_exception.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 09:00:45 by ericpayen         #+#    #+#             */
/*   Updated: 2026/10/18 15:46:25 by ericpayen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rosetta.h"

t_entry	*lookup_exception(t_dict *dict, int value)
{
	t_entry	*curr;

	curr = dict->head;
	while (curr != NULL)
	{
		if (curr->value == value && curr->triplet_count == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

t_entry	*lookup_scale(t_dict *dict, int triplet_count)
{
	t_entry	*curr;

	curr = dict->head;
	while (curr != NULL)
	{
		if (curr->triplet_count == triplet_count)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void	free_dictionary(t_dict *dict)
{
	t_entry	*curr;
	t_entry	*next_node;

	if (!dict || !dict->head)
		return ;
	curr = dict->head;
	while (curr != NULL)
	{
		next_node = curr->next;
		free(curr);
		curr = next_node;
	}
	dict->head = NULL;
}
