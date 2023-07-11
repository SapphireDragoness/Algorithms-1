/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2016 University of Piemonte Orientale, Computer Science Institute
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
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/bst.h>
#include <upo/test.h>


#define TEST_OK 1
#define TEST_FAIL 0


static int test_bst1();
static int test_bst2();
static int test_bst3();
static int test_bst4();
static int test_bst5();
static int test_empty_bst();
static int test_int_bst(int *keys, int *values, size_t n, int *no_keys, size_t m);
static int test_str_bst(char **keys, int *values, size_t n, char **no_keys, size_t m);
static int test_bst(void *keys, size_t key_sz, void *values, size_t value_sz, size_t n, void *no_keys, size_t m, upo_bst_comparator_t key_cmp, char* (*key_to_string)(const void*), char* (*value_to_string)(const void*));
extern const void* upo_bst_check(const upo_bst_t, const void*);
extern void upo_bst_dump(const upo_bst_t, FILE *, char* (*)(const void*), int, char* (*)(const void*), int);
extern void* upo_bst_put(upo_bst_t, void*, void*);


int main()
{
    const size_t n = 5;

    size_t i = 0;
    int ret = TEST_FAIL;

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
                ret = test_bst1();
                break;
            case 2:
                ret = test_bst2();
                break;
            case 3:
                ret = test_bst3();
                break;
            case 4:
                ret = test_bst4();
                break;
            case 5:
                ret = test_bst5();
                break;
            default:
                fprintf(stderr, "ERROR: Unexpected test case number");
                abort();
        }
        printf("Test BST #%lu => %s\n", i, (ret == TEST_OK) ? "[OK]" : "[FAIL]");
    }

    ret = test_empty_bst();
    printf("Test Empty BST => %s\n", (ret == TEST_OK) ? "[OK]" : "[FAIL]");

    return 0;
}


int test_bst1()
{
    /*
     * BST:
     *       8
     *     /   \
     *    3     10
     *   / \     \
     *  1   6     14
     *     / \   /
     *    4   7 13
     */

    int keys[] = {8, 3, 1, 6, 4, 7, 10, 14, 13};
    int values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int no_keys[] = {0, 2, 5, 9, 11, 16};
    size_t n = sizeof keys/sizeof keys[0];
    size_t m = sizeof no_keys/sizeof no_keys[0];

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );
    assert( m == sizeof no_keys/sizeof no_keys[0] );

    return test_int_bst(keys, values, n, no_keys, m);
}

int test_bst2()
{
    /*
     * BST:
     *            11
     *           /
     *          9
     *         /
     *        7
     *       /
     *      5
     *     /
     *    3
     *   /
     *  1
     */

    int keys[] = {11, 9, 7, 5, 3, 1};
    int values[] = {0, 1, 2, 3, 4, 5};
    int no_keys[] = {0, 2, 4, 6, 8, 10, 12};
    size_t n = sizeof keys/sizeof keys[0];
    size_t m = sizeof no_keys/sizeof no_keys[0];

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );
    assert( m == sizeof no_keys/sizeof no_keys[0] );

    return test_int_bst(keys, values, n, no_keys, m);
}

int test_bst3()
{
    /*
     * BST:
     * 1
     *  \
     *   3
     *    \
     *     5
     *      \
     *       7
     *        \
     *         9
     *          \
     *           11
     */

    int keys[] = {1, 3, 5, 7, 9, 11};
    int values[] = {0, 1, 2, 3, 4, 5};
    int no_keys[] = {0, 2, 4, 6, 8, 10, 12};
    size_t n = sizeof keys/sizeof keys[0];
    size_t m = sizeof no_keys/sizeof no_keys[0];

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );
    assert( m == sizeof no_keys/sizeof no_keys[0] );

    return test_int_bst(keys, values, n, no_keys, m);
}

int test_bst4()
{
    /*
     * BST:
     *      11
     *     / \
     *    3   13
     *   / \   \
     *  1   9   19
     *     /   /
     *    7   15
     *   /     \
     *  5       17
     */

    int keys[] = {11, 3, 1, 9, 7, 5, 13, 19, 15, 17};
    int values[] = {-11, -3, -1, -9, -7, -5, -13, -19, -15, -17};
    int no_keys[] = {0, 2, 4, 8, 10, 12, 14, 16, 18};
    size_t n = sizeof keys/sizeof keys[0];
    size_t m = sizeof no_keys/sizeof no_keys[0];

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );
    assert( m == sizeof no_keys/sizeof no_keys[0] );

    return test_int_bst(keys, values, n, no_keys, m);
}

