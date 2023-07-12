/**
 * \file upo/queue_private.h
 *
 * \brief Private header for the queue data structure.
 *
 * \author SapphireDragoness
 *
 * \copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 *  This file is part of UPOalglib.
 *
 *  UPOalglib is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  UPOalglib is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UPO_QUEUE_PRIVATE_H
#define UPO_QUEUE_PRIVATE_H

#include <upo/queue.h>
#include <stddef.h>

/** \brief Defines the structure of each node of the doubly-linked list implementing the queue. */
struct upo_queue_node_s
{
    void *data; /**< User-provided data. */
    struct upo_queue_node_s *next; /**< Pointer to the next node in the list. */
    struct upo_queue_node_s *prev; /**< Pointer to the previous node in the list. */
};
/** \brief Defines the type of a list node. */
typedef struct upo_queue_node_s upo_queue_node_t;

/** \brief Defines the structure of the list implementing the queue. */
struct upo_queue_s
{
    upo_queue_node_t *head; /**< The front of the list. */
    upo_queue_node_t *tail; /**< The back of the list. */
    size_t size; /**< The size of the list. This field allows to guarantee a constant complexity for the `size` operation. */
};

#endif