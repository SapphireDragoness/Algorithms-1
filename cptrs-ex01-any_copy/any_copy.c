/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static void any_copy(void *dest, const void *src, size_t n);


void any_copy(void *dest, const void *src, size_t n)
{
    assert( dest != NULL );
    assert( src != NULL );

    unsigned char *pc1 = dest;
    const unsigned char *pc2 = src;
    
    for(size_t i = 0; i < n; i++) {
        pc1[i] = pc2[i];
    }
    
}

int main()
{
    char cary[] = "Hello, World";
    int iary[] = {1,2,3,4,5,-4,-3,-2,-1};
    float fary[] = {1.1,2.2,3.3,4.4,5.5,-4.6,-3.7,-2.8,-1.9};
    char cary_cpy[13]; /* strlen("...") + 1 (for the '\0' character) */
    int iary_cpy[9];
    float fary_cpy[9];
    size_t cary_size = sizeof cary/sizeof cary[0];
    size_t iary_size = sizeof iary/sizeof iary[0];
    size_t fary_size = sizeof fary/sizeof fary[0];
    size_t i;

    any_copy(cary_cpy, cary, sizeof cary);
    printf("[");
    for (i = 0; i < cary_size; ++i)
    {
        assert( cary_cpy[i] == cary[i] );

        printf("'%c' ", cary_cpy[i]);
    }
    printf("]\n");

    printf("[");
    any_copy(iary_cpy, iary, sizeof iary);
    for (i = 0; i < iary_size; ++i)
    {
        assert( iary_cpy[i] == iary[i] );

        printf("%d ", iary_cpy[i]);
    }
    printf("]\n");

    printf("[");
    any_copy(fary_cpy, fary, sizeof fary);
    for (i = 0; i < fary_size; ++i)
    {
        assert( fary_cpy[i] == fary[i] );

        printf("%f ", fary_cpy[i]);
    }
    printf("]\n");

    return 0;
}
