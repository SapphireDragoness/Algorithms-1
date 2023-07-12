/*
 * Copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
 *
 * UPOalglib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * UPOalglib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include <stdio.h>
#include <upo/error.h>
#include <upo/queue.h>


static void test_create_destroy();
static void test_enqueue_dequeue();
static void test_head();
static void test_empty();
static void test_size();
static void test_clear();
static void test_null();

void test_create_destroy()
{
    upo_queue_t queue;

    queue = upo_queue_create();

    assert( queue != NULL );

    upo_queue_destroy(queue, 0);
}

void test_enqueue_dequeue()
{
    int value = 1;
    upo_queue_t queue;

    queue = upo_queue_create();

    upo_queue_enqueue(queue, &value);

    assert( upo_queue_size(queue) == 1 );

    upo_queue_dequeue(queue, 0);

    assert( upo_queue_size(queue) == 0 );

    upo_queue_destroy(queue, 0);
}

void test_head()
{
    int value1 = 1;
    int value2 = 2;
    upo_queue_t queue;

    queue = upo_queue_create();

    upo_queue_enqueue(queue, &value1);
    upo_queue_enqueue(queue, &value2);

    assert( upo_queue_peek(queue) != NULL );
    assert( *((int*) upo_queue_peek(queue)) == value1 );

    upo_queue_dequeue(queue, 0);

    assert( upo_queue_peek(queue) != NULL );
    assert( *((int*) upo_queue_peek(queue)) == value2 );

    upo_queue_dequeue(queue, 0);

    assert( upo_queue_peek(queue) == NULL );

    upo_queue_destroy(queue, 0);
}

void test_empty()
{
    int value = 1;
    upo_queue_t queue;

    queue = upo_queue_create();

    assert( upo_queue_is_empty(queue) );

    upo_queue_enqueue(queue, &value);

    assert( !upo_queue_is_empty(queue) );

    upo_queue_dequeue(queue, 0);

    assert( upo_queue_is_empty(queue) );

    upo_queue_destroy(queue, 0);
}

void test_size()
{
    upo_queue_t queue;
    size_t n = 10;
    size_t i;

    queue = upo_queue_create();

    /* Allocates n double's vectors of size 1,2,...,n, respectively */
    for (i = 1; i <= n; ++i)
    {
        size_t sz = (i+1)*sizeof(double);
        double *dv = malloc(sz);
        if (dv == NULL)
        {
            upo_throw_sys_error("Unable to allocate memory for a vector of double");
        }
        memset(dv, 0, sz);

        upo_queue_enqueue(queue, dv);
    }

    assert( upo_queue_size(queue) == n );

    upo_queue_dequeue(queue, 1);

    assert( upo_queue_size(queue) == (n-1) );

    upo_queue_destroy(queue, 1);
}

void test_clear()
{
    upo_queue_t queue;
    size_t n = 10;
    size_t i;

    queue = upo_queue_create();

    /* Allocates n double's vectors of size 1,2,...,n, respectively */
    for (i = 1; i <= n; ++i)
    {
        size_t sz = (i+1)*sizeof(double);
        double *dv = malloc(sz);
        if (dv == NULL)
        {
            upo_throw_sys_error("Unable to allocate memory for a vector of double");
        }
        memset(dv, 0, sz);

        upo_queue_enqueue(queue, dv);
    }

    assert( upo_queue_size(queue) == n );

    upo_queue_clear(queue, 1);

    assert( upo_queue_size(queue) == 0 );

    upo_queue_destroy(queue, 1);
}

void test_null()
{
    upo_queue_t queue = NULL;

    assert( upo_queue_size(queue) == 0 );

    assert( upo_queue_is_empty(queue) );

    upo_queue_enqueue(queue, NULL);

    upo_queue_clear(queue, 0);

    assert( upo_queue_size(queue) == 0 );

    upo_queue_destroy(queue, 0);
}


int main()
{
    printf("Test case 'create/destroy'... ");
    fflush(stdout);
    test_create_destroy();
    printf("OK\n");

    printf("Test case 'enqueue/dequeue'... ");
    fflush(stdout);
    test_enqueue_dequeue();
    printf("OK\n");

    printf("Test case 'head'... ");
    fflush(stdout);
    test_head();
    printf("OK\n");

    printf("Test case 'empty'... ");
    fflush(stdout);
    test_empty();
    printf("OK\n");

    printf("Test case 'size'... ");
    fflush(stdout);
    test_size();
    printf("OK\n");

    printf("Test case 'clear'... ");
    fflush(stdout);
    test_clear();
    printf("OK\n");

    printf("Test case 'null'... ");
    fflush(stdout);
    test_null();
    printf("OK\n");

    return 0;
}
