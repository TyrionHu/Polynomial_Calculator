/*
 * @Description: 
 * @Version: 
 * @Author: Tyrion Huu
 * @Date: 2022-09-14 21:35:03
 * @LastEditors: Tyrion Huu
 * @LastEditTime: 2022-09-16 21:35:48
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>     
#include<iostream>
#include<cmath>

# define TRUE           1
# define FALSE          0
# define DONE           1
# define ERROR          -1
# define INFEASIBLE     -1
// # define OVERFLOW       -2

typedef int Status;

typedef struct Node
{
    double          coefficient;
    long            power;
    struct Node *   next;
}Node;

