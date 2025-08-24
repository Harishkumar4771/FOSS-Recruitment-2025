#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct seat{
    int s_no;
    char from[50];
    char to[50];
    bool avail;
    struct seat* next_s;
};
struct coach{
    struct seat* seats;
    struct coach* next_c;

};
struct train{
    struct coach* coaches;

};