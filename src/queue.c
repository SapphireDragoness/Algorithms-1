/**
 * \file upo/queue.h
 *
 * \brief Queue implementation.
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

#include "queue_private.h"
#include <stdio.h>
#include <stdlib.h>

upo_queue_t upo_queue_create() {
    upo_queue_t queue = malloc(sizeof(struct upo_queue_s));
    if(queue == NULL) {
        perror("Unable to create a queue, memory allocation failed.");
        abort();
    }
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    return queue;
}

void upo_queue_destroy(upo_queue_t queue, int destroy_data) {
    if(queue != NULL) {
        upo_queue_clear(queue, destroy_data);
        free(queue);
    }
}

void upo_queue_clear(upo_queue_t queue, int destroy_data) {
    if(queue == NULL || upo_queue_is_empty(queue)) return;
    while(queue->head != queue->tail) {
        upo_queue_node_t *node = queue->tail;
        queue->tail = node->prev;
        if(destroy_data) {
            free(node->data);
        }
        free(node);
        queue->size -= 1;
    }
    free(queue->head);
    queue->size -= 1;
}

void upo_queue_enqueue(upo_queue_t queue, void *data) {
    if(queue != NULL) {
        upo_queue_node_t *node = malloc(sizeof(upo_queue_node_t));
        if(node == NULL) { 
            perror("Unable to allocate node.\n");
            abort();
        }
        node->data = data;
        node->prev = NULL;
        node->next = NULL;
        if(queue->head == NULL) {
            queue->head = node;
            queue->tail = node;
        }
        else {
            node->prev = queue->tail;
            queue->tail->next = node;
            queue->tail = queue->tail->next;
        }
        queue->size += 1;
    }
}

void upo_queue_dequeue(upo_queue_t queue, int destroy_data) {
    if(queue != NULL) {
        upo_queue_node_t *node = queue->head;
        queue->head = node->next;
        if(queue->size == 1) {
            queue->head = NULL;
        }
        if(destroy_data) {
            free(node->data);
        }
        free(node);
        queue->size -= 1;
    }
}

void* upo_queue_peek(const upo_queue_t queue) {
    if(queue == NULL || queue->head == NULL) {
        return NULL;
    }
    return queue->head->data;
}

size_t upo_queue_size(const upo_queue_t queue) {
    if(queue == NULL) {
        return 0;
    }
    return queue->size;
}

int upo_queue_is_empty(const upo_queue_t queue) {
    if(queue == NULL) {
        return 1;
    }
    return queue->size > 0 ? 0 : 1;
}