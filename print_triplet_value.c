/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_triplet_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 09:05:04 by ericpayen         #+#    #+#             */
/*   Updated: 2026/10/18 10:57:47 by ericpayen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rosetta.h"

static void	append_unit(t_dict *dict, int units)
{
	int	idx_u;

	if (dict->out_buf.len < OUT_BUF_SIZE - 1)
		dict->out_buf.str[dict->out_buf.len++] = '-';
	idx_u = lookup_exception(dict, 0, units);
	if (idx_u != -1)
		print_dict_word(dict, idx_u);
	else
		print_triplet_value(dict, units);
}

static int	print_tens_units(t_dict *dict, int tens, int units)
{
	int	idx_t;

	if (lookup_exception(dict, 0, tens) == -1)
	{
		if (tens == 70 || tens == 90)
		{
			tens -= 10;
			units += 10;
		}
	}
	idx_t = lookup_exception(dict, 0, tens);
	if (idx_t == -1)
		return (-1);
	print_dict_word(dict, idx_t);
	if (units > 0)
		append_unit(dict, units);
	return (0);
}

static void	handle_hundreds(t_dict *dict, int *n)
{
	int	idx;

	idx = lookup_exception(dict, 0, *n / 100);
	if (idx != -1)
		print_dict_word(dict, idx);
	if (dict->out_buf.len < OUT_BUF_SIZE - 1)
		dict->out_buf.str[dict->out_buf.len++] = ' ';
	idx = lookup_exception(dict, 0, 100);
	if (idx != -1)
		print_dict_word(dict, idx);
	*n %= 100;
	if (*n > 0 && dict->out_buf.len < OUT_BUF_SIZE - 1)
		dict->out_buf.str[dict->out_buf.len++] = ' ';
}

void	print_triplet_value(t_dict *dict, int n)
{
	int	idx;

	if (n >= 100)
		handle_hundreds(dict, &n);
	if (n > 0)
	{
		idx = lookup_exception(dict, 0, n);
		if (idx != -1)
			print_dict_word(dict, idx);
		else
		{
			if (print_tens_units(dict, (n / 10) * 10, n % 10) == -1)
				dict->loaded_exceptions_count = -1;
		}
	}
}
