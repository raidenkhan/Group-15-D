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
void changePin(void);
void balanceCheck(void);
int main(){
printf("\n\n\t\t\t_____________Welcome_____________\n\n");
char cont='y';
while(cont=='y' || cont =='Y'){
    system("color 4f");
    printf("\n\t\t<1> Add a user \n\n\t\t<2> Make A Withdrawal \n\n\t\t<3> ReadData\n\n\t\t<4> Change Pin\n\n\t\t<5> Check My Balance\n \n\t\t>>>:");
    char choice;
    scanf(" %c",&choice);
    fflush(stdin);
    //SWITCH INTO AVAILABLE USER OPTIONS
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
                case'4':
                    changePin();
                    break;
                case '5':
                    balanceCheck();
                    break;
                default:
                    printf("\n\nPlease enter A valid Choice to continue\n\n");
    }
    printf("\nWould you like to continue\n");
    scanf(" %c",&cont);
    fflush(stdin);
}

return 0;
}
void createUser(){
        system("cls");

        //CREATE A USER STRUCT
        struct banker curr;

        //DECLARE FILE POINTERS AND OPEN A FILE IN APPEND MODE
        FILE *fp;
        fp=fopen("newData.txt","a");


        //TAKE USER DATA AND STORE IN USER STRUCT
        printf("\t\tPlease enter name: ");
        scanf(" %s",curr.name);
        printf("\n\t\tPlease enter balance: ");
        fflush(stdin);
        float balance=0;
        scanf("%f",&balance);
        //printf("\n***Balnce is %f\**n",balance);
        curr.balance=balance;
        printf("\n\t\tPlease enter the id: ");
        scanf("%d",&curr.id);
        printf("\n\n\n\t\tAccount Created successfully\n");

        //SAVE USER INFO INTO THE FILE
        fwrite(&curr,sizeof(struct banker),1,fp);
        fclose(fp);
}
void makeWithdrawal(){
    system("cls");

    //DECLEAR VARIABLE S TO USE
        float amount;
        int id=0;
        printf("\n\t\tWhat is your id: ");
        scanf(" %d",&id);
        struct banker curr;
        struct banker toWrite;

        //DECLARE FILE POINTER


        int pres=0;
        FILE *fp;
        FILE *fp1;
        fp=fopen("newData.txt","r");
        fp1=fopen("tmpData.txt","w");
    if(fp==NULL|| fp1==NULL){
        printf("\nCan't create or read file\n");
    }

        //SEARCH THROUGH THE FILE RECORDS
        while(fread(&curr,sizeof(struct banker),1,fp)){
                //printf("\nReading %s %d \n",curr.name,curr.id);
                // printf("Reached here");

                //SEARCH FOR THE USER WHOSE PIN MATCHES
            if(curr.id==id){
                printf("Welcome %s\n",curr.name);
                pres=1;

                //TAKE INPUT OF AMOUNT TO WITHDRAW
                printf("\nHow much would you like to withdraw: ");
                scanf("%f",&amount);

                //COPY THE USER INTO THE A NEW USER WITH THE CHANGES
                strcpy(toWrite.name,curr.name);
                fflush(stdin);
                toWrite.balance=curr.balance-amount;

                //CHECK IF BALANCE IS LESS THAN AMOUNT TO WTIHDRAW

                            if(curr.balance<amount){
                                printf("\nInsufficient Balance to perfom this transaction\n");

                                toWrite.balance=curr.balance;
                            }
                toWrite.id=curr.id;
                fclose(fp1);
                fp1=fopen("tmpData.txt","a");
                fwrite(&toWrite,sizeof(struct banker),1,fp1);
            }

            //IF ID !=CURR ID JUST WRITE THE USE TO THE FILE
            else
            {
                fwrite(&curr,sizeof(struct banker),1,fp1);
            }
        }
        //printf("\nThis is pres %d\n",pres);
        if(!pres){
            printf("No user with this id!!!\n");
        }

        //CLOSE THE FILE POINTERS
        fclose(fp1);
        fclose(fp);

        //REMOVE THE OLD COPY OF THE FILE
        remove("newData.txt");

        //RENAME THE TEMPORY FILE TO THE SAME FILE NAME
        rename("tmpData.txt","newData.txt");

        //END OF FUNCTION
    }


    void readEntries(){

        //CLEAR CONSOLE
    system("cls");

    //DECLEAR A FILE POINTER AND OPEN THE FILE
    FILE *fp;
    fp=fopen("newData.txt","r");
    if(fp==NULL){
        printf("Null pointer Dectedt\n");
    }
    struct banker curr;
    //LOOP THROUGH ALL ENTRIES OF THE FILE
    while(fread(&curr,sizeof(struct banker),1,fp)){
        printf("Name : %s \t Balance: %f \n with id %d\n",curr.name,curr.balance,curr.id);
    }
    fclose(fp);
}



void changePin()
{
        system("cls");
        printf("Please enter the old pin: ");
        int id =0;
        int newId=0;
        scanf("%d",&id);

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
                if(curr.id==id){
                    printf("Welcome %s\n",curr.name);
                    pres=1;
                    printf("\nPlease enter your new Pin: ");
                    scanf("%d",&newId);
                    strcpy(toWrite.name,curr.name);
                    fflush(stdin);
                    toWrite.id=newId;
                    toWrite.balance=curr.balance;
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
void balanceCheck(){

        system("cls");
         struct banker curr;
            int pres=0;
            FILE *fp;
            fp=fopen("newData.txt","r");
        if(fp==NULL)
                        {
                            printf("\nCan't create or read file\n");
                        }
        int id;
        printf("Please enter the user id: ");
        scanf("%d",&id);
            while(fread(&curr,sizeof(struct banker),1,fp))
            {
                if(curr.id==id)
                        {
                            pres=1;
                            printf("\n***WELCOME %s************\n\n ",curr.name);
                            printf("\nYour Account Balance GHS: %.2f\n",curr.balance);
                            printf("\t\t   ___________\n\t\t   ___________\n");
                        }
            }

            if(!pres)
            {
                printf("No user with this id!!!\n");
            }

}
