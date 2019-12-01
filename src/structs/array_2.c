/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 11:44:17 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/16 11:44:19 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_array				*ft_array_construct(unsigned int size)
{
	t_array			*out;

	out = (t_array*)malloc(sizeof(t_array));
	if (!out)
		return (NULL);
	if (size > 0)
	{
		out->items = malloc(size * sizeof(void*));
		out->size = size;
	}
	else
	{
		out->items = malloc(sizeof(void*));
		out->size = 1;
	}
	if (!out->items)
	{
		free(out);
		return (NULL);
	}
	out->n_items = 0;
	return (out);
}

void				ft_array_free(t_array *array)
{
	if (!array)
		return ;
	free(array->items);
	free(array);
}

static int			ft_array_double_size(t_array *array, int skip_from)
{
	unsigned int	addon;
	void			**items;
	unsigned int	n_items;

	if (2 * array->size <= array->size || (skip_from > -1 &&
		(unsigned int)skip_from >= array->n_items))
		return (0);
	items = (void**)malloc(2 * array->size * sizeof(void*));
	if (!items)
		return (0);
	addon = (skip_from == -1) ? 0 : 1;
	n_items = 0;
	while (n_items < array->n_items + addon)
	{
		if (n_items == (unsigned int)skip_from)
			n_items++;
		items[n_items] = array->items[n_items];
		n_items++;
	}
	free(array->items);
	array->items = items;
	array->n_items = n_items;
	array->size = 2 * array->size;
	return (1);
}

int					ft_array_add(t_array *array, void *item)
{
	if (!item)
		return (-1);
	if (array->n_items >= array->size && !ft_array_double_size(array, -1))
		return (0);
	array->items[array->n_items] = item;
	array->n_items++;
	return (1);
}

int					ft_array_insert(t_array *array, unsigned int index,
	void *item)
{
	unsigned int	i;

	if (index > array->n_items)
		return (0);
	if (!item)
		return (-1);
	if (index == array->n_items)
		return (ft_array_add(array, item));
	i = array->n_items;
	if (array->n_items >= array->size && !ft_array_double_size(array, index))
		return (0);
	else
		while (i-- > index)
			array->items[i + 1] = array->items[i];
	array->items[index] = item;
	array->n_items++;
	return (1);
}