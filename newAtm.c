#include <stdio.h>
#include <string.h>
struct banker{
char name[10];
float balance;
int id;
};
void readEntries(void);
void makeWithdrawal(void);
void createUser(void);
int main(){
printf("\n\nWelcome\n\n");
char cont='y';
while(cont=='y'){
    printf("\n1.Add a user \n2.Make A Deposit \n3.ReadData\n>>>:");
    char choice;
    scanf(" %c",&choice);
    fflush(stdin);
    switch(choice){
case '1':
    createUser();
    break;
case '2':
    makeWithdrawal();
    break;
case '3':
    readEntries();
    break;
default:
    printf("Please enter A valid Choice to continue");
    }
    printf("\nWould you like to continue\n");
    scanf(" %c",&cont);
    fflush(stdin);
}

return 0;
}
void createUser(){
struct banker curr;
FILE *fp;
fp=fopen("newData.txt","w");
printf("Please enter name: ");
scanf(" %s",curr.name);
printf("\nPlease enter balance: ");
fflush(stdin);
float balance=0;
scanf("%f",&balance);
//printf("\n***Balnce is %f\**n",balance);
curr.balance=balance;
printf("\nPlease enter the id: ");
scanf("%d",&curr.id);
printf("\nAccount Created successfully\n");
fwrite(&curr,sizeof(struct banker),1,fp);
fclose(fp);
}
void makeWithdrawal(){
    float amount;
    int id=0;
    printf("What is your id: ");
    scanf(" %d",&id);
    struct banker curr;
    struct banker toWrite;
    int pres=0;
    FILE *fp;
    FILE *fp1;
    fp=fopen("newData.txt","r");
    fp1=fopen("tmpData.txt","w");
if(fp==NULL|| fp1==NULL){
    printf("\nCan't create or read file\n");
}
    while(fread(&curr,sizeof(struct banker),1,fp)){
            printf("\nReading %s %d \n",curr.name,curr.id);
             printf("Reached here");
        if(curr.id==id){
            printf("Welcome %s\n",curr.name);
            pres=1;
            printf("\nHow much would you like to withdraw: ");
            scanf("%f",&amount);
            strcpy(toWrite.name,curr.name);
            fflush(stdin);
            toWrite.balance=curr.balance-amount;
            toWrite.id=curr.id;
            fclose(fp1);
            fp1=fopen("tmpData.txt","a");
            fwrite(&toWrite,sizeof(struct banker),1,fp1);
        }else{
            fwrite(&curr,sizeof(struct banker),1,fp1);
        }
    }
    printf("\nThis is pres %d\n",pres);
    if(!pres){
        printf("No user with this id!!!\n");
    }
    fclose(fp1);
    fclose(fp);
    remove("newData.txt");
    rename("tmpData.txt","newData.txt");
}
void readEntries(){
FILE *fp;
fp=fopen("newData.txt","r");
if(fp==NULL){
    printf("Null pointer Dectedt\n");
}
struct banker curr;
while(fread(&curr,sizeof(struct banker),1,fp)){
    printf("Name : %s \t Balance: %f \n with id %d",curr.name,curr.balance,curr.id);
}
fclose(fp);
}
