#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define NAME_LENGTH 60
#define FUEL_PRICE 310
#define MAX_DELIVERIES 50

char cityNames[MAX_CITIES][NAME_LENGTH];
int distance[MAX_CITIES][MAX_CITIES];
int cityCount=0;

void manageCities();
void addCity();
void listCities();
void renameCity();
void removeCity();
void setDistance();

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
                printf("Error: Invalid Choice!\n");
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
                printf("Error: Invalid Choice!\n");
                break;

       }


    } while (choice1!=4);


}

void addCity(){
    char newcityname[NAME_LENGTH];

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
            printf("Error: The city already exists.\n");
            return;
        }
    }

        strncpy(cityNames[cityCount], newcityname, NAME_LENGTH);
        cityNames[cityCount][NAME_LENGTH - 1] = '\0';
        cityCount++;
        printf("New City added successfully!\n");

}

void listCities(){
    if(cityCount==0){
        printf("Error: No cities available!\n");
        return;
    }
    printf("Available Cities: \n");
    for(int i=0;i<cityCount;i++){
        printf("%d. %s\n",i+1,cityNames[i]);
    }
}

void renameCity(){
    if(cityCount==0){
        printf("Error: No cities available!\n");
        return;
    }

    int idx=0;
    char name[NAME_LENGTH];

    listCities();

    printf("Enter the index of the city you want to rename: ");
    scanf("%d",&idx);

    if(idx<=0 || idx>cityCount){
        printf("Error: Invalid city index!\n");
        return;
    }

    printf("Enter New Name: ");
    scanf("%s",name);


    if (name[0] == '\0') {
        printf("Error: Name cannot be empty!\n");
        return;

    }

    for(int i=0; i<cityCount; i++){
        if(i!=(idx-1) && strcmp(cityNames[i],name)==0){
            printf("\"%s\" city already exists.\n",name);
            return;
        }
    }

    strncpy(cityNames[idx-1],name,NAME_LENGTH);
    cityNames[idx - 1][NAME_LENGTH - 1] = '\0';
    printf("Rename Successful!\n");




}

void removeCity(){

    if(cityCount==0){
        printf("Error: No cities available!\n");
        return;
    }

    int idx=0;
    char name[NAME_LENGTH];

    listCities();

    printf("Enter the index of the city you want to remove: ");
    scanf("%d",&idx);

    if(idx<=0 || idx>cityCount){
        printf("Error: Invalid city index!\n");
        return;
    }

    for(int i=idx-1; i<cityCount-1;i++){
        strcpy(cityNames[i],cityNames[i+1]);
    }
    cityCount--;
    printf("City Removed Successfully!\n");

}

void setDistance(){
    int city1, city2, dis;
    if(cityCount<2){
        printf("Error: Need at least two cities!\n");
        return;
    }

    listCities();

    printf("Enter city index (From): ");
    scanf("%d",&city1);

    printf("Enter city index (To): ");
    scanf("%d",&city2);

    if (city1<=0 || city1>cityCount || city2<=0 || city2>cityCount) {
        printf("Error: Invalid city index!\n");
        return;
    }

    if (city1 == city2) {
        printf("Distance from a city to itself is always zero!\n");
        return;
    }

    printf("Enter the distance between %s and %s (in km): ", cityNames[city1-1], cityNames[city2-1]);
    scanf("%d",&dis);

    if (dis <= 0) {
        printf("Error: Distance must be a positive non zero value!\n");
        return;
    }

    distance[city1-1][city2-1]= dis;
    distance[city2-1][city1-1]= dis;

    printf("Distance updated successfully!");






}
