#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
struct seat{
    int s_no;
    char from[50];
    char to[50];
    bool avail;
    struct seat* next_s;
};
struct coach{
    int coach_no;
    struct seat* seats;
    struct coach* next_c;

};
struct  haults{
    char name[50];
    struct tm arrival;
    struct tm departure;
    struct station* next_s;
};
struct train{
    int train_no;
    struct coach* coaches;

};
struct train* createtrain(int seat,int coaches);