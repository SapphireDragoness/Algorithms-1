/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/sort.h>


/* Types and global data */

#define TEST_OK 1
#define TEST_FAIL 0

struct item_s
{
    long id;
    char* name;
};
typedef struct item_s item_t;

/* Comparators */

static int int_comparator(const void *a, const void *b);
static int double_comparator(const void *a, const void *b);
static int string_comparator(const void *a, const void *b);
static int item_comparator(const void *a, const void *b);

/* Test cases */
static int test_sort1();
static int test_sort2();
static int test_sort3();
static int test_sort4();
static int test_sort5();
static int test_sort6();


int main()
{
    size_t n = 6;
    size_t i = 0;
    int ret = 0;

    printf("*** [DISCLAIMER] ***************************************************************\n");
    printf("The following tests are provided as is, to allow you to quickly test your code.\n");
    printf("However, passing these tests is a necessary but not sufficient condition,\n");
    printf("meaning that they do not guarantee that your code is correct.\n");
    printf("In fact, your code may be wrong even it passes all these tests\n");
    printf("********************************************************************************\n\n");

    for (i = 1; i <= n; ++i)
    {
        switch (i)
        {
            case 1:
                ret = test_sort1();
                break;
            case 2:
                ret = test_sort2();
                break;
            case 3:
                ret = test_sort3();
                break;
            case 4:
                ret = test_sort4();
                break;
            case 5:
                ret = test_sort5();
                break;
            case 6:
                ret = test_sort6();
                break;
            default:
                fprintf(stderr, "ERROR: Unexpected test case number");
                abort();
        }
        printf("Test Sorting Algorithm: case #%lu => %s\n", i, (ret == TEST_OK) ? "[OK]" : "[FAIL]");
    }

    return 0;
}


int int_comparator(const void *a, const void *b)
{
    const int *aa = a;
    const int *bb = b;

    return (*aa > *bb) - (*aa < *bb);
}

int double_comparator(const void *a, const void *b)
{
    const double *aa = a;
    const double *bb = b;

    return (*aa > *bb) - (*aa < *bb);
}

int string_comparator(const void *a, const void *b)
{
    const char **aa = (const char**) a;
    const char **bb = (const char**) b;

    return strcmp(*aa, *bb);
}

int item_comparator(const void *a, const void *b)
{
    const item_t *aa = a;
    const item_t *bb = b;

    return (aa->id > bb->id) - (aa->id < bb->id);
}

int test_sort1()
{
    int a[] = {3,1,0,7,13,-1,6,-3,78};
    size_t n = sizeof a/sizeof a[0];
    int *expect_a = NULL;
    size_t i = 0;
    int ret = TEST_OK;

    /* Clones the test array and sorts it so that it can be used to check for correctness */

    expect_a = malloc(n*sizeof a[0]);
    if (expect_a == NULL)
    {
        perror("ERROR: Cannot allocate memory for check array");
        abort();
    }

    memcpy(expect_a, a, n*sizeof a[0]);

    qsort(expect_a, n, sizeof a[0], int_comparator);

    /* Applies the bidirectional bubble sort algorithm and checks that it works */

    upo_bidi_bubble_sort(a, n, sizeof a[0], int_comparator);
    for (i = 0; i < n && ret == TEST_OK; ++i)
    {
        if (int_comparator(&a[i], &expect_a[i]) != 0)
        {
            fprintf(stderr, "[file: %s, line: %d] ERROR: Index: %lu -> Expected element %d, got %d.\n", __FILE__, __LINE__, i, expect_a[i], a[i]);
            ret = TEST_FAIL;
        }
    }

    /* Clean-up memory */

    free(expect_a);

    return ret;
}

int test_sort2()
{
    int a[] = {1,2,3,4,5,6,7,8,9,10};
    size_t n = sizeof a/sizeof a[0];
    int *expect_a = NULL;
    size_t i = 0;
    int ret = TEST_OK;

    /* Clones the test array and sorts it so that it can be used to check for correctness */

    expect_a = malloc(n*sizeof a[0]);
    if (expect_a == NULL)
    {
        perror("ERROR: Cannot allocate memory for test array");
        abort();
    }

    memcpy(expect_a, a, n*sizeof a[0]);

    qsort(expect_a, n, sizeof a[0], int_comparator);

    /* Applies the bidirectional bubble sort algorithm and checks that it works */

    upo_bidi_bubble_sort(a, n, sizeof a[0], int_comparator);
    for (i = 0; i < n && ret == TEST_OK; ++i)
    {
        if (int_comparator(&a[i], &expect_a[i]) != 0)
        {
            fprintf(stderr, "[file: %s, line: %d] ERROR: Index: %lu -> Expected element %d, got %d.\n", __FILE__, __LINE__, i, expect_a[i], a[i]);
            ret = TEST_FAIL;
        }
    }

    /* Clean-up memory */

    free(expect_a);

    return ret;
}

