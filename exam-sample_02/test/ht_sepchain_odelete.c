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
#include <upo/hashtable.h>
#include <upo/test.h>


#define TEST_OK 1
#define TEST_FAIL 0


static int test_ht1();
static int test_ht2();
static int test_ht3();
static int test_ht4();
static int test_ht5();
static int test_ht6();
static int test_empty_ht();
static int test_int_ht(int *keys, int *values, size_t n, int *no_keys, size_t m);
static int test_str_ht(char **keys, int *values, size_t n, char **no_keys, size_t m);
static int test_ht(void *keys, size_t key_sz, void *values, size_t value_sz, size_t n, void *no_keys, size_t m, upo_ht_hasher_t key_hasher, upo_ht_comparator_t key_cmp, char* (*key_to_string)(const void*), char* (*value_to_string)(const void*));
extern upo_ht_sepchain_list_node_t* upo_ht_sepchain_check_order(const upo_ht_sepchain_t ht);
extern int upo_ht_sepchain_contains(const upo_ht_sepchain_t ht, const void *key);
extern void upo_ht_sepchain_dump(const upo_ht_sepchain_t, FILE *, char* (*)(const void*), int, char* (*)(const void*), int);
extern void* upo_ht_sepchain_put(upo_ht_sepchain_t ht, void *key, void *value);


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
                ret = test_ht1();
                break;
            case 2:
                ret = test_ht2();
                break;
            case 3:
                ret = test_ht3();
                break;
            case 4:
                ret = test_ht4();
                break;
            case 5:
                ret = test_ht5();
                break;
            case 6:
                ret = test_ht6();
                break;
            default:
                fprintf(stderr, "ERROR: Unexpected test case number");
                abort();
        }
        printf("Test HT #%zu => %s\n", i, (ret == TEST_OK) ? "[OK]" : "[FAIL]");
    }

    ret = test_empty_ht();
    printf("Test Empty HT => %s\n", (ret == TEST_OK) ? "[OK]" : "[FAIL]");

    return 0;
}


int test_ht1()
{
    int keys[] = {0,1,2,3,4,5,6,7,8,9,1000,2000,3000,4000,5000,6000,7000,8000,9000};
    int values[] = {0,1,2,3,4,5,6,7,8,9,1000,2000,3000,4000,5000,6000,7000,8000,9000};
    int no_keys[] = {10,11,12,13,14,15,16,19,1010,2010,3010,4010,5010};
    size_t n = sizeof keys/sizeof keys[0];
    size_t m = sizeof no_keys/sizeof no_keys[0];

    assert( n == (sizeof keys/sizeof keys[0]) );
    assert( n == (sizeof values/sizeof values[0]) );
    assert( m == (sizeof no_keys/sizeof no_keys[0]) );

    return test_int_ht(keys, values, n, no_keys, m);
}

int test_ht2()
{
    int keys[] = {0,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900};
    int values[] = {0,1,2,3,4,5,6,7,8,9,1000,2000,3000,4000,5000,6000,7000,8000,9000};
    int no_keys[] = {1,11,21,31,41,51,61,71,81,91,101,201,301,401,501,601,701,801,901,1001,1101,1201,1301,1401,1501};
    size_t n = sizeof keys/sizeof keys[0];
    size_t m = sizeof no_keys/sizeof no_keys[0];

    assert( n == (sizeof keys/sizeof keys[0]) );
    assert( n == (sizeof values/sizeof values[0]) );
    assert( m == (sizeof no_keys/sizeof no_keys[0]) );

    return test_int_ht(keys, values, n, no_keys, m);
}

int test_ht3()
{
    int keys[] = {0,1,2,3,4,10,11,12,13,14,1000,2000,3000,4000,5000,6000,7000,8000,9000};
    int values[] = {0,1,2,3,4,5,6,7,8,9,1000,2000,3000,4000,5000,6000,7000,8000,9000};
    int no_keys[] = {5,6,7,8,9,15,16,17,18,19,1500,1600,1700,1800,1900};
    size_t n = sizeof keys/sizeof keys[0];
    size_t m = sizeof no_keys/sizeof no_keys[0];

    assert( n == (sizeof keys/sizeof keys[0]) );
    assert( n == (sizeof values/sizeof values[0]) );
    assert( m == (sizeof no_keys/sizeof no_keys[0]) );

    return test_int_ht(keys, values, n, no_keys, m);
}

int test_ht4()
{
    char *keys[] = {"AA","AB","AQ","Aa","Aq","Ba","Ca","Da","Ea","Fa","AAA", "Ab"};
    int values[] = {0,1,2,3,4,5,6,7,8,9,10,11};
    char *no_keys[] = {"xAA","xAB","xAQ","xAa","xAq","xBa","xCa","xDa","xEa","xFa","xAAA", "xAb", "yAA", "yAB"};
    size_t n = sizeof keys/sizeof keys[0];
    size_t m = sizeof no_keys/sizeof no_keys[0];

    assert( n == (sizeof keys/sizeof keys[0]) );
    assert( n == (sizeof values/sizeof values[0]) );
    assert( m == (sizeof no_keys/sizeof no_keys[0]) );

    return test_str_ht(keys, values, n, no_keys, m);
}

int test_ht5()
{
    char *keys[] = {"aaa","aba","aca","ada","aea","afa","aga","aha","aia","aja"};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    char *no_keys[] = {"a1a","a2a","a3a","a4a","a5a","a6a","a7a","a9a","a9a","a10a"};
    size_t n = sizeof keys/sizeof keys[0];
    size_t m = sizeof no_keys/sizeof no_keys[0];

    assert( n == (sizeof keys/sizeof keys[0]) );
    assert( n == (sizeof values/sizeof values[0]) );
    assert( m == (sizeof no_keys/sizeof no_keys[0]) );

    return test_str_ht(keys, values, n, no_keys, m);
}

int test_ht6()
{
    char *keys[] = {"aaa","aab","aac","aad","aba","abb","abc","abd","abe","abf"};
    int values[] = {0,1,2,3,4,5,6,7,8,9};
    char *no_keys[] = {"aax","abx","acx","adx","aex","afx"};
    size_t n = sizeof keys/sizeof keys[0];
    size_t m = sizeof no_keys/sizeof no_keys[0];

    assert( n == (sizeof keys/sizeof keys[0]) );
    assert( n == (sizeof values/sizeof values[0]) );
    assert( m == (sizeof no_keys/sizeof no_keys[0]) );

    return test_str_ht(keys, values, n, no_keys, m);
}

int test_empty_ht()
{
    int dummy1 = 0;
    int dummy2 = 1;

    return test_int_ht(&dummy1, &dummy1, 0, &dummy2, 0);
}

int test_int_ht(int *keys, int *values, size_t n, int *no_keys, size_t m)
{
    assert( keys );
    assert( values );
    assert( no_keys );

    return test_ht(keys, sizeof keys[0], values, sizeof values[0], n, no_keys, m, upo_ht_hash_int_div, upo_test_int_cmp, upo_test_int_to_string, upo_test_int_to_string);
}

int test_str_ht(char **keys, int *values, size_t n, char **no_keys, size_t m)
{
    assert( keys );
    assert( values );
    assert( no_keys );

    return test_ht(keys, sizeof keys[0], values, sizeof values[0], n, no_keys, m, upo_ht_hash_str_kr2e, upo_test_str_cmp, upo_test_str_to_string, upo_test_int_to_string);
}

int test_ht(void *keys, size_t key_sz, void *values, size_t value_sz, size_t n, void *no_keys, size_t m, upo_ht_hasher_t key_hasher, upo_ht_comparator_t key_cmp, char* (*key_to_string)(const void*), char* (*value_to_string)(const void*))
{
    upo_ht_sepchain_t ht = NULL;
    size_t base_cap = 3;
    size_t caps[4];
    size_t nc;
    unsigned char *pck = keys;
    unsigned char *pcv = values;
    unsigned char *pcnk = no_keys;
    int ret = TEST_OK;

/*
    caps[0] = 2*n+UPO_HT_SEPCHAIN_DEFAULT_CAPACITY;
    caps[1] = n*UPO_HT_SEPCHAIN_DEFAULT_CAPACITY;
    caps[2] = UPO_HT_SEPCHAIN_DEFAULT_CAPACITY;
*/
    caps[0] = 3*n+base_cap;
    caps[1] = 2*n+base_cap;
    caps[2] = n*base_cap;
    caps[3] = base_cap;
    nc = sizeof caps/sizeof caps[0];

    for (size_t k = 0; k < nc && ret == TEST_OK; ++k)
    {
        ht = upo_ht_sepchain_create(caps[k], key_hasher, key_cmp);

        assert( ht != NULL );

        if (n > 0)
        {
            // Non-empty HT

            // Populate the HT
            for (size_t i = 0; i < n; ++i)
            {
                upo_ht_sepchain_put(ht, pck + i*key_sz, pcv + i*value_sz);
            }

            // Remove from HT
            for (size_t i = 0; i < n && ret == TEST_OK; ++i)
            {
                size_t old_size = 0;
                size_t new_size = 0;
                int found = 0;

                void *key = NULL;

                key = malloc(key_sz);
                if (key == NULL)
                {
                    perror("Unable to allocate memory for key");
                    abort();
                }

                memcpy(key, pck + i*key_sz, key_sz);

                old_size = upo_ht_sepchain_size(ht);

                upo_ht_sepchain_odelete(ht, key, 0);

                new_size = upo_ht_sepchain_size(ht);

                found = upo_ht_sepchain_contains(ht, key);

                if (found == 1)
                {
                    char *key_str = key_to_string(key);
                    fprintf(stderr, "[file: %s, line: %d] ERROR: HT Alternative #: %lu, Key: '%s' -> Found key after its deletion.\n", __FILE__, __LINE__, k, key_str);
                    fprintf(stderr, "[file: %s, line: %d]: <HT>\n", __FILE__, __LINE__);
                    upo_ht_sepchain_dump(ht, stderr, key_to_string, 1, value_to_string, 1);
                    fprintf(stderr, "[file: %s, line: %d]: </HT>\n", __FILE__, __LINE__);
                    fflush(stderr);
                    free(key_str);
                    ret = TEST_FAIL;
                }
                else if (new_size != (old_size-1))
                {
                    char *key_str = key_to_string(key);
                    fprintf(stderr, "[file: %s, line: %d] ERROR: HT Alternative #: %lu, Key: '%s' -> Expected size: %lu, got %lu.\n", __FILE__, __LINE__, k, key_str, (old_size-1), new_size);
                    fprintf(stderr, "[file: %s, line: %d]: <HT>\n", __FILE__, __LINE__);
                    upo_ht_sepchain_dump(ht, stderr, key_to_string, 1, value_to_string, 1);
                    fprintf(stderr, "[file: %s, line: %d]: </HT>\n", __FILE__, __LINE__);
                    fflush(stderr);
                    free(key_str);
                    ret = TEST_FAIL;
                }

                free(key);

                // Check order of stored values 

                upo_ht_sepchain_list_node_t *node = upo_ht_sepchain_check_order(ht);
                if (node != NULL)
                {
                    char *key_str1 = key_to_string(node->key);
                    char *key_str2 = key_to_string(node->next->key);
                    fprintf(stderr, "[file: %s, line: %d] ERROR: HT Alternative #: %zu, Keys: '%s' and '%s' are out of order.\n", __FILE__, __LINE__, k, key_str1, key_str2);
                    free(key_str1);
                    free(key_str2);
                    fprintf(stderr, "[file: %s, line: %d]: <HT>\n", __FILE__, __LINE__);
                    upo_ht_sepchain_dump(ht, stderr, key_to_string, 1, value_to_string, 1);
                    fprintf(stderr, "[file: %s, line: %d]: </HT>\n", __FILE__, __LINE__);
                    fflush(stderr);
                    ret = TEST_FAIL;
                }
            }

            upo_ht_sepchain_clear(ht, 0);

            // Now for each key to be removed, fill the HT with all keys, remove the given key and then check that the other keys are still present in the HT

            for (size_t j = 0; j < n && ret == TEST_OK; ++j)
            {
                // Populate the HT
                for (size_t i = 0; i < n && ret == TEST_OK; ++i)
                {
                    upo_ht_sepchain_put(ht, pck + i*key_sz, pcv + i*value_sz);
                }

                // Remove from the HT

                void *key = NULL;

                key = malloc(key_sz);
                if (key == NULL)
                {
                    perror("Unable to allocate memory for key");
                    abort();
                }

                memcpy(key, pck + j*key_sz, key_sz);

                size_t old_size = 0;
                size_t new_size = 0;
                int found = 0;

                old_size = upo_ht_sepchain_size(ht);

                upo_ht_sepchain_odelete(ht, key, 0);

                new_size = upo_ht_sepchain_size(ht);

                found = upo_ht_sepchain_contains(ht, key);

                if (found == 1)
                {
                    char *key_str = key_to_string(key);
                    fprintf(stderr, "[file: %s, line: %d] ERROR: HT Alternative #: %lu, Key: '%s' -> Found key after its deletion.\n", __FILE__, __LINE__, k, key_str);
                    fprintf(stderr, "[file: %s, line: %d]: <HT>\n", __FILE__, __LINE__);
                    upo_ht_sepchain_dump(ht, stderr, key_to_string, 1, value_to_string, 1);
                    fprintf(stderr, "[file: %s, line: %d]: </HT>\n", __FILE__, __LINE__);
                    fflush(stderr);
                    free(key_str);
                    ret = TEST_FAIL;
                }
                else if (new_size != (old_size-1))
                {
                    char *key_str = key_to_string(key);
                    fprintf(stderr, "[file: %s, line: %d] ERROR: HT Alternative #: %lu, Key: '%s' -> Expected size: %lu, got %lu.\n", __FILE__, __LINE__, k, key_str, (old_size-1), new_size);
                    fprintf(stderr, "[file: %s, line: %d]: <HT>\n", __FILE__, __LINE__);
                    upo_ht_sepchain_dump(ht, stderr, key_to_string, 1, value_to_string, 1);
                    fprintf(stderr, "[file: %s, line: %d]: </HT>\n", __FILE__, __LINE__);
                    fflush(stderr);
                    free(key_str);
                    ret = TEST_FAIL;
                }

                for (size_t i = 0; i < n && ret == TEST_OK; ++i)
                {
                    if (i == j)
                    {
                        // Skip the remove key
                        continue;
                    }

                    found = upo_ht_sepchain_contains(ht, pck + i*key_sz);

                    if (found == 0)
                    {
                        ret = TEST_FAIL;
                        char *key_str = key_to_string(key);
                        char *key2_str = key_to_string(pck + i*key_sz);
                        fprintf(stderr, "[file: %s, line: %d] ERROR: HT Alternative #: %lu, Key: '%s' -> Key '%s' not found after the deletion of another key.\n", __FILE__, __LINE__, k, key_str, key2_str);
                        fprintf(stderr, "[file: %s, line: %d]: <HT>\n", __FILE__, __LINE__);
                        upo_ht_sepchain_dump(ht, stderr, key_to_string, 1, value_to_string, 1);
                        fprintf(stderr, "[file: %s, line: %d]: </HT>\n", __FILE__, __LINE__);
                        fflush(stderr);
                        free(key_str);
                        free(key2_str);
                        ret = TEST_FAIL;
                    }
                }

                /* Clean-up */
                free(key);

                // Clear the HT
                upo_ht_sepchain_clear(ht, 0);
            }

            // Now populate again the HT and try to remove a key not stored in it.

            // Populate the HT
            for (size_t i = 0; i < n; ++i)
            {
                upo_ht_sepchain_put(ht, pck + i*key_sz, pcv + i*value_sz);
            }

            // Remove from HT
            for (size_t i = 0; i < m && ret == TEST_OK; ++i)
            {
                size_t old_size = 0;
                size_t new_size = 0;
                int found = 0;

                // Use a different pointer for key to catch comparison-by-pointers issues

                void *key = NULL;

                key = malloc(key_sz);
                if (key == NULL)
                {
                    perror("Unable to allocate memory for key");
                    abort();
                }

                memcpy(key, pcnk + i*key_sz, key_sz);

                old_size = upo_ht_sepchain_size(ht);

                upo_ht_sepchain_odelete(ht, key, 0);

                new_size = upo_ht_sepchain_size(ht);

                found = upo_ht_sepchain_contains(ht, key);

                if (found == 1)
                {
                    char *key_str = key_to_string(key);
                    fprintf(stderr, "[file: %s, line: %d] ERROR: HT Alternative #: %lu, Key: '%s' -> Found key not belonging to the HT.\n", __FILE__, __LINE__, k, key_str);
                    fprintf(stderr, "[file: %s, line: %d]: <HT>\n", __FILE__, __LINE__);
                    upo_ht_sepchain_dump(ht, stderr, key_to_string, 1, value_to_string, 1);
                    fprintf(stderr, "[file: %s, line: %d]: </HT>\n", __FILE__, __LINE__);
                    fflush(stderr);
                    free(key_str);
                    ret = TEST_FAIL;
                }
                else if (new_size != old_size)
                {
                    char *key_str = key_to_string(key);
                    fprintf(stderr, "[file: %s, line: %d] ERROR: HT Alternative #: %lu, Key: '%s' -> Expected size: %lu, got %lu.\n", __FILE__, __LINE__, k, key_str, old_size, new_size);
                    fprintf(stderr, "[file: %s, line: %d]: <HT>\n", __FILE__, __LINE__);
                    upo_ht_sepchain_dump(ht, stderr, key_to_string, 1, value_to_string, 1);
                    fprintf(stderr, "[file: %s, line: %d]: </HT>\n", __FILE__, __LINE__);
                    fflush(stderr);
                    free(key_str);
                    ret = TEST_FAIL;
                }

                free(key);

                // Check order of stored values 

                upo_ht_sepchain_list_node_t *node = upo_ht_sepchain_check_order(ht);
                if (node != NULL)
                {
                    char *key_str1 = key_to_string(node->key);
                    char *key_str2 = key_to_string(node->next->key);
                    fprintf(stderr, "[file: %s, line: %d] ERROR: HT Alternative #: %zu, Keys: '%s' and '%s' are out of order.\n", __FILE__, __LINE__, k, key_str1, key_str2);
                    free(key_str1);
                    free(key_str2);
                    fprintf(stderr, "[file: %s, line: %d]: <HT>\n", __FILE__, __LINE__);
                    upo_ht_sepchain_dump(ht, stderr, key_to_string, 1, value_to_string, 1);
                    fprintf(stderr, "[file: %s, line: %d]: </HT>\n", __FILE__, __LINE__);
                    fflush(stderr);
                    ret = TEST_FAIL;
                }
            }

            upo_ht_sepchain_clear(ht, 0);
        }
        else
        {
            // Empty HT: no test
        }

        upo_ht_sepchain_destroy(ht, 0);
    }

    return ret;
}
