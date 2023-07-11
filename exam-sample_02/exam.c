/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */


/******************************************************************************/
/*** NOME:                                                                  ***/
/*** COGNOME:                                                               ***/
/*** MATRICOLA:                                                             ***/
/******************************************************************************/


#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <upo/bst.h>
#include <upo/hashtable.h>


/**** BEGIN of EXERCISE #1 ****/

size_t upo_bst_subtree_count_even(const upo_bst_t bst, const void *key)
{
    if(key == NULL) {
        fprintf(stderr, "Key is null");
        return 0;
    }
    if(bst == NULL || upo_bst_is_empty(bst)) {
        fprintf(stderr, "BST is empty or null");
        return 0;
    }
    size_t height = 0;
    const upo_bst_node_t *node = upo_bst_find_impl(bst->root, key, bst->key_cmp, &height);
    return upo_bst_subtree_count_even_impl(node, height);
}

const upo_bst_node_t* upo_bst_find_impl(const upo_bst_node_t *node, const void *key, upo_bst_comparator_t cmp, size_t *height) {
    if(node == NULL) return 0;
    if(cmp(key, node->key) < 0){
        *height+=1;
        return upo_bst_find_impl(node->left, key, cmp, height);
    } 
    else if(cmp(key, node->key) > 0) {
        *height+=1;
        return upo_bst_find_impl(node->right, key, cmp, height);
    }
    else return node;
}

size_t upo_bst_subtree_count_even_impl(const upo_bst_node_t *node, size_t height) {
    if(node == NULL) return 0;
    size_t count = 0;
    if(height % 2 == 0) count = 1;
    return count + upo_bst_subtree_count_even_impl(node->left, height+1) + upo_bst_subtree_count_even_impl(node->right, height+1);
}

/**** END of EXERCISE #1 ****/


/**** BEGIN of EXERCISE #2 ****/

void upo_ht_sepchain_odelete(upo_ht_sepchain_t ht, const void *key, int destroy_data)
{
    if(ht == NULL || upo_ht_sepchain_is_empty(ht)) {
        fprintf(stderr, "Hashtable is empty or null");
        return;
    }

    size_t hash = ht->key_hash(key, ht->capacity);
    upo_ht_sepchain_list_node_t *node = ht->slots[hash].head;
    upo_ht_sepchain_list_node_t *prev = NULL;

    while(node != NULL && ht->key_cmp(key, node->key) > 0) {
        prev = node;
        node = node->next;
    }   
    if(node != NULL && ht->key_cmp(key, node->key) == 0) {
        if(prev == NULL) {
            ht->slots[hash].head = node->next;
        }
        else {
            prev->next = node->next;
        }
        if(destroy_data) {
            free(node->value);
            free(node->key);
        }
        free(node);
        ht->size -= 1;
    }
}

/**** END of EXERCISE #2 ****/
