/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:16:11 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/28 21:16:12 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"
#include "tube.h"
#include "libft.h"

void					ft_room_free(t_room *room)
{
	if (!room)
		return ;
	free(room->a_tubes);
	free(room->bt_tubes);
	free(room->key.key);
	free(room);
}

t_room					*ft_room_construct(char *key, unsigned int status)
{
	t_room				*out;

	out = (t_room*)malloc(sizeof(t_room));
	if (!out)
		return (NULL);
	out->a_tubes = ft_array_construct(0);
	out->bt_tubes = ft_btree_construct(NULL);
	out->status = status;
	out->key = (t_data){key};
	if (!key || !out->a_tubes || !out->bt_tubes)
	{
		ft_room_free(out);
		return (NULL);
	}
	return (out);
}

int						ft_room_add_tube(t_tube *tube)
{
	if (!ft_array_add(&(tube->room1->a_tubes), tube) ||
		!ft_array_add(&(tube->room2->a_tubes), tube) ||
		!ft_btree_add(tube->room1->bt_tubes, (t_data*)tube) ||
		!ft_btree_add(tube->room2->bt_tubes, (t_data*)tube))
		return (0);
	return (1);
}

int						ft_room_create_tube_oriented(t_room *out, t_room *in)
{
	t_tube				*tube;

	tube = ft_tube_construct(out, in, 1, 1);
	if (!tube || !ft_room_add_tube(tube))
	{
		ft_tube_free(tube);
		return (0);
	}
	return (1);
}

int						ft_room_create_tube_pair(char *key1, char *key2,
	t_btree *bt_rooms)
{
	t_room				*in;
	t_room				*out;
	char				*key;
	int					result;

	result = -1;
	if (!(key = ft_strjoin(key1, "#IN")))
		return (0);
	in = (t_room*)ft_btree_get_data(bt_rooms, key);
	free(key);
	if (!(key = ft_strjoin(key2, "#OUT")))
		return (0);
	out = (t_room*)ft_btree_get_data(bt_rooms, key);
	free(key);
	if (in && out)
		result = ft_room_create_tube_oriented(out, in);
	if (!result || !(key = ft_strjoin(key2, "#IN")))
		return (0);
	in = (t_room*)ft_btree_get_data(bt_rooms, key);
	free(key);
	if (!(key = ft_strjoin(key1, "#OUT")))
		return (0);
	out = (t_room*)ft_btree_get_data(bt_rooms, key);
	free(key);
	return ((in && out) ? ft_room_create_tube_oriented(out, in) : result);
}

t_room					*ft_room_create_start(char *key, t_btree *bt_rooms)
{
	t_room				*start;

	if (!(start = ft_room_construct(key, 1)) || !ft_btree_add(bt_rooms, start))
	{
		ft_room_free(start);
		return (NULL);
	}
	return (start);
}

t_room					*ft_room_create_end(char *key, t_btree *bt_rooms)
{
	t_room				*end;

	if (!(end = ft_room_construct(key, 0)) || !ft_btree_add(bt_rooms, end))
	{
		ft_room_free(end);
		return (NULL);
	}
	return (end);
}

int						ft_room_create_pair(char *key, t_btree *bt_rooms)
{
	t_room				*in;
	t_room				*out;
	t_tube				*tube;

	in = ft_room_construct(ft_strjoin(key, "#IN"), 0);
	out = ft_room_construct(ft_strjoin(key, "#OUT"), 1);
	free(key);
	if (!in || !out)
		return (0);
	tube = ft_tube_construct(in, out, 1, 0);
	if (!tube || !ft_room_add_tube(tube))
	{
		ft_tube_free(tube);
		ft_room_free(in);
		ft_room_free(out);
		return (0);
	}
	return (1);
}
