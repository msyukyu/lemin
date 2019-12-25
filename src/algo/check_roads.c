/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_roads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 10:25:41 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/29 10:25:43 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void			cr_exchange(t_path **cur, t_path *other)
{
	t_step			*s1;
	t_step			*e1;
	t_step			*s2;
	t_step			*e2;

	s1 = (*cur)->cur->prev;
	e1 = other->cur;
	s2 = e1->prev;
	tube_inverse(s1->next->tube);
	e2 = s1->next->next;
	path_extract_step(*cur, e2->prev);
	while (s2->prev->room == e2->next->room)
	{
		tube_inverse(e2->tube);
		e2 = e2->next;
		s2 = s2->prev;
		path_extract_step(*cur, e2->prev);
		path_extract_step(other, s2->next);
	}
	s2 = s2->prev;
	path_extract_step(other, s2->next);
	s1->next = e1;
	e1->prev = s1;
	s2->next = e2;
	e2->prev = s2;
	s1 = (*cur)->last;
	(*cur)->last = other->last;
	other->last = s1;
	other->cur = e2;
	*cur = other;
}

static void			cr_cut_loop(t_path **path, t_step *other)
{
	t_step			*cur;

	tube_inverse(other->tube);
	cur = other->next;
	while (cur != (*path)->cur)
	{
		tube_inverse(cur->tube);
		path_extract_step(*path, cur);
		cur = cur->next;
	}
	while (other->prev->room == cur->next->room)
	{
		tube_inverse(cur->tube);
		other = other->prev;
		cur = cur->next;
		path_extract_step(*path, other->next);
		path_extract_step(*path, cur->prev);
	}
	path_extract_step(*path, other);
	(*path)->cur = cur;
}

static int			cr_find_other(t_path **path)
{
	t_path			*road;
	t_step			*cur;

	road = lemin->paths->first;
	while (road)
	{
		cur = road->first;
		while (cur)
		{
			if (cur->room == (*path)->cur->room)
			{
				if (road != *path)
				{
					road->cur = cur;
					cr_exchange(path, road);
					return (1);
				} 
				else if (road->cur->next != cur->next ||
					road->cur->prev != cur->prev)
				{
					cr_cut_loop(path, cur);
					return (1);
				}
			}
			cur = cur->next;
		}
		road = road->next;
	}
	return (0);
}

void				check_roads(void)
{
	t_path			*cur;
	t_tube			*t;

	cur = lemin->best_path;
	cur->cur = cur->first;
	while (cur->cur->next)
	{
		t = cur->cur->tube;
		if (t->cost == LEMIN_DIR_REVERSE)
		{
			if (!cr_find_other(&cur))
				lemin_error(LEMIN_ERR_ALGO);
		}
		tube_inverse(cur->cur->tube);
		cur->cur = cur->cur->next;
	}
}