int test_sort3()
{
    int a[] = {10,9,8,7,6,5,4,3,2,1};
    size_t n = sizeof a/sizeof a[0];
    int *expect_a = NULL;
    size_t i = 0;
    int ret = TEST_OK;

    /* Clones the test array and sorts it so that it can be used to check for correctness */

    expect_a = malloc(n*sizeof a[0]);
    if (expect_a == NULL)
    {
        perror("ERROR: Cannot allocate memory for test array");
        abort();
    }

    memcpy(expect_a, a, n*sizeof a[0]);

    qsort(expect_a, n, sizeof a[0], int_comparator);

    /* Applies the bidirectional bubble sort algorithm and checks that it works */

    upo_bidi_bubble_sort(a, n, sizeof a[0], int_comparator);
    for (i = 0; i < n && ret == TEST_OK; ++i)
    {
        if (int_comparator(&a[i], &expect_a[i]) != 0)
        {
            fprintf(stderr, "[file: %s, line: %d] ERROR: Index: %lu -> Expected element %d, got %d.\n", __FILE__, __LINE__, i, expect_a[i], a[i]);
            ret = TEST_FAIL;
        }
    }

    /* Clean-up memory */

    free(expect_a);

    return ret;
}

int test_sort4()
{
    double a[] = {3.0,1.3,0.4,7.8,13.2,-1.1,6.0,-3.2,78};
    size_t n = sizeof a/sizeof a[0];
    double *expect_a = NULL;
    size_t i = 0;
    int ret = TEST_OK;

    /* Clones the test array and sorts it so that it can be used to check for correctness */

    expect_a = malloc(n*sizeof a[0]);
    if (expect_a == NULL)
    {
        perror("ERROR: Cannot allocate memory for test array");
        abort();
    }

    memcpy(expect_a, a, n*sizeof a[0]);

    qsort(expect_a, n, sizeof a[0], double_comparator);

    /* Applies the bidirectional bubble sort algorithm and checks that it works */

    upo_bidi_bubble_sort(a, n, sizeof a[0], double_comparator);
    for (i = 0; i < n && ret == TEST_OK; ++i)
    {
        if (double_comparator(&a[i], &expect_a[i]) != 0)
        {
            fprintf(stderr, "[file: %s, line: %d] ERROR: Index: %lu -> Expected element %f, got %f.\n", __FILE__, __LINE__, i, expect_a[i], a[i]);
            ret = TEST_FAIL;
        }
    }

    /* Clean-up memory */

    free(expect_a);

    return ret;
}

int test_sort5()
{
    char *a[] = {"The","quick","brown","fox","jumps","over","the","lazy","dog"};
    size_t n = sizeof a/sizeof a[0];
    char **expect_a = NULL;
    size_t i = 0;
    int ret = TEST_OK;

    /* Clones the test array and sorts it so that it can be used to check for correctness */

    expect_a = malloc(n*sizeof a[0]);
    if (expect_a == NULL)
    {
        perror("ERROR: Cannot allocate memory for test array");
        abort();
    }

    memcpy(expect_a, a, n*sizeof a[0]);

    qsort(expect_a, n, sizeof a[0], string_comparator);

    /* Applies the bidirectional bubble sort algorithm and checks that it works */

    upo_bidi_bubble_sort(a, n, sizeof a[0], string_comparator);
    for (i = 0; i < n && ret == TEST_OK; ++i)
    {
        if (string_comparator(&a[i], &expect_a[i]) != 0)
        {
            fprintf(stderr, "[file: %s, line: %d] ERROR: Index: %lu -> Expected element '%s', got '%s'.\n", __FILE__, __LINE__, i, expect_a[i], a[i]);
            ret = TEST_FAIL;
        }
    }

    /* Clean-up memory */

    free(expect_a);

    return ret;
}

int test_sort6()
{
    item_t a[] = {{9,"john"},{8,"jane"},{7,"mary"},{6,"anthony"},{5,"stevie"},{4,"bob"},{3,"ann"},{2,"claire"},{1,"alice"}};
    size_t n = sizeof a/sizeof a[0];
    item_t *expect_a = NULL;
    size_t i = 0;
    int ret = TEST_OK;

    /* Clones the test array and sorts it so that it can be used to check for correctness */

    expect_a = malloc(n*sizeof a[0]);
    if (expect_a == NULL)
    {
        perror("ERROR: Cannot allocate memory for test array");
        abort();
    }

    memcpy(expect_a, a, n*sizeof a[0]);

    qsort(expect_a, n, sizeof a[0], item_comparator);

    /* Applies the bidirectional bubble sort algorithm and checks that it works */

    upo_bidi_bubble_sort(a, n, sizeof a[0], item_comparator);
    for (i = 0; i < n && ret == TEST_OK; ++i)
    {
        if (item_comparator(&a[i], &expect_a[i]) != 0)
        {
            fprintf(stderr, "[file: %s, line: %d] ERROR: Index: %lu -> Expected element {id: %ld, name: '%s'}, got {id: %ld, name: '%s'}.\n", __FILE__, __LINE__, i, expect_a[i].id, expect_a[i].name, a[i].id, a[i].name);
            ret = TEST_FAIL;
        }
    }

    /* Clean-up memory */

    free(expect_a);

    return ret;
}
