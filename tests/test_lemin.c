#include "lemin.h"

char		*in = "hivadeyfbcgopzwxklmjtunqsr";

t_global	*lemin = NULL;

void			display_hm(t_mhmap *mhmap, int (*f)(void *receiver, void *sent))
{
	printf("======display hashmap \n");
	ft_hmap_bnode_iteration(NULL, (t_hmap*)mhmap, f);
}

int				show_tube(void *receiver, void *sent)
{
	t_tube		*tube;

	tube = (t_tube*)sent;
	if (!receiver)
	{
		printf("%s - %s\n", tube->room1->key.key, tube->room2->key.key);
		return (1);
	}
	return (0);
}

void			display_room(t_room *room)
{
	printf("--------display room \n");
	printf("		name : %s\n", room->key.key);
	printf("		display room's tube hasmap\n");
	display_hm(&room->hm_tubes, show_tube);
}

int				show_room(void *receiver, void *sent)
{
	t_room		*room;

	room = (t_room*)sent;
	if (!receiver)
	{
		display_room(room);
		return (1);
	}
	return (0);
}

void			display_start(t_room *start)
{
	printf("======display start \n");
	display_room(start);
}

void			display_end(t_room *end)
{
	printf("======display end \n");
	display_room(end);
}

void			display_n_ants(int n_ants)
{
	printf("======display n_ants \n");
	printf("%d\n", n_ants);
}

int				main(void)
{
	global_construct();
	global_construct_hashmap_rooms(4);
	read_lemin();
	printf("======display lemin's room hashmap\n");
	display_hm(&lemin->hm_rooms, show_room);
	display_start(lemin->start);
	display_end(lemin->end);
	display_n_ants(lemin->n_ants);
	global_free();
	return (0);
}
