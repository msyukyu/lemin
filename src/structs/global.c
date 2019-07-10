/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 13:53:19 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/03 14:37:17 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_global    *generate_global()
{
    t_global    *s;
    if (!(s = (t_global *)malloc(sizeof(t_global))))
        print(NULL);
    s->start = NULL;
    s->end = NULL;
    s->next_line = 0;
    return (s);
}

t_global    *destroy_global(t_global *s)
{
    if (s)
        free(s);
    return (NULL);
}