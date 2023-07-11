/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file upo/hashtable.h
 *
 * \brief The Hash Table (HT) abstract data type.
 *
 * Hash Tables are containers composed of unique keys (containing at most one of
 * each key value) that associates values of another type with the keys.
 *
 * \author Marco Guazzone (marco.guazzone@uniupo.it)
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

#ifndef UPO_HASHTABLE_H
#define UPO_HASHTABLE_H


#include <stddef.h>


/*** BEGIN of COMMON TYPES ***/


/** \brief The type for hash functions.
 *
 * Declares the type for key hash functions that are used to map key
 * space into the index space to use for indexing the hash table.
 * A hash function takes two parameters:
 * - The first parameter is a pointer to the key to hash.
 * - The second parameter is the capacity of the hash table.
 * A hash function returns a nonnegative number which represents a position
 * (index) in the hash table.
 */
typedef size_t (*upo_ht_hasher_t)(const void*, size_t);

/**
 * \brief The type for key comparison functions.
 *
 * Declares the type for key comparison functions that are used to compare keys
 * stored in the hash table.
 * A comparison function takes two parameters:
 * - The first parameter is a pointer to the first key to compare.
 * - The second parameter is a pointer to the second key to compare.
 * A comparison function returns a number less than, equal to, or greater than
 * zero if the first key (first argument) is less than, equal to, or greater
 * than the second key (second argument), respectively.
 */
typedef int (*upo_ht_comparator_t)(const void*, const void*);


/*** END of COMMON TYPES ***/


/*** BEGIN of HASH TABLE with SEPARATE CHAINING ***/


/** \brief Default capacity of hash tables with separate chaining. */
#define UPO_HT_SEPCHAIN_DEFAULT_CAPACITY 997U


/** \brief Type for nodes of the list of collisions. */
struct upo_ht_sepchain_list_node_s
{
    void *key; /**< Pointer to the user-provided key. */
    void *value; /**< Pointer to the value associated to the key. */
    struct upo_ht_sepchain_list_node_s *next; /**< Pointer to the next node in the list. */
};
/** \brief Alias for the type for nodes of the list of collisions. */
typedef struct upo_ht_sepchain_list_node_s upo_ht_sepchain_list_node_t;

/** \brief Type for slots of hash tables with separate chaining. */
struct upo_ht_sepchain_slot_s
{
    upo_ht_sepchain_list_node_t *head; /**< Pointer to the head of the list of collisions. */
};
/** \brief Alias for the type for slots of hash tables with separate chaining. */
typedef struct upo_ht_sepchain_slot_s upo_ht_sepchain_slot_t;

/** \brief Type for hash tables with separate chaining. */
struct upo_ht_sepchain_s
{
    upo_ht_sepchain_slot_t *slots; /**< The hash table as array of slots. */
    size_t capacity; /**< The capacity of the hash table. */
    size_t size; /**< The number of elements stored in the hash table. */
    upo_ht_hasher_t key_hash; /**< The key hash function. */
    upo_ht_comparator_t key_cmp; /**< The key comparison function. */
};

/** \brief Type for hash tables with separate chaining. */
typedef struct upo_ht_sepchain_s* upo_ht_sepchain_t;


/**
 * \brief Creates a new empty hash table.
 *
 * \param m The initial capacity of the hash table.
 * \param key_hash A pointer to the function used to hash keys.
 * \param key_cmp A pointer to the function used to compare keys.
 * \return An empty hash table.
 *
 * Worst-case complexity: linear in the capacity `m` of the hash table, `O(m)`.
 */
upo_ht_sepchain_t upo_ht_sepchain_create(size_t m, upo_ht_hasher_t key_hash, upo_ht_comparator_t key_cmp);

/**
 * \brief Destroys the given hash table.
 *
 * \param ht The hash table to destroy.
 * \param destroy_data Tells whether the previously allocated memory for data
 *  stored in the hash table must be freed (value `1`) or not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the capacity `m` of the hash table, `O(m)`.
 */
void upo_ht_sepchain_destroy(upo_ht_sepchain_t ht, int destroy_data);

/**
 * \brief Removes all key-value pairs from the given hash table.
 *
 * \param ht The hash table to clear.
 * \param destroy_data Tells whether the previously allocated memory for data
 *  stored in the hash table must be freed (value `1`) or not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the capacity `m` of the hash table, `O(m)`.
 */
void upo_ht_sepchain_clear(upo_ht_sepchain_t ht, int destroy_data);

/**
 * \brief Tells if the given hash table is empty.
 *
 * \param ht The hash table.
 * \return `1` if the hash table is empty or `0` otherwise.
 *
 * A hash table is empty if it doesn't contain any node.
 *
 * Worst-case complexity: constant, `O(1)`.
 */
int upo_ht_sepchain_is_empty(const upo_ht_sepchain_t ht);

/**
 * \brief Returns the capacity of the hash table.
 *
 * \param ht The hash table.
 * \return The total number of slots of the hash tables.
 *
 * Worst-case complexity: constant, `O(1)`.
 */
size_t upo_ht_sepchain_capacity(const upo_ht_sepchain_t ht);

/**
 * \brief Returns the size of the hash table.
 *
 * \param ht The hash table.
 * \return The number of keys stored in the hash tables.
 *
 * Worst-case complexity: linear in the capacity `m` of the hash table, `O(m)`.
 */
size_t upo_ht_sepchain_size(const upo_ht_sepchain_t ht);

/**
 * \brief Returns the load factor of the hash table.
 *
 * \param ht The hash table.
 * \return The load factor which is defined as the ratio between the number of
 *  stored keys (i.e., the keys) and the number of slots (i.e., the capacity).
 *
 * Worst-case complexity: constant, `O(1)`.
 */
