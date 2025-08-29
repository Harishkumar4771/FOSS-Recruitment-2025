#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
/*This file contains of all functions and structures required for our project*/
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
    char arrival[6];
    char departure[6];
    struct haults* next_s;
};
struct train{
    int train_no;
    struct coach* coaches;
    struct haults* route;

};
long generatePNR(int train_no){

    return rand()%100000;
}
struct train* createtrain(int seat,int coaches){
    struct train* train=(struct train*)malloc(sizeof(struct train));
    if(!train){
        printf("Memory allocation failed");
        return NULL;
    }
    train->train_no=12636;
    train->coaches=NULL;
    train->route=NULL;
    struct coach* prevcoach=NULL;
    int i,j;
    for(i=1;i<=coaches;i++){
        struct coach* c=(struct coach*)malloc(sizeof(struct coach));
        c->coach_no=i;
        c->seats=NULL;
        c->next_c=NULL;
        struct seat* prevseat;
        for(j=1;j<=seat;j++){
            struct seat* s=(struct seat*)malloc(sizeof(struct seat));
            s->s_no=j;
            s->from[0]='\0';
            s->to[0]='\0';
            s->avail=true;
            s->next_s=NULL;
            if(prevseat==NULL){
                c->seats=s;
            }
            else{
                prevseat->next_s=s;
            }
            prevseat=s;

        }
        if (prevcoach==NULL){
            train->coaches=c;
        }
        else{
            prevcoach->next_c=c;
        }
        prevcoach=c;


    }
    return train;
    
}
void addhault(struct train* t,char* name,char* arr,char* dep){
    struct haults* station=(struct haults*)malloc(sizeof(struct haults));
    strcpy(station->name,name);
    strcpy(station->arrival,arr);
    strcpy(station->departure,dep);
    station->next_s=NULL;
    if(t->route==NULL){
        t->route=station;
    }
    else{
        struct haults* temp=t->route;
        while(temp->next_s!=NULL){
            temp=temp->next_s;
        }
        temp->next_s=station;
    }
    
}

void timetable(struct train* t){
    printf("Route of train no %d\n",t->train_no);
    struct haults* temp=t->route;
    while(temp!=NULL){
        printf("%12s Arr:%6s  Dep:%6s",temp->name,temp->arrival,temp->departure);
        temp=temp->next_s;
    }
}
struct train* bookticket(struct train* t,char* from,char* to,int number){
    FILE *fp=fopen("Passenger_details.txt","a");
    struct coach* temp_c=t->coaches;
    int s=number;
    while(temp_c!=NULL && s>0){
        struct seat* temp_s=temp_c->seats;
        while(temp_s!=NULL && s>0){
        if(temp_s->avail==true){
            temp_s->avail=false;
            int seatno=temp_s->s_no;
            int coachno=temp_c->coach_no;
            strcpy(temp_s->from,from);
            strcpy(temp_s->to,to);
            long pnr=generatePNR(t->train_no);
            printf("-------------Ticket-------------\n");
            printf("PNR   : %ld\n", pnr);
            printf("Train : %d\n", t->train_no);
            printf("Coach : %d\n", temp_c->coach_no);
            printf("Seat  : %d\n", temp_s->s_no);
            printf("From  : %s\n", from);
            printf("To    : %s\n", to);
            s=s-1;
            fprintf(fp, "PNR:%ld Train:%d Coach:%d Seat:%d From:%s To:%s\n",
            pnr, t->train_no, temp_c->coach_no, temp_s->s_no, from, to);
        }
        temp_s=temp_s->next_s;
    }
    temp_c=temp_c->next_c;
        
    }
    fclose(fp);
    return t;

}
void changeboardingpoint(struct train* t, long pnr, char* from2) {
    FILE *fp, *temp;
    fp = fopen("Passenger_details.txt", "r");
    temp = fopen("temp.txt", "w");
    long f_pnr;
    int train_no, coach, seat;
    char from[50], to[50];
    int found = 0;

    while (fscanf(fp, "PNR:%ld Train:%d Coach:%d Seat:%d From:%s To:%s\n",
                  &f_pnr, &train_no, &coach, &seat, from, to) == 6) {
        if (f_pnr == pnr) {
            found = 1;
            fprintf(temp, "PNR:%ld Train:%d Coach:%d Seat:%d From:%s To:%s\n",
                    f_pnr, train_no, coach, seat, from2, to);
            printf("Boarding point changed for PNR %ld → New From: %s\n", pnr, from2);
        } else {
            fprintf(temp, "PNR:%ld Train:%d Coach:%d Seat:%d From:%s To:%s\n",
                    f_pnr, train_no, coach, seat, from, to);
        }
    }

    fclose(fp);
    fclose(temp);
    remove("Passenger_details.txt");
    rename("temp.txt", "Passenger_details.txt");
    if (!found) {
        printf("PNR Number doesn’t exist\n");
    }
}

struct train* cancelticket(struct train* t, long pnr) {
    FILE *fp, *temp;
    fp = fopen("Passenger_details.txt", "r");
    temp = fopen("temp.txt", "w");
    long f_pnr;
    int train_no, coach, seat;
    char from[50], to[50];
    int found = 0;

    while (fscanf(fp, "PNR:%ld Train:%d Coach:%d Seat:%d From:%s To:%s\n",
                  &f_pnr, &train_no, &coach, &seat, from, to) == 6) {
        if (f_pnr == pnr) {
            found = 1;
            // update linked list availability
            struct coach* temp_c = t->coaches;
            while (temp_c) {
                if (temp_c->coach_no == coach) {
                    struct seat* temp_s = temp_c->seats;
                    while (temp_s) {
                        if (temp_s->s_no == seat) {
                            temp_s->avail = true;
                            temp_s->from[0] = '\0';
                            temp_s->to[0] = '\0';
                            break;
                        }
                        temp_s = temp_s->next_s;
                    }
                    break;
                }
                temp_c = temp_c->next_c;
            }
            printf("Ticket cancelled successfully\n");
            // don’t write cancelled ticket into file
        } else {
            fprintf(temp, "PNR:%ld Train:%d Coach:%d Seat:%d From:%s To:%s\n",
                    f_pnr, train_no, coach, seat, from, to);
        }
    }

    fclose(fp);
    fclose(temp);
    remove("Passenger_details.txt");
    rename("temp.txt", "Passenger_details.txt");
    if (!found) {
        printf("PNR number not exist\n");
    }
    return t;
}


