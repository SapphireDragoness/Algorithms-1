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

#include "bst_private.h"
#include <stdio.h>
#include <stdlib.h>


/**** EXERCISE #1 - BEGIN of FUNDAMENTAL OPERATIONS ****/


upo_bst_t upo_bst_create(upo_bst_comparator_t key_cmp)
{
    upo_bst_t tree = malloc(sizeof(struct upo_bst_s));
    if (tree == NULL)
    {
        perror("Unable to create a binary search tree");
        abort();
    }

    tree->root = NULL;
    tree->key_cmp = key_cmp;

    return tree;
}

void upo_bst_destroy(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear(tree, destroy_data);
        free(tree);
    }
}

void upo_bst_clear_impl(upo_bst_node_t *node, int destroy_data)
{
    if (node != NULL)
    {
        upo_bst_clear_impl(node->left, destroy_data);
        upo_bst_clear_impl(node->right, destroy_data);

        if (destroy_data)
        {
            free(node->key);
            free(node->value);
        }

        free(node);
    }
}

void upo_bst_clear(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear_impl(tree->root, destroy_data);
        tree->root = NULL;
    }
}

upo_bst_node_t* upo_bst_node_create(void *key, void *value) {
    upo_bst_node_t *node = NULL;
    node = malloc(sizeof(struct upo_bst_node_s));
    if(node == NULL) {
        perror("Unable to create node.");
        abort();
    }
    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

upo_bst_node_t* upo_bst_put_impl(upo_bst_node_t *node, void *key, void *value, void *old_value, upo_bst_comparator_t key_cmp) {
    old_value = NULL;
    if(node == NULL) return upo_bst_node_create(key, value);
    else if(key_cmp(key, node->key) < 0) node->left = upo_bst_put_impl(node->left, key, value, old_value, key_cmp);
    else if(key_cmp(key, node->key) > 0) node->right = upo_bst_put_impl(node->right, key, value, old_value, key_cmp);
    else {
        old_value = node->value;
        node->value = value;
    }
    return node;
}

void* upo_bst_put(upo_bst_t tree, void *key, void *value)
{
    void *old_value = NULL;
    tree->root = upo_bst_put_impl(tree->root, key, value, old_value, tree->key_cmp);
    return old_value;
}

upo_bst_node_t* upo_bst_insert_impl(upo_bst_node_t *node, void *key, void *value, upo_bst_comparator_t key_cmp) {
    if(node == NULL) return upo_bst_node_create(key, value);
    else if(key_cmp(key, node->key) < 0) node->left = upo_bst_insert_impl(node->left, key, value, key_cmp);
    else if(key_cmp(key, node->key) > 0) node->right = upo_bst_insert_impl(node->right, key, value, key_cmp);
    return node;
}

void upo_bst_insert(upo_bst_t tree, void *key, void *value)
{
    tree->root = upo_bst_insert_impl(tree->root, key, value, tree->key_cmp);
}

upo_bst_node_t* upo_bst_get_impl(upo_bst_node_t *node, const void *key, upo_bst_comparator_t key_cmp) {
    if(node == NULL) return NULL;
    if(key_cmp(key, node->key) < 0) return upo_bst_get_impl(node->left, key, key_cmp);
    else if(key_cmp(key, node->key) > 0) return upo_bst_get_impl(node->right, key, key_cmp);
    else return node;
} 

void* upo_bst_get(const upo_bst_t tree, const void *key)
{
    upo_bst_node_t *node = upo_bst_get_impl(tree->root, key, tree->key_cmp);
    if(node != NULL) return node->value;
    return NULL;
}

int upo_bst_contains(const upo_bst_t tree, const void *key)
{
    return upo_bst_get_impl(tree->root, key, tree->key_cmp) != NULL ? 1 : 0;
}

upo_bst_node_t* upo_bst_delete_1C_impl(upo_bst_node_t *node, int destroy_data) {
    upo_bst_node_t *tmp = node;
    if(node->left != NULL) node = node->left;
    else node = node->right;
    if(destroy_data == 1) {
        free(tmp->key);
        free(tmp->value);
    } 
    free(tmp);
    return node;
}

upo_bst_node_t* upo_bst_delete_2C_impl(upo_bst_node_t *node, int destroy_data, upo_bst_comparator_t key_cmp) {
    upo_bst_node_t *max = upo_bst_max_impl(node->left);
    node->key = max->key;
    node->value = max->value;
    node->left = upo_bst_delete_impl(node->left, node->key, destroy_data, key_cmp);
    if(destroy_data == 1) {
        free(max->key);
        free(max->value);
    } 
    return node;
}

upo_bst_node_t* upo_bst_delete_impl(upo_bst_node_t *node, const void *key, int destroy_data, upo_bst_comparator_t key_cmp) {
    if(node == NULL) return NULL;
    if(key_cmp(key, node->key) < 0) node->left = upo_bst_delete_impl(node->left, key, destroy_data, key_cmp);
    else if(key_cmp(key, node->key) > 0) node->right = upo_bst_delete_impl(node->right, key, destroy_data, key_cmp);
    else if(node->left != NULL && node->right != NULL) node = upo_bst_delete_2C_impl(node, destroy_data, key_cmp);
    else node = upo_bst_delete_1C_impl(node, destroy_data);
    return node;
}

void upo_bst_delete(upo_bst_t tree, const void *key, int destroy_data)
{
    tree->root = upo_bst_delete_impl(tree->root, key, destroy_data, tree->key_cmp);
}

size_t upo_bst_size_impl(upo_bst_node_t *node) {
    if(node == NULL) return 0;
    return 1 + upo_bst_size_impl(node->left) + upo_bst_size_impl(node->right);
}

size_t upo_bst_size(const upo_bst_t tree)
{
    if(tree == NULL) return 0;
    return upo_bst_size_impl(tree->root);
}

int upo_bst_is_leaf_impl(upo_bst_node_t *node) {
    if(node->left == NULL && node->right == NULL) return 1;
    return 0;
}

size_t upo_bst_height_impl(upo_bst_node_t *node) {
    if(node == NULL || upo_bst_is_leaf_impl(node)) return 0;
    size_t left = upo_bst_height_impl(node->left);
    size_t right = upo_bst_height_impl(node->right);
    return 1 + (left > right ? left : right);
}

size_t upo_bst_height(const upo_bst_t tree)
{
    return upo_bst_height_impl(tree->root);
}

void upo_bst_traverse_in_order_impl(upo_bst_node_t *node, upo_bst_visitor_t visit, void *visit_context) {
    if(node != NULL) {
        upo_bst_traverse_in_order_impl(node->left, visit, visit_context);
        visit(node->key, node->value, visit_context);
        upo_bst_traverse_in_order_impl(node->right, visit, visit_context);
    }
}

void upo_bst_traverse_in_order(const upo_bst_t tree, upo_bst_visitor_t visit, void *visit_context)
{
    upo_bst_traverse_in_order_impl(tree->root, visit, visit_context);
}

int upo_bst_is_empty(const upo_bst_t tree)
{
    return ((tree == NULL) || (tree->root == NULL)) ? 1 : 0;
}


/**** EXERCISE #1 - END of FUNDAMENTAL OPERATIONS ****/


/**** EXERCISE #2 - BEGIN of EXTRA OPERATIONS ****/

void* upo_bst_min_impl(upo_bst_node_t *node) {
    if(node == NULL) return NULL;
    if(node->left != NULL) return upo_bst_min_impl(node->left);
    else return node;
} 

void* upo_bst_min(const upo_bst_t tree)
{
    if(tree == NULL || tree->root == NULL) return NULL;
    upo_bst_node_t *node = NULL;
    node = upo_bst_min_impl(tree->root);
    return node != NULL ? node->key : NULL;
}

void* upo_bst_max_impl(upo_bst_node_t *node) {
    if(node == NULL) return NULL;
    if(node->right != NULL) return upo_bst_max_impl(node->right);
    else return node;
}   

void* upo_bst_max(const upo_bst_t tree)
{
    if(tree == NULL || tree->root == NULL) return NULL;
    upo_bst_node_t *node = NULL;
    node = upo_bst_max_impl(tree->root);
    return node != NULL ? node->key : NULL;
}

void upo_bst_delete_min(upo_bst_t tree, int destroy_data)
{
    if(tree == NULL || tree->root == NULL) return;
    void *min = upo_bst_min(tree);
    tree->root = upo_bst_delete_impl(tree->root, min, destroy_data, tree->key_cmp);
}

void upo_bst_delete_max(upo_bst_t tree, int destroy_data)
{
    if(tree == NULL || tree->root == NULL) return;
    void *max = upo_bst_max(tree);
    tree->root = upo_bst_delete_impl(tree->root, max, destroy_data, tree->key_cmp);
}

const upo_bst_node_t *upo_bst_floor_impl(const upo_bst_node_t *node, const void *key, upo_bst_comparator_t key_cmp) {
    if(node != NULL) {
        int cmp = key_cmp(key, node->key);
        if(cmp < 0) return upo_bst_floor_impl(node->left, key, key_cmp);
        else if(cmp > 0) {
            const upo_bst_node_t *floor_node = NULL;
            floor_node = upo_bst_floor_impl(node->right, key, key_cmp);
            return (floor_node != NULL) ? floor_node : node;
        }
        else return node;
    }
    return NULL;
}

void* upo_bst_floor(const upo_bst_t tree, const void *key)
{
    if(tree != NULL && tree->root != NULL) {
        const upo_bst_node_t *node = NULL;
        node = upo_bst_floor_impl(tree->root, key, tree->key_cmp);
        if(node != NULL) return node->key;
    }
    return NULL;
}

const upo_bst_node_t *upo_bst_ceiling_impl(const upo_bst_node_t *node, const void *key, upo_bst_comparator_t key_cmp) {
    if(node != NULL) {
        int cmp = key_cmp(key, node->key);
        if(cmp > 0) return upo_bst_ceiling_impl(node->right, key, key_cmp);
        else if(cmp < 0) {
            const upo_bst_node_t *ceiling_node = NULL;
            ceiling_node = upo_bst_ceiling_impl(node->left, key, key_cmp);
            return (ceiling_node != NULL) ? ceiling_node : node;
        }
        else return node;
    }
    return NULL;
}

void* upo_bst_ceiling(const upo_bst_t tree, const void *key)
{
    if(tree != NULL  && tree->root != NULL) {
        const upo_bst_node_t *node = NULL;
        node = upo_bst_ceiling_impl(tree->root, key, tree->key_cmp);
        if(node != NULL) return node->key;
    }
    return NULL;
}

void upo_bst_keys_range_impl(const upo_bst_node_t *node, const void *low_key, const void *high_key, upo_bst_comparator_t key_cmp, upo_bst_key_list_t *list) {
    if(node != NULL) {
        upo_bst_keys_range_impl(node->left, low_key, high_key, key_cmp, list);
        upo_bst_key_list_node_t *list_node = NULL;
        list_node = malloc(sizeof(struct upo_bst_key_list_node_s));
        if(list_node == NULL) {
            perror("Unable to allocate node.\n");
            abort();
        }
        if((key_cmp(node->key, low_key) >= 0) && (key_cmp(node->key, high_key) <= 0)) {
            list_node->key = node->key;
            list_node->next = *list;
            *list = list_node;
        }
        upo_bst_keys_range_impl(node->right, low_key, high_key, key_cmp, list);
    }
}

upo_bst_key_list_t upo_bst_keys_range(const upo_bst_t tree, const void *low_key, const void *high_key)
{
    if(tree == NULL) return NULL;
    upo_bst_key_list_t list = NULL;
    upo_bst_keys_range_impl(tree->root, low_key, high_key, tree->key_cmp, &list);
    return list;
}

void upo_bst_keys_impl(const upo_bst_node_t *node, upo_bst_comparator_t key_cmp, upo_bst_key_list_t *list) {
    if(node != NULL) {
        upo_bst_keys_impl(node->left, key_cmp, list);
        upo_bst_key_list_node_t *list_node = NULL;
        list_node = malloc(sizeof(struct upo_bst_key_list_node_s));
        if(list_node == NULL) {
            perror("Unable to allocate node.\n");
            abort();
        }
        list_node->key = node->key;
        list_node->next = *list;
        *list = list_node;
        upo_bst_keys_impl(node->right, key_cmp, list);
    }
}

upo_bst_key_list_t upo_bst_keys(const upo_bst_t tree)
{
    if(tree == NULL) return NULL;
    upo_bst_key_list_t list = NULL;
    upo_bst_keys_impl(tree->root, tree->key_cmp, &list);
    return list;
}

int upo_bst_is_bst_impl(const upo_bst_node_t *node, const void *min_key, int min_key_changed, const void *max_key, int max_key_changed, upo_bst_comparator_t key_cmp) {
    if(node != NULL) {
        if(key_cmp(node->key, min_key) < 0 
        || (min_key_changed && key_cmp(node->key, min_key) == 0)
        || key_cmp(node->key, max_key) > 0
        || (max_key_changed && key_cmp(node->key, max_key) == 0)) {
            return 0;
        }
        return upo_bst_is_bst_impl(node->left, min_key, min_key_changed, node->key, 1, key_cmp) && upo_bst_is_bst_impl(node->right, node->key, 1, max_key, max_key_changed, key_cmp);
    }
    return 1;
}

int upo_bst_is_bst(const upo_bst_t tree, const void *min_key, const void *max_key)
{
    if(tree == NULL) return 1;
    return upo_bst_is_bst_impl(tree->root, min_key, 0, max_key, 0, tree->key_cmp);
}

/**** EXERCISE #2 - END of EXTRA OPERATIONS ****/

/**** EXERCISE #3 - BEGIN of ADDITIONAL OPERATIONS ****/

size_t upo_bst_rank_impl(upo_bst_node_t *node, const void *key, upo_bst_comparator_t cmp) {
    if(node == NULL) return 0;
    if(cmp(key, node->key) <= 0) return upo_bst_rank_impl(node->left, key, cmp);
    else return 1 + upo_bst_rank_impl(node->left, key, cmp) + upo_bst_rank_impl(node->right, key, cmp);
}

size_t upo_bst_rank(const upo_bst_t bst, const void *key) {
    if(bst == NULL || upo_bst_is_empty(bst)) return 0;
    return upo_bst_rank_impl(bst->root, key, bst->key_cmp);
}

void *upo_bst_predecessor_impl(upo_bst_node_t *node, const void *key, upo_bst_comparator_t cmp) {
    if(node == NULL) return NULL;
    if(cmp(key, node->key) <= 0) return upo_bst_predecessor_impl(node->left, key, cmp);
    upo_bst_node_t *pred = upo_bst_predecessor_impl(node->right, key, cmp);
    return (pred != NULL) ? pred : node->key;
}

void *upo_bst_predecessor(const upo_bst_t bst, const void* key) {
    if(bst == NULL || upo_bst_is_empty(bst)) return NULL;
    return upo_bst_predecessor_impl(bst->root, key, bst->key_cmp);
}

void *upo_bst_get_value_depth_impl(upo_bst_node_t *node, const void *key, long *depth, upo_bst_comparator_t cmp) {
    if(node == NULL) {
        *depth = -1;
        return NULL;
    }
    *depth += 1;    
    if(cmp(key, node->key) < 0) {
        return upo_bst_get_value_depth_impl(node->left, key, depth, cmp);
    }
    else if(cmp(key, node->key) > 0) {
        return upo_bst_get_value_depth_impl(node->right, key, depth, cmp);
    }
    else
        return node->key;
}

void *upo_bst_get_value_depth(const upo_bst_t bst, const void *key, long *depth) {
    *depth = -1;
    if(bst == NULL || upo_bst_is_empty(bst)) {
        return NULL;
    }
    return upo_bst_get_value_depth_impl(bst->root, key, depth, bst->key_cmp);
}

void upo_bst_keys_le_impl(upo_bst_node_t *node, const void *key, upo_bst_comparator_t cmp, upo_bst_key_list_t *list) {
    if(node == NULL) return;
    if(cmp(node->key, key) <= 0) {
        upo_bst_key_list_node_t *list_node = malloc(sizeof(upo_bst_key_list_node_t));
        if(list_node == NULL) {
            perror("Malloc failed.");
            abort();
        }
        list_node->key = node->key;
        list_node->next = *list;
        *list = list_node;
        upo_bst_keys_le_impl(node->right, key, cmp, list);
    }
    upo_bst_keys_le_impl(node->left, key, cmp, list);
}

upo_bst_key_list_t upo_bst_keys_le(const upo_bst_t bst, const void *key) {
    if(bst == NULL || upo_bst_is_empty(bst)) return NULL;
    upo_bst_key_list_t list = NULL;
    upo_bst_keys_le_impl(bst->root, key, bst->key_cmp, &list);
    return list;
}

size_t upo_bst_subtree_count_leaves_depth_impl(upo_bst_node_t *node, const void *key, size_t leaves_depth, size_t current_depth, int subtree_found, upo_bst_comparator_t cmp) {
    if(node == NULL) return 0;
    if(current_depth > leaves_depth) return 0;
    if(subtree_found) {
        if(upo_bst_is_leaf_impl(node) && current_depth == leaves_depth) return 1;
        return upo_bst_subtree_count_leaves_depth_impl(node->left, key, leaves_depth, current_depth+1, subtree_found, cmp) + upo_bst_subtree_count_leaves_depth_impl(node->right, key, leaves_depth, current_depth+1, subtree_found, cmp);
    }
    else {
        if(cmp(key, node->key) > 0) return upo_bst_subtree_count_leaves_depth_impl(node->right, key, leaves_depth, current_depth+1, subtree_found, cmp);
        else if(cmp(key, node->key) < 0 ) return upo_bst_subtree_count_leaves_depth_impl(node->left, key, leaves_depth, current_depth+1, subtree_found, cmp);
        return upo_bst_subtree_count_leaves_depth_impl(node->left, key, leaves_depth, current_depth+1, 1, cmp);
    }
}

size_t upo_bst_subtree_count_leaves_depth(const upo_bst_t bst, const void *key, size_t d) {
    if(bst == NULL || upo_bst_is_empty(bst)) return 0;
    return upo_bst_subtree_count_leaves_depth_impl(bst->root, key, d, 0, 0, bst->key_cmp);
}

/**** EXERCISE #3 - END of ADDITIONAL OPERATIONS ****/

upo_bst_comparator_t upo_bst_get_comparator(const upo_bst_t tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    return tree->key_cmp;
}