double upo_ht_sepchain_load_factor(const upo_ht_sepchain_t ht);

/**
 * \brief Returns the key comparator function.
 *
 * \param ht The hash table.
 * \return The key comparator function.
 */
upo_ht_comparator_t upo_ht_sepchain_get_comparator(const upo_ht_sepchain_t ht);

/**
 * \brief Returns the key hasher function.
 *
 * \param ht The hash table.
 * \return The key hasher function.
 */
upo_ht_hasher_t upo_ht_sepchain_get_hasher(const upo_ht_sepchain_t ht);

/**
 * \brief Removes the value identified by the provided key in the given
 *  hash table.
 *
 * \param ht The hash table.
 * \param key The key.
 * \param destroy_data Tells whether the previously allocated memory for data,
 *  that is to be removed, must be freed (value `1`) or not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 *
 * Worst-case complexity: linear in the number `n` of elements, `O(n)`.
 */
void upo_ht_sepchain_odelete(upo_ht_sepchain_t ht, const void *key, int destroy_data);


/*** END of HASH TABLE with SEPARATE CHAINING ***/


/*** BEGIN of HASH FUNCTIONS ***/


/**
 * \brief Hash function for integers that uses the division method.
 *
 * \param x The integer to be hashed.
 * \param m The number of possible hash values.
 * \return The hash value which is an integer number in \f$\{0,\ldots,m-1\}\f$.
 *
 * The division method is defined as:
 * \f[
 *   h(x) = x \bmod m
 * \f]
 * where:
 * - \f$y \bmod z\f$ means the remainder of the division \f$y / z\f$.
 * .
 */
size_t upo_ht_hash_int_div(const void *x, size_t m);

/**
 * \brief Hash function for integers that uses the multiplication method.
 *
 * \param x The integer to be hashed.
 * \param a A multiplicative constant in the range of (0,1).
 * \param m The number of possible hash values.
 * \return The hash value which is an integer number in \f$\{0,\ldots,m-1\}\f$.
 *
 * The multiplication method is defined as:
 * \f[
 *   h(x) = m \lfloor a x \bmod 1 \rfloor
 * \f]
 * where:
 * - \f$\lfloor y \rfloor\f$ means the floor of \f$y\f$, that is the greatest
 *   integer less than or equal to \f$y\f$.
 * - \f$y \bmod z\f$ means the remainder of the division \f$y / z\f$.
 * - \f$y \bmod 1\f$ is the fractional part of \f$y\f$, that is
 *   the result of \f$y - \lfloor y \rfloor\f$.
 * .
 */
size_t upo_ht_hash_int_mult(const void *x, double a, size_t m);

/**
 * \brief Hash function for integers that uses the multiplication method and
 *  the value of the multiplicative constant as proposed by Knuth.
 *
 * \param x The integer to be hashed.
 * \param m The number of possible hash values.
 * \return The hash value which is an integer number in \f$\{0,\ldots,m-1\}\f$.
 */
size_t upo_ht_hash_int_mult_knuth(const void *x, size_t m);

/**
 * \brief Hash function for strings.
 *
 * \param s The string to be hashed.
 * \param h0 The initial value for the hash value that is usually chosen
 *  randomly from a universal family mapping integer domain
 *  \f$\{0,\ldots,p-1\} \mapsto \{0,\ldots,m-1\}\f$.
 * \param a A multiplicative factor such that \f$a \in \{0,\ldots,p-1\}\f$ which
 *  is usually uniformly random.
 * \param m The number of possible hash values.
 * \return The hash value which is an integer number in \f$\{0,\ldots,m-1\}\f$.
 *
 * The implemented hash function is the following:
 * \f[
 *     h(k) = h_0 \left( \big(\sum_{i=0}^{\ell-1} k_i\cdot a^i \big) \bmod m \right), 
 * \f]
 * where:
 * - \f$k=(k_0,\ldots,k_{\ell-1})\f$ is an array of characters of size \$\ell\$
 */
size_t upo_ht_hash_str(const void *s, size_t h0, size_t a, size_t m);

/**
 * \brief The Bernstein's hash function `djb2`.
 *
 * This hash function was first reported by Daniel J. Bernstein in comp.lang.c on 1991.
 *
 * See:
 * - https://groups.google.com/forum/#!msg/comp.lang.c/lSKWXiuNOAk/zstZ3SRhCjgJ
 * - http://www.cse.yorku.ca/~oz/hash.html
 * .
 */
size_t upo_ht_hash_str_djb2(const void *s, size_t m);

/**
 * \brief The Bernstein's hash function `djb2a`.
 *
 * This hash function is an alternative to the 'djb2' hash function that was
 * first reported by Daniel J. Bernstein in comp.lang.c on 1991.
 * Instead of using the sum operator it uses the XOR operator.
 *
 * See:
 * - https://groups.google.com/forum/#!msg/comp.lang.c/lSKWXiuNOAk/zstZ3SRhCjgJ
 * - http://www.cse.yorku.ca/~oz/hash.html
 * .
 */
size_t upo_ht_hash_str_djb2a(const void *s, size_t m);

/**
 * \brief The Java's hash function `hashCode`.
 *
 * See:
 * - https://docs.oracle.com/javase/8/docs/api/java/lang/String.html#hashCode--
 * .
 */
size_t upo_ht_hash_str_java(const void *s, size_t m);

/**
 * \brief The Kernighan and Ritchie's hash function proposed in the second
 *  edition of their C book.
 */
size_t upo_ht_hash_str_kr2e(const void *s, size_t m);

/**
 * \brief The SGI STL's hash function `hash_fun`.
 *
 */
size_t upo_ht_hash_str_sgistl(const void *s, size_t m);


/*** END of HASH FUNCTIONS ***/


#endif /* UPO_HASHTABLE_H */
