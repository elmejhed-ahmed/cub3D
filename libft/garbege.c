/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbege.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:03:28 by ael-mejh          #+#    #+#             */
/*   Updated: 2024/09/27 16:55:31 by ael-mejh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_garb **get_last_node()
{
    static t_garb *node = NULL;
    return &node;
}

void *gc_malloc(int size)
{
    t_garb **head = get_last_node();
    t_garb *node;
    char *ptr;

    ptr = malloc(size);
    if (!ptr)
        return NULL;
    node = (t_garb *)malloc(sizeof(t_garb));
    if (!node)
        return (free (ptr), NULL);
    node->ptr = ptr;
    node->next = *head;
    *head = node;
    return ptr;
}