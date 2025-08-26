#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
struct seat{
    int s_no;
    char* from;
    char* to;
    bool avail;
    struct seat* next_s;
};
struct coach{
    int coach_no;
    struct seat* seats;
    struct coach* next_c;

};
struct  haults{
    char* name;
    char* arrival;
    char* departure;
    struct haults* next_s;
};
struct train{
    int train_no;
    struct coach* coaches;
    struct haults* route;

};
long generatePNR(int train_no){
    time_t now=NULL;
    return train_no*100000+now%100000;
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
            s->from='\0';
            s->to='\0';
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
struct haults* addhault(struct train* t,char* name,char* arr,char* dep){
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
    struct coaches* temp_c=t->coaches;
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
        } 
    }
        
    }

}