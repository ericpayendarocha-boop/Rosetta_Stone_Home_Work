/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rosetta.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 08:41:14 by ericpayen         #+#    #+#             */
/*   Updated: 2026/10/18 15:43:10 by ericpayen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROSETTA_H
# define ROSETTA_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define OUT_BUF_SIZE 16384
# define ARENA_SIZE 16384

typedef struct s_parse
{
	int		mode;
	int		n_idx;
	int		t_idx;
	int		has_colon;
}			t_parse;

typedef struct s_buf
{
	char	str[OUT_BUF_SIZE];
	int		len;
}			t_buf;

typedef struct s_entry
{
	int				value;
	int				triplet_count;
	int				text_offset;
	struct s_entry	*next;
}			t_entry;

typedef struct s_dict
{
	t_entry	*head;
	t_buf	out_buf;
	char	text_arena[ARENA_SIZE];
	int		arena_len;
	int		error_state;
}			t_dict;

void		print_dict_word(t_dict *dict, t_entry *node);
t_entry		*lookup_exception(t_dict *dict, int value);
t_entry		*lookup_scale(t_dict *dict, int triplet_count);
void		print_triplet_value(t_dict *dict, int n);
void		print_large_number(t_dict *dict, const char *num_str);
int			load_dictionary_from_file(t_dict *dict, const char *filename);
int			reset_or_save(t_dict *d, char *num_buf, t_parse *p);
int			ft_strlen(const char *str);
int			check_input(int argc, char **argv, const char **p, char **v);
void		free_dictionary(t_dict *dict);
void		save_entry(t_dict *d, char *nb_buf, int n_idx, int t_idx);

#endif
