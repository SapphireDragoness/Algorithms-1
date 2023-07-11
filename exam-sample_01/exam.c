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
#include <upo/sort.h>


/**** BEGIN of EXERCISE #1 ****/

const void* upo_bst_predecessor(const upo_bst_t bst, const void *key)
{
    if(key == NULL) {
        fprintf(stderr, "Key is null");
        return NULL;
    }
    if(upo_bst_is_empty(bst)) {
        fprintf(stderr, "BST is empty");
        return NULL;
    }
    return upo_bst_predecessor_impl(bst->root, key, bst->key_cmp);
}

const void* upo_bst_predecessor_impl(upo_bst_node_t *node, const void *key, upo_bst_comparator_t cmp) {
    if(node == NULL) return NULL;
    if(cmp(key, node->key) <= 0) return upo_bst_predecessor_impl(node->left, key, cmp);
    const void *pred_key = upo_bst_predecessor_impl(node->right, key, cmp);
    return (pred_key != NULL) ? pred_key : node->key;
}

/**** END of EXERCISE #1 ****/


/**** BEGIN of EXERCISE #2 ****/

void upo_bidi_bubble_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    if(base == NULL) {
        fprintf(stderr, "The base of the array can't be null.");
        return;
    }

    unsigned char *pc = base;
    int swapped = 1;

    for(size_t i = 0; i < n && swapped; i++) {
        swapped = 0;
        for(size_t j = 0; j < (n-1); j++) {
            if(cmp(pc+j*size, pc+(j+1)*size) > 0) {
                upo_swap(pc+(j+1)*size, pc+j*size, size);
                swapped = 1;
            }
        }
        if(swapped) {
            swapped = 0;
            for(size_t j = n-2; j > 0; j--) {
                if(cmp(pc+j*size, pc+(j-1)*size) < 0) {
                    upo_swap(pc+(j-1)*size, pc+j*size, size);
                    swapped = 1;
                }
            }
        }
    }
}

void upo_swap(void *pv1, void *pv2, size_t size) {
    unsigned char *pc1 = pv1;
    unsigned char *pc2 = pv2;

    while(size-- > 0) {
        unsigned char tmp = *pc1;
        *pc1 = *pc2;
        *pc2 = tmp;
        pc1++;
        pc2++;
    }
}

/**** END of EXERCISE #2 ****/
