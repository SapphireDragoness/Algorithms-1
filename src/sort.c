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
#include "sort_private.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void upo_insertion_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    unsigned char *bp = base;
    for(size_t i = 1; i < n; i++){
        size_t j = i;
        while((j > 0) && cmp(bp+j*size, bp+(j-1)*size) < 0) {
            upo_swap(bp+j*size, bp+(j-1)*size, size);
            j--;
        }
    }
}

void upo_merge_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    upo_merge_sort_rec(base, 0, n - 1, size, cmp);
}

void upo_merge_sort_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp) { 
    size_t mid;
    if(lo >= hi) return;
    mid = lo + (hi - lo)/2;
    upo_merge_sort_rec(base, lo, mid, size, cmp);
    upo_merge_sort_rec(base, mid + 1, hi, size, cmp);
    upo_merge(base, lo, mid, hi, size, cmp);
}

void upo_merge(void *base, size_t lo, size_t mid, size_t hi, size_t size, upo_sort_comparator_t cmp) {
    size_t i = 0;
    size_t j = mid + 1 - lo;
    size_t n = hi - lo + 1;
    size_t k;
    unsigned char *bp = base;
    unsigned char *aux = NULL;
    aux = malloc(n*size);
    memcpy(aux, bp+lo*size, n*size);
    for(k = lo; k <= hi; k++) {
        if(i > (mid - lo)) {
            memcpy(bp+k*size, aux+j*size, size);
            j++;
        }
        else if(j > (hi - lo)) {
            memcpy(bp+k*size, aux+i*size, size);           
            i++;
        }
        else if(cmp(aux+j*size, aux+i*size) < 0) {
            memcpy(bp+k*size, aux+j*size, size);           
            j++;
        }
        else {
            memcpy(bp+k*size, aux+i*size, size);    
            i++;
        }
    }
    free(aux);
}

void upo_quick_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    upo_quick_sort_rec(base, 0, n - 1, size, cmp);
}

void upo_quick_sort_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp) {
    size_t j;
    if(lo >= hi) return;
    j = upo_partition(base, lo, hi, size, cmp);
    if(j > 0) upo_quick_sort_rec(base, lo, j - 1, size, cmp);
    upo_quick_sort_rec(base, j + 1, hi, size, cmp);
}

size_t upo_partition(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp) {
    unsigned char *bp = base;
    size_t p = lo;
    size_t i = lo;
    size_t j = hi + 1;
    while(1) {
        do{
            i += 1;
        }while((i < hi) && cmp(bp+i*size, bp+p*size) < 0);
        do{
            j -= 1;
        }while((j > lo) && cmp(bp+j*size, bp+p*size) > 0);
        if(i >= j) break;
        upo_swap(bp+i*size, bp+j*size, size);
    }
    upo_swap(bp+p*size, bp+j*size, size);
    return j;
}

void upo_bubble_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp) {
    unsigned char *pc = base;
    int swapped = 1;

    for(size_t i = 0; i < n && swapped; i++) {
        swapped = 0;
        for(size_t j = 0; j < n-1; j++) {
            if(cmp(pc+j*size, pc+(j+1)*size) > 0)  {
                upo_swap(pc+j*size, pc+(j+1)*size, size);
                swapped = 1;
            }
        }
    }
}

void upo_quick_sort_median3_cutoff(void *base, size_t n, size_t size, upo_sort_comparator_t cmp) {
    upo_quick_sort_median3_cutoff_rec(base, 0, n-1, size, cmp);
}

void upo_quick_sort_median3_cutoff_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp) {
    if(lo >= hi) return;
    if(hi-lo+1 <= 10) {
        upo_insertion_sort((unsigned char*) base + lo*size, hi-lo+1, size, cmp);
        return;
    }
    size_t j = upo_partition_median3(base, lo, hi, size, cmp);
    if(j > 0) upo_quick_sort_median3_cutoff_rec(base, lo, j-1, size, cmp);
    upo_quick_sort_median3_cutoff_rec(base, j+1, hi, size, cmp);
}

size_t upo_partition_median3(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp) {
    size_t mid = lo+(hi-lo)/2;
    unsigned char *ptr = base;
    unsigned char *lo_ptr = ptr+lo*size;
    unsigned char *mid_ptr = ptr+mid*size;
    unsigned char *hi_ptr = ptr+hi*size;
    if(cmp(lo_ptr, mid_ptr) > 0) {
        upo_swap(lo_ptr, mid_ptr, size);
    }
    if(cmp(lo_ptr, hi_ptr) > 0) {
        upo_swap(lo_ptr, hi_ptr, size);
    }
    if(cmp(mid_ptr, hi_ptr) > 0) {
        upo_swap(mid_ptr, hi_ptr, size);
    }
    if((hi-lo+1) <= 3) {
        return mid;
    }
    upo_swap(mid_ptr, ptr+(lo+1)*size, size);
    return upo_partition(base, lo+1, hi-1, size, cmp);
}

void upo_swap(void *pv1, void *pv2, size_t n) {
    if(pv1 == pv2) return;
    void *tmp = malloc(n);
    memmove(tmp, pv1, n);
    memmove(pv1, pv2, n);
    memmove(pv2, tmp, n);
    free(tmp);
}