/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 10:20:00 by ericpayen         #+#    #+#             */
/*   Updated: 2026/10/18 10:52:53 by ericpayen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rosetta.h"

static int	validate_string_number(const char *str, int *start, int *end)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = 0;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	*start = i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		has_digit = 1;
		i++;
	}
	if (!has_digit)
		return (0);
	*end = i;
	return (1);
}

int	check_input(int argc, char **argv, const char **path, char **val_str)
{
	int	start;
	int	end;

	*path = "numbers.dict";
	if (argc < 2 || argc > 3)
		return (0);
	*val_str = argv[argc - 1];
	if (argc == 3)
		*path = argv[1];
	start = 0;
	end = 0;
	if (!validate_string_number(*val_str, &start, &end))
		return (0);
	*val_str = &((*val_str)[start]);
	(*val_str)[end - start] = '\0';
	return (1);
}
