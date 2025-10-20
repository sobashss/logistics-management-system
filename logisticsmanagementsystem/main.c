#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define NAME_LENTH 60
#define FUEL_PRICE 310

char cityNames[MAX_CITIES][NAME_LENTH];
int cityCount=0;

void manageCities();
void addCity();
void listCities();
void renameCity();
void removeCity();

int main()
{
    int choice=0;

    do{

        printf("===================================\n");
        printf("    Logistics Management System\n");
        printf("===================================\n");
        printf("1.Manage Cities\n");
        printf("2.Manage Distances\n");
        printf("3.New Delivery Requests\n");
        printf("4.View Performance Reports\n");
        printf("5.Exit\n");
        printf("-----------------------------------\n");
        printf("Please Enter Your Choice (1-5): ");
        scanf("%d",&choice);
        printf("-----------------------------------\n");

        switch (choice){

            case 1:
                manageCities();
                break;

            case 2:

                break;

            case 3:

                break;

            case 4:

                break;

            case 5:
                printf("Exiting...\n");
                break;

            default :
                printf("Invalid Choice!\n");
                break;

        }

    } while (choice!=5);


    return 0;
}

void manageCities(){

    int choice1=0;

    do{
        printf("1.Add a New City\n");
        printf("2.Remove a City\n");
        printf("3.Rename a City\n");
        printf("4.Back to Main Menu\n");
        printf("Enter your Choice: ");
        scanf("%d",&choice1);

        switch (choice1){

            case 1:
                addCity();
                break;
            case 2:
                removeCity();
                break;
            case 3:
                renameCity();
                break;
            case 4:
                break;
            default :
                printf("Invalid Choice!\n");
                break;

       }


    } while (choice1!=4);


}

void addCity(){
    char newcityname[NAME_LENTH];

    if(cityCount>=MAX_CITIES){
        printf("Error: Maximum number of cities exceeded.\n");
        return;
    }

    printf("Enter Name of the City: ");
    scanf("%s",newcityname);

    if(newcityname[0] == '\0'){
        printf("Error: Name cannot be empty.\n");
        return;
    }

    for(int i=0;i<cityCount;i++){
        if(strcmp(cityNames[i],newcityname) == 0){
            printf("The city already exists.\n");
            return;
        }
    }

        strncpy(cityNames[cityCount], newcityname, NAME_LENTH);
        cityNames[cityCount][NAME_LENTH - 1] = '\0';
        cityCount++;
        printf("New City added successfully!\n");

}

void listCities(){
    if(cityCount==0){
        printf("No cities available.");
    }
    printf("Available Cities: \n");
    for(int i=0;i<cityCount;i++){
        printf("%d. %s\n",i+1,cityNames[i]);
    }
}

void renameCity(){
    if(cityCount==0){
        printf("No cities available.");
    }
    else{
        int idx=0;
        char name[NAME_LENTH];

        listCities();

        printf("Enter the index of the city you want to rename: ");
        scanf("%d",&idx);

        if(idx<=0 || idx>cityCount){
            printf("Invalid city index!\n");
        }

        printf("Enter New Name: ");
        scanf("%s",name);


        if (name[0] == '\0') {
            printf("Error: Name cannot be empty!");

        }

        for(int i=0; i<cityCount; i++){
            if(i!=(idx-1) && strcmp(cityNames[i],name)==0){
                    printf("\"%s\" city already exists.\n",name);
            }
        }

        strncpy(cityNames[idx-1],name,NAME_LENTH);
        cityNames[idx - 1][NAME_LENTH - 1] = '\0';
        printf("Rename Successful!\n");

    }


}

void removeCity(){

    if(cityCount==0){
        printf("No cities available!");
    }
    else{
        int idx=0;
        char name[NAME_LENTH];

        listCities();

        printf("Enter the index of the city you want to remove: ");
        scanf("%d",&idx);

        if(idx<=0 || idx>cityCount){
            printf("Invalid city index!\n");
        }

        for(int i=idx-1; i<cityCount-1;i++){
            strcpy(cityNames[i],cityNames[i+1]);
        }
        cityCount--;
        printf("City Removed Successfully!\n");


    }

}