int test_bst5()
{
    /*
     *         "aae"
     *          / \
     *      "aac" "aaj"
     *       / \      \
     *   "aaa" "aad"  "aak"
     */

    char *keys[] = {"aae", "aaj", "aac", "aad", "aaa", "aak"};
    int values[] = {-5, -10, -3, -4, -1, -11};
    char *no_keys[] = {"AAA", "xyz", "aaf"};
    size_t n = sizeof keys/sizeof keys[0];
    size_t m = sizeof no_keys/sizeof no_keys[0];

    assert( n == sizeof keys/sizeof keys[0] );
    assert( n == sizeof values/sizeof values[0] );
    assert( m == sizeof no_keys/sizeof no_keys[0] );

    return test_str_bst(keys, values, n, no_keys, m);
}

int test_empty_bst()
{
    return test_int_bst(NULL, NULL, 0, NULL, 0);
}

int test_int_bst(int *keys, int *values, size_t n, int *no_keys, size_t m)
{
    return test_bst(keys, sizeof keys[0], values, sizeof values[0], n, no_keys, m, upo_test_int_cmp, upo_test_int_to_string, upo_test_int_to_string);
}

int test_str_bst(char **keys, int *values, size_t n, char **no_keys, size_t m)
{
    return test_bst(keys, sizeof keys[0], values, sizeof values[0], n, no_keys, m, upo_test_str_cmp, upo_test_str_to_string, upo_test_int_to_string);
}

