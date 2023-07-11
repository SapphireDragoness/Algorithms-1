/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file upo/test/utility.h
 *
 * \brief Collection of useful functions for testing.
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

#ifndef UPO_TEST_H
#define UPO_TEST_H


int upo_test_int_cmp(const void* a, const void* b);

int upo_test_str_cmp(const void* a, const void* b);

char* upo_test_double_to_string(const void *pval);

char* upo_test_int_to_string(const void *pval);

char* upo_test_str_to_string(const void *pval);

char* upo_test_array_to_string(const void *base, size_t nelem, size_t elem_sz, char* (*to_string)(const void*));


#endif /* UPO_TEST_H */
