/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_triplet_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 09:05:04 by ericpayen         #+#    #+#             */
/*   Updated: 2026/10/18 15:13:34 by ericpayen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rosetta.h"

static void	append_unit(t_dict *dict, int units)
{
	t_entry	*node;

	if (dict->out_buf.len < OUT_BUF_SIZE - 1)
		dict->out_buf.str[dict->out_buf.len++] = '-';
	node = lookup_exception(dict, units);
	if (node)
		print_dict_word(dict, node);
	else
		print_triplet_value(dict, units);
}

static int	print_tens_units(t_dict *dict, int tens, int units)
{
	t_entry	*node;

	node = lookup_exception(dict, tens);
	if (!node)
	{
		if (tens == 70 || tens == 90)
		{
			tens -= 10;
			units += 10;
		}
	}
	node = lookup_exception(dict, tens);
	if (!node)
		return (-1);
	print_dict_word(dict, node);
	if (units > 0)
		append_unit(dict, units);
	return (0);
}

static void	handle_hundreds(t_dict *dict, int *n)
{
	t_entry	*node;

	node = lookup_exception(dict, *n / 100);
	if (node)
		print_dict_word(dict, node);
	if (dict->out_buf.len < OUT_BUF_SIZE - 1)
		dict->out_buf.str[dict->out_buf.len++] = ' ';
	node = lookup_exception(dict, 100);
	if (node)
		print_dict_word(dict, node);
	*n %= 100;
	if (*n > 0 && dict->out_buf.len < OUT_BUF_SIZE - 1)
		dict->out_buf.str[dict->out_buf.len++] = ' ';
}

void	print_triplet_value(t_dict *dict, int n)
{
	t_entry	*node;

	if (n >= 100)
		handle_hundreds(dict, &n);
	if (n > 0)
	{
		node = lookup_exception(dict, n);
		if (node)
			print_dict_word(dict, node);
		else
		{
			if (print_tens_units(dict, (n / 10) * 10, n % 10) == -1)
				dict->error_state = 1;
		}
	}
}