int test_bst(void *keys, size_t key_sz, void *values, size_t value_sz, size_t n, void *no_keys, size_t m, upo_bst_comparator_t key_cmp, char* (*key_to_string)(const void*), char* (*value_to_string)(const void*))
{
    upo_bst_t bst = NULL;
    unsigned char *pck = keys;
    unsigned char *pcv = values;
    unsigned char *pcnk = no_keys;
    size_t i;
    int ret = TEST_OK;

    /* Creates BST */

    bst = upo_bst_create(key_cmp);

    assert( bst != NULL );

    if (n > 0)
    {
        // Non-empty BST

        // Populate BST

        for (i = 0; i < n; ++i)
        {
            upo_bst_put(bst, pck + i*key_sz, pcv + i*value_sz);
        }

        // Find the predecessor of each key

        // Keys
        for (i = 0; i < n && ret == TEST_OK; ++i)
        {
            void *pkey = NULL;
            const void *p_pred = NULL;
            const void *p_pred_check = NULL;

            pkey = malloc(key_sz);
            if (pkey == NULL)
            {
                perror("[ERROR] Unable to allocate memory for key");
                abort();
            }

            memcpy(pkey, pck + i*key_sz, key_sz);

            p_pred = upo_bst_predecessor(bst, pkey);

            p_pred_check = upo_bst_check(bst, pkey);

            if (p_pred == NULL && p_pred_check != NULL)
            {
                char *key_str = key_to_string(pkey);
                char *pred_check_str = key_to_string(p_pred_check);
                fprintf(stderr, "[file: %s, line: %d] ERROR: Input key: '%s' -> Expected predecessor '%s', got none.\n", __FILE__, __LINE__, key_str, pred_check_str);
                free(pred_check_str);
                free(key_str);
                fprintf(stderr, "[file: %s, line: %d]: <BST>\n", __FILE__, __LINE__);
                upo_bst_dump(bst, stderr, key_to_string, 1, value_to_string, 1);
                fprintf(stderr, "[file: %s, line: %d]: </BST>\n", __FILE__, __LINE__);
                fflush(stderr);
                ret = TEST_FAIL;
            }
            else if (p_pred != NULL && p_pred_check == NULL)
            {
                char *key_str = key_to_string(pkey);
                char *pred_str = key_to_string(p_pred);
                fprintf(stderr, "[file: %s, line: %d] ERROR: Input key: '%s' -> Expected no predecessor, got '%s'.\n", __FILE__, __LINE__, key_str, pred_str);
                free(pred_str);
                free(key_str);
                fprintf(stderr, "[file: %s, line: %d]: <BST>\n", __FILE__, __LINE__);
                upo_bst_dump(bst, stderr, key_to_string, 1, value_to_string, 1);
                fprintf(stderr, "[file: %s, line: %d]: </BST>\n", __FILE__, __LINE__);
                fflush(stderr);
                ret = TEST_FAIL;
            }
            else if (p_pred != p_pred_check && memcmp(p_pred, p_pred_check, key_sz))
            {
                char *key_str = key_to_string(pkey);
                char *pred_str = key_to_string(p_pred);
                char *pred_check_str = key_to_string(p_pred_check);
                fprintf(stderr, "[file: %s, line: %d] ERROR: Input key: '%s' -> Expected predecessor '%s', got '%s'.\n", __FILE__, __LINE__, key_str, pred_check_str, pred_str);
                free(pred_check_str);
                free(pred_str);
                free(key_str);
                fprintf(stderr, "[file: %s, line: %d]: <BST>\n", __FILE__, __LINE__);
                upo_bst_dump(bst, stderr, key_to_string, 1, value_to_string, 1);
                fprintf(stderr, "[file: %s, line: %d]: </BST>\n", __FILE__, __LINE__);
                fflush(stderr);
                ret = TEST_FAIL;
            }

            free(pkey);
        }

        // Find the predecessor of each no-key

        // No keys
        for (i = 0; i < m && ret == TEST_OK; ++i)
        {
            void *pkey = NULL;
            const void *p_pred = NULL;
            const void *p_pred_check = NULL;

            pkey = malloc(key_sz);
            if (pkey == NULL)
            {
                perror("[ERROR] Unable to allocate memory for key");
                abort();
            }

            memcpy(pkey, pcnk + i*key_sz, key_sz);

            p_pred = upo_bst_predecessor(bst, pkey);

            p_pred_check = upo_bst_check(bst, pkey);

            if (p_pred == NULL && p_pred_check != NULL)
            {
                char *key_str = key_to_string(pkey);
                char *pred_check_str = key_to_string(p_pred_check);
                fprintf(stderr, "[file: %s, line: %d] ERROR: Input key: '%s' -> Expected predecessor '%s', got none.\n", __FILE__, __LINE__, key_str, pred_check_str);
                free(pred_check_str);
                free(key_str);
                fprintf(stderr, "[file: %s, line: %d]: <BST>\n", __FILE__, __LINE__);
                upo_bst_dump(bst, stderr, key_to_string, 1, value_to_string, 1);
                fprintf(stderr, "[file: %s, line: %d]: </BST>\n", __FILE__, __LINE__);
                fflush(stderr);
                ret = TEST_FAIL;
            }
            else if (p_pred != NULL && p_pred_check == NULL)
            {
                char *key_str = key_to_string(pkey);
                char *pred_str = key_to_string(p_pred);
                fprintf(stderr, "[file: %s, line: %d] ERROR: Input key: '%s' -> Expected no predecessor, got '%s'.\n", __FILE__, __LINE__, key_str, pred_str);
                free(pred_str);
                free(key_str);
                fprintf(stderr, "[file: %s, line: %d]: <BST>\n", __FILE__, __LINE__);
                upo_bst_dump(bst, stderr, key_to_string, 1, value_to_string, 1);
                fprintf(stderr, "[file: %s, line: %d]: </BST>\n", __FILE__, __LINE__);
                fflush(stderr);
                ret = TEST_FAIL;
            }
            else if (p_pred != p_pred_check && memcmp(p_pred, p_pred_check, key_sz))
            {
                char *key_str = key_to_string(pkey);
                char *pred_str = key_to_string(p_pred);
                char *pred_check_str = key_to_string(p_pred_check);
                fprintf(stderr, "[file: %s, line: %d] ERROR: Input key: '%s' -> Expected predecessor '%s', got '%s'.\n", __FILE__, __LINE__, key_str, pred_check_str, pred_str);
                free(pred_check_str);
                free(pred_str);
                free(key_str);
                fprintf(stderr, "[file: %s, line: %d]: <BST>\n", __FILE__, __LINE__);
                upo_bst_dump(bst, stderr, key_to_string, 1, value_to_string, 1);
                fprintf(stderr, "[file: %s, line: %d]: </BST>\n", __FILE__, __LINE__);
                fflush(stderr);
                ret = TEST_FAIL;
            }

            free(pkey);
        }
    }
    else
    {
        // Empty BST

        int dummy_key = 0;
        const void *p_pred = NULL;

        p_pred = upo_bst_predecessor(bst, &dummy_key);

        if (p_pred != NULL)
        {
            char *pred_str = key_to_string(p_pred);
            fprintf(stderr, "[file: %s, line: %d] ERROR: Empty BST -> Expected no predecessor, got '%s'.\n", __FILE__, __LINE__, pred_str);
            free(pred_str);
            ret = TEST_FAIL;
        }
    }

    /* Destroy */
 
    upo_bst_destroy(bst, 0);

    return ret;
}
