#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define FUEL_PRICE 310


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
