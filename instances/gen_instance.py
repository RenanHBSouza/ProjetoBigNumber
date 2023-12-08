#!/usr/bin/env python
###########################################################
# Created: sáb 21 out 2023 18:39:59
#
# Author: Maycon Sambinelli, msambinelli@gmail.com
#
###########################################################

import sys
 
from random import randint

def random_number(ndigs):

    if randint(0, 1) == 1:
        print('-', end='')

    for i in range(ndigs):
        print(randint(0, 9), end='')
    print()

def random_set_fix_op(nmin, nmax, op, n):

    for i in range(n):
        random_number(randint(nmin, nmax))
        random_number(randint(nmin, nmax))
        print(op)


def random_set_random_op(nmin, nmax, n):

    op = ['+', '-', '*']
    for i in range(n):
        random_number(randint(nmin, nmax))
        random_number(randint(nmin, nmax))
        j = randint(0, len(op) - 1)
        print(op[j])


random_set_random_op(1000, 1000, 10)
