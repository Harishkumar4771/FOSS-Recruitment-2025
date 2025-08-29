#include<stdio.h>
#include "head_def.h"
int main(){
    char from[50];char to[50];
    long pnr;
    int no;
    struct train* t=createtrain(50,12);
    addhault(t,"Mumbai CSMT","--","18:00");
    addhault(t,"Dadar","18:22","18:24");
    addhault(t,"Thane","18:40","18:44");
    addhault(t,"Kalyan","19:01","19:05");
    addhault(t,"Lonavala","20:10","20:15");
    addhault(t,"Pune","21:20","--");
    int choice;
    printf("Welcome to our train reservation\n");
    printf("Press the following numbers to perform operations needed\n");
    printf("1-Timetable of train\n2-Book ticket\n3-Change boarding point\n");
    printf("4-Cancel ticket\n5-Exit(any integer)\n");
    printf("Choose your option:");
    scanf("%d",&choice);
    switch(choice){
        case 1:
            timetable(t);
            break;
        case 2:
            printf("Your boarding point:");
            fgets(from,sizeof(from),stdin);
            printf("Your destination");
            fgets(to,sizeof(to),stdin);
            printf("Enter number of tickets needed:");
            scanf("%d",&no);
            t=bookticket(t,from,to,no);
            break;
        case 3:
            printf("Your new boarding point:");
            fgets(from,sizeof(from),stdin);
            printf("Enter your pnr number:");
            scanf("%ld",&pnr);
            changeboardingpoint(t,pnr,from);
            break;
        case 4:
           printf("Enter your pnr number:");
           scanf("%ld",&pnr);
           t=cancelticket(t,pnr);    
           break;
        default:
            exit(5);
            break;      
                
                
    }

}
