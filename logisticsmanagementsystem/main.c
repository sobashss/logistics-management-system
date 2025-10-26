#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CITIES 30
#define NAME_LENGTH 60
#define FUEL_PRICE 310.0
#define MAX_DELIVERIES 50
#define INF 999999

char cityNames[MAX_CITIES][NAME_LENGTH];
int distance[MAX_CITIES][MAX_CITIES];
int cityCount=0;
char vehicleTypes[3][10] = {"Van", "Truck", "Lorry"};
int vehicleCapacity[3] = {1000, 5000, 10000}; //kg
int vehicleRate[3] = {30, 40, 80};  //LKR
int vehicleSpeed[3] = {60, 50, 45}; //kmph
float vehicleFuelEfficiency[3] = {12.0, 6.0, 4.0}; //kmpl
int deliveryCount=0;
int leastDistance[MAX_CITIES][MAX_CITIES];
int deliverySource[MAX_DELIVERIES];
int deliveryDest[MAX_DELIVERIES];
int deliveryDistance[MAX_DELIVERIES];
float deliveryTime[MAX_DELIVERIES];
float deliveryRevenue[MAX_DELIVERIES];
float deliveryProfit[MAX_DELIVERIES];
char deliveryDate[MAX_DELIVERIES][20];

void manageCities();
void addCity();
void listCities();
void renameCity();
void removeCity();
void setDistance();
void displayDistanceTable();
int selectVehicle();
void deliveryRequest();
float deliveryCost(float distance, float rate, float weight);
float estimatedDeliveryTime(float distance, float speed);
float fuelConsumption(float distance, float efficiency);
float fuelCost(float consumption);
float totalOperationalCost(float deliveryCost, float fuelCost);
float profit(float deliveryCost);
float finalCharge(float totalCost, float profit);
void initializeDistances();
void leastDistanceRoute();
void manageDistances();
void showReports();
void saveData();
void loadData();
int getSafeInput();
void clearScreen();
void pauseProgram();

int main(){
    int choice=0;

    initializeDistances();
    loadData();

    do{
        clearScreen();

        printf("======================================================\n");
        printf("             Logistics Management System\n");
        printf("======================================================\n");
        printf("1.Manage Cities\n");
        printf("2.Manage Distances\n");
        printf("3.New Delivery Requests\n");
        printf("4.View Performance Reports\n");
        printf("5.Exit\n");
        printf("------------------------------------------------------\n");
        printf("Please Enter Your Choice (1-5): ");
        choice = getSafeInput();
        printf("======================================================\n");

        switch (choice){

            case 1:
                manageCities();
                break;

            case 2:
                manageDistances();
                break;

            case 3:
                deliveryRequest();
                break;

            case 4:
                showReports();
                break;

            case 5:
                saveData();
                printf("Exiting...\n");
                break;

            default :
                printf("Error: Invalid Choice!\n");
                pauseProgram();

                break;

        }

    } while (choice!=5);


    return 0;
}

void manageCities(){

    int choice1=0;

    do{
        clearScreen();
        printf("\n------------------ City Management -------------------\n");
        printf("1.Add a New City\n");
        printf("2.Remove a City\n");
        printf("3.Rename a City\n");
        printf("4.Back to Main Menu\n");
        printf("------------------------------------------------------\n");
        printf("Enter your Choice: ");
        choice1= getSafeInput();
        printf("------------------------------------------------------\n");

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
                pauseProgram();
                break;

       }


    } while (choice1!=4);


}

void addCity(){
    char newcityname[NAME_LENGTH];

    if(cityCount>=MAX_CITIES){
        printf("Error: Maximum number of cities exceeded.\n");
        pauseProgram();
        return;
    }

    printf("Enter Name of the City: ");

    fgets(newcityname, NAME_LENGTH, stdin);
    newcityname[strcspn(newcityname, "\n")] = '\0';

    if(newcityname[0] == '\0'){
        printf("Error: Name cannot be empty.\n");
        pauseProgram();
        return;
    }

    for(int i=0;i<cityCount;i++){
        if(strcmp(cityNames[i],newcityname) == 0){
            printf("Error: The city already exists.\n");
            pauseProgram();
            return;
        }
    }

        strncpy(cityNames[cityCount], newcityname, NAME_LENGTH);
        cityNames[cityCount][NAME_LENGTH - 1] = '\0';

        //initializing distances for new city
        int newIdx = cityCount;

        for (int i = 0; i < MAX_CITIES; i++) {
            distance[newIdx][i] = -1;
            distance[i][newIdx] = -1;
        }

        distance[newIdx][newIdx] = 0;

        cityCount++;

        printf("New City added successfully!\n");
        pauseProgram();

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
        pauseProgram();
        return;
    }

    int idx=0;
    char name[NAME_LENGTH];

    listCities();

    printf("Enter the index of the city you want to rename: ");
    idx = getSafeInput();

    if(idx<=0 || idx>cityCount){
        printf("Error: Invalid city index!\n");
        pauseProgram();
        return;
    }

    printf("Enter New Name: ");

    fgets(name, NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';


    if (name[0] == '\0') {
        printf("Error: Name cannot be empty!\n");
        pauseProgram();
        return;
    }

    for(int i=0; i<cityCount; i++){
        if(i!=(idx-1) && strcmp(cityNames[i],name)==0){
            printf("\"%s\" city already exists.\n",name);
            pauseProgram();
            return;
        }
    }

    strncpy(cityNames[idx-1],name,NAME_LENGTH);
    cityNames[idx - 1][NAME_LENGTH - 1] = '\0';
    printf("Rename Successful!\n");
    pauseProgram();
}

void removeCity(){

    if(cityCount==0){
        printf("Error: No cities available!\n");
        pauseProgram();
        return;
    }

    int idx=0;

    listCities();

    printf("Enter the index of the city you want to remove: ");
    idx = getSafeInput();

    if(idx<=0 || idx>cityCount){
        printf("Error: Invalid city index!\n");
        pauseProgram();
        return;
    }
    //removing city from cityNames array
    for(int i=idx-1; i<cityCount-1;i++){
        strcpy(cityNames[i],cityNames[i+1]);
    }

    //removing distances related to that city from distance array
    for (int i=idx-1; i<cityCount-1; i++) {

        for (int j=0; j<cityCount;j++) {
            distance[i][j] = distance[i + 1][j];
        }
    }

    for (int j=idx-1; j<cityCount-1; j++) {

        for (int i=0; i<cityCount; i++) {
            distance[i][j] = distance[i][j + 1];
        }
    }

    cityCount--;

    printf("City Removed Successfully!\n");
    pauseProgram();

    leastDistanceRoute();

}

void setDistance(){
    int city1, city2, dis;
    if(cityCount<2){
        printf("Error: Need at least two cities!\n");
        pauseProgram();
        return;
    }

    listCities();

    printf("Enter city index (From): ");
    city1 = getSafeInput();

    printf("Enter city index (To): ");
    city2 = getSafeInput();

    if (city1<=0 || city1>cityCount || city2<=0 || city2>cityCount) {
        printf("Error: Invalid city index!\n");
        pauseProgram();
        return;
    }

    if (city1 == city2) {
        printf("Distance from a city to itself is always zero!\n");
        pauseProgram();
        return;
    }

    printf("Enter the distance between %s and %s (in km): ", cityNames[city1-1], cityNames[city2-1]);
    dis = getSafeInput();

    if (dis <= 0) {
        printf("Error: Distance must be a positive non zero value!\n");
        pauseProgram();
        return;
    }

    distance[city1-1][city2-1]= dis;
    distance[city2-1][city1-1]= dis;

    printf("Distance updated successfully!\n");

    leastDistanceRoute();
    printf("Info: All least-cost routes have been re-calculated.\n");
    pauseProgram();

}

void displayDistanceTable(){

    clearScreen();

    if (cityCount == 0) {
        printf("Error: No cities added. Cannot display distance table!\n");
        pauseProgram();
        return;
    }


//finding the longest city name
    int longestName = 0;

    for (int i=0; i<cityCount; i++) {
        int len=strlen(cityNames[i]);

        if (len>longestName) {
            longestName=len;
        }
    }

    int headerWidth = longestName + 5;

    int dataWidth = 7;

    printf("\n----- Distance Table (km) -----\n");

    //printing column headers
    printf("%-*s |", headerWidth, " ");

    for (int i = 0; i < cityCount; i++) {

        printf(" [%-*d] ", dataWidth - 3, i + 1);
    }
    printf("\n");

    //printing line to separate
    for(int i = 0; i < headerWidth; i++) printf("-");
    printf("-+-");
    for (int i = 0; i < cityCount; i++) {
        for(int j = 0; j < dataWidth; j++) printf("-");
    }
    printf("\n");

    //printing rows
    for (int i = 0; i < cityCount; i++) {

        char rowHeader[NAME_LENGTH + 5];
        sprintf(rowHeader, "[%d] %s", i + 1, cityNames[i]);

        // printing header
        printf("%-*s |", headerWidth, rowHeader);

        // printing actual distances for that row
        for (int j = 0; j < cityCount; j++) {
            if (distance[i][j] == -1) {

                printf(" %-*s", dataWidth - 1, "N/A");
            } else {

                printf(" %-*d", dataWidth - 1, distance[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");

    pauseProgram();

}

int selectVehicle(){

    clearScreen();
    int choice0;
    printf("\n--- Select a Vehicle Type ---\n");

    for (int i = 0; i < 3; i++) {
        printf("  Type %d: %s  \n", (i + 1), vehicleTypes[i]);
        printf("-----------------------\n");
        printf("  Capacity: %d kg\n", vehicleCapacity[i]);
        printf("  Rate    : %d LKR/km\n", vehicleRate[i]);
        printf("  Speed   : %d km/h\n", vehicleSpeed[i]);
        printf("-----------------------\n");
        printf("\n");
    }
    while(1){
        printf("Enter vehicle type(1=Van, 2=Truck, 3=Lorry): ");
        choice0 = getSafeInput();

        if(choice0>=1 && choice0<=3){
            return choice0-1;
        }
        else{
            printf("Error: Invalid choice. Please enter 1, 2 or 3.\n");
            pauseProgram();
        }
    }

}

void deliveryRequest(){

    clearScreen();

    if(deliveryCount>=MAX_DELIVERIES){
        printf("Error: Maximum delivery limit reached. Cannot add a new request!\n");
        pauseProgram();
        return;
    }

    else if (cityCount < 2) {
        printf("Error: You need at least 2 cities to make a delivery.\n");
        pauseProgram();
        return;
    }

    int weight,sourceIdx,destIdx;

    listCities();

    printf("Enter source city index: ");
    sourceIdx = getSafeInput();

    printf("Enter destination city index: ");
    destIdx = getSafeInput();

    if (sourceIdx <=0 || sourceIdx>cityCount || destIdx<=0 || destIdx>cityCount) {
        printf("Error: Invalid city index!\n");
        pauseProgram();
        return;
    }

    else if (sourceIdx == destIdx) {
        printf("Error: Source and destination cities cannot be the same!\n");
        pauseProgram();
        return;
    }


    int vehicleIdx = selectVehicle();
    printf("Enter delivery weight (kg): ");
    weight= getSafeInput();

    if (weight <= 0) {
        printf("Error: Weight must be a non zero positive number!\n");
        pauseProgram();
        return;
    }

    else if (weight > vehicleCapacity[vehicleIdx]) {
        printf("Error: Weight exceeds the %s's capacity of %d kg.\n",vehicleTypes[vehicleIdx], vehicleCapacity[vehicleIdx]);
        pauseProgram();
        return;
    }

    leastDistanceRoute();

    int dist = leastDistance[sourceIdx-1][destIdx-1];

    if(dist == INF){
        printf("Error: No valid route exists between these two cities.\n");
        pauseProgram();
        return;
    }

    //calculations
    float d =(float)dist;
    float w =(float)weight;
    float r =(float)vehicleRate[vehicleIdx];
    float s =(float)vehicleSpeed[vehicleIdx];
    float e = vehicleFuelEfficiency[vehicleIdx];

    float cost = deliveryCost(d, r, w);
    float dtime = estimatedDeliveryTime(d, s);
    float consumption = fuelConsumption(d, e);
    float fCost = fuelCost(consumption);
    float totalCost = totalOperationalCost(cost, fCost);
    float prof = profit(cost);
    float charge = finalCharge(totalCost, prof);

    //displaying cost estimation to user
    printf("\n======================================================\n");
    printf("            DELIVERY COST ESTIMATION\n");
    printf("------------------------------------------------------\n");
    printf("  From: %s\n", cityNames[sourceIdx-1]);
    printf("  To: %s\n", cityNames[destIdx-1]);
    printf("  Minimum Distance: %d km\n", dist);
    printf("  Vehicle: %s\n", vehicleTypes[vehicleIdx]);
    printf("  Weight:  %d kg\n", weight);
    printf("------------------------------------------------------\n");
    printf("Base Cost: %d x %d x (1 + %d/10000) = %.2f LKR\n", dist, vehicleRate[vehicleIdx], weight, cost);
    printf("Fuel Used: %.2f L\n", consumption);
    printf("Fuel Cost: %.2f LKR\n", fCost);
    printf("Operational Cost: %.2f LKR\n", totalCost);
    printf("Profit: %.2f LKR\n", prof);
    printf("Customer Charge: %.2f LKR\n", charge);
    printf("Estimated Time: %.2f hours\n", dtime);
    printf("======================================================\n");

    char answer;


    while(1){
        printf("Do you want to confirm delivery? (yes= y/ no= n)");
        scanf(" %c",&answer);

        if(answer=='y'|| answer=='Y'){

            //recording date and time of the delivery request
            time_t t = time(NULL);
            struct tm* tm = localtime(&t);
            strftime(deliveryDate[deliveryCount], 20, "%Y-%m-%d_%H:%M", tm);

            deliverySource[deliveryCount] = sourceIdx-1;
            deliveryDest[deliveryCount] = destIdx-1;
            deliveryDistance[deliveryCount] = dist;
            deliveryTime[deliveryCount] = dtime;
            deliveryRevenue[deliveryCount] = charge;
            deliveryProfit[deliveryCount] = prof;

            deliveryCount++;

            printf("Delivery recorded successfully! Total deliveries: %d\n", deliveryCount);
            printf("Date Recorded: %s\n", deliveryDate[deliveryCount - 1]);
            pauseProgram();
            break;
        }

        else if(answer=='n' || answer=='N'){

            printf("Delivery cancelled. Thank You!\n");
            pauseProgram();
            break;
        }

        else{
            printf("Error: Invalid answer. Please enter 'y' or 'n'.\n");
            pauseProgram();
        }

    }

}

//--Cost, Time, and Fuel Calculations--//

float deliveryCost(float distance, float rate, float weight){

    float cost = distance*rate*(1+weight/10000.0);
    return cost;
}

float estimatedDeliveryTime(float distance, float speed){

    float time = distance/speed;
    return time;
}

float fuelConsumption(float distance, float efficiency){

    float consumption = distance/efficiency;
    return consumption;
}

float fuelCost(float consumption){
    float cost = consumption*FUEL_PRICE;
    return cost;
}

float totalOperationalCost(float deliveryCost, float fuelCost){
    float total = deliveryCost+fuelCost;
    return total;
}

float profit(float deliveryCost){
    return deliveryCost*0.25;
}

float finalCharge(float totalCost, float profit){
    return totalCost+profit;
}

//finding least distance root by Floyd Warshall algorithm.

void initializeDistances(){

    for (int i=0; i<MAX_CITIES; i++) {
        for (int j=0; j<MAX_CITIES; j++) {

            if (i==j) {
                distance[i][j]=0;
            } else {
                distance[i][j]=-1;
            }
        }
    }
}

void leastDistanceRoute(){

    for(int i=0; i<cityCount; i++){

        for (int j=0; j<cityCount; j++) {

            if(i==j){
                leastDistance[i][j]=0;
            }
            else if(distance[i][j]==-1){
                leastDistance[i][j]=INF; //INF means no direct paths
            }
            else{
                leastDistance[i][j]=distance[i][j];
            }
        }
    }

    // k = via city
    // i = starting city
    // j = destination city

    for (int k=0; k<cityCount; k++){

        for(int i=0; i<cityCount; i++){

            for(int j=0; j<cityCount; j++){

                if(leastDistance[i][k]==INF || leastDistance[k][j]==INF){
                    continue;
                }

                if(leastDistance[i][k] + leastDistance[k][j] < leastDistance[i][j]){
                    leastDistance[i][j]= leastDistance[i][k] + leastDistance[k][j];

                }
            }
        }
    }
}

void manageDistances() {

    int choice2;

    do {
        printf("---------------- Distance Management -----------------\n");
        printf("1. Input/Edit Distance\n");
        printf("2. Display Distance Table\n");
        printf("3. Back to Main Menu\n");
        printf("------------------------------------------------------\n");
        printf("Enter choice: ");
        choice2 = getSafeInput();
        printf("------------------------------------------------------\n");

        switch (choice2) {
            case 1:
                setDistance();
                break;
            case 2:
                displayDistanceTable();
                break;
            case 3:
                break;
            default:
                printf("Error: Invalid Choice!\n");
                pauseProgram();
                break;
        }
    } while (choice2 != 3);
}

void showReports() {
    clearScreen();
    if (deliveryCount == 0) {
        printf("No deliveries completed yet!\n");
        pauseProgram();
        return;
    }

    float totalDist = 0;
    float totalTime = 0;
    float totalRevenue = 0;
    float totalProfit = 0;
    int longestRoute = 0;
    int shortestRoute = INF;

    for (int i = 0; i < deliveryCount; i++) {
        totalDist += deliveryDistance[i];
        totalTime += deliveryTime[i];
        totalRevenue += deliveryRevenue[i];
        totalProfit += deliveryProfit[i];


        if (deliveryDistance[i] > longestRoute) {
            longestRoute = deliveryDistance[i];
        }

        if (deliveryDistance[i] < shortestRoute) {
            shortestRoute = deliveryDistance[i];
        }
    }

    printf("============================================\n");
    printf("             Performance Report\n");
    printf("============================================\n");
    printf("a. Total Deliveries Completed: %d\n", deliveryCount);
    printf("b. Total Distance Covered:     %.2f km\n", totalDist);
    printf("c. Average Delivery Time:      %.2f hours\n", totalTime / deliveryCount);
    printf("d. Total Revenue:              LKR %.2f\n", totalRevenue);
    printf("d. Total Profit:               LKR %.2f\n", totalProfit);
    printf("e. Longest Route Completed:    %d km\n", longestRoute);
    printf("e. Shortest Route Completed:   %d km\n", shortestRoute);
    printf("=============================================\n");
    pauseProgram();

}

void saveData(){

    FILE *fRoutes, *fDeliveries;

    //saving routes file
    fRoutes= fopen("routes.txt", "w");

    if (fRoutes == NULL) {
        printf("Error: Could not save data to routes.txt\n");
        return;
    }

    fprintf(fRoutes,"%d\n", cityCount);

    for (int i = 0; i<cityCount; i++) {
        fprintf(fRoutes,"%s\n", cityNames[i]);
    }

    for (int i = 0; i<cityCount; i++) {

        for (int j = 0; j<cityCount; j++) {
            fprintf(fRoutes, "%d ", distance[i][j]);
        }
        fprintf(fRoutes, "\n");
    }

    fclose(fRoutes);

    //saving deliveries file

    fDeliveries = fopen("deliveries.txt", "w");

    if (fDeliveries == NULL) {
        printf("Error: Could not save data to deliveries.txt\n");
        return;
    }

    fprintf(fDeliveries, "%d\n", deliveryCount);

    for (int i = 0; i<deliveryCount; i++) {
        fprintf(fDeliveries, "%d %d %d %f %f %f %s\n",deliverySource[i],deliveryDest[i],deliveryDistance[i],deliveryTime[i],deliveryRevenue[i],deliveryProfit[i],deliveryDate[i]);
    }

    fclose(fDeliveries);

    printf("All data saved successfully to routes.txt and deliveries.txt\n");

}

void loadData() {

    FILE *fRoutes, *fDeliveries;
    //loading routes
    fRoutes = fopen("routes.txt", "r");

    if (fRoutes == NULL) {
        printf("Info: routes.txt not found. Starting with empty data.\n");
        initializeDistances();
        return;
    }

    if (fscanf(fRoutes, "%d\n", &cityCount) != 1) {
         printf("Error: routes.txt is corrupt. Starting empty.\n");
         initializeDistances();
         return;
    }

    for (int i=0; i<cityCount; i++) {
        if (fgets(cityNames[i], NAME_LENGTH, fRoutes) == NULL) {
            break;
        }
        cityNames[i][strcspn(cityNames[i], "\n")] = '\0';
    }

    for (int i=0; i<cityCount; i++) {
        for (int j=0; j<cityCount; j++) {
            fscanf(fRoutes, "%d", &distance[i][j]);
        }
    }

    fclose(fRoutes);
    //loading deliveries
    fDeliveries = fopen("deliveries.txt", "r");

    if (fDeliveries == NULL) {
        printf("Info: deliveries.txt not found. Starting with 0 deliveries.\n");
        return;
    }

    fscanf(fDeliveries, "%d\n", &deliveryCount);

    for (int i=0; i<deliveryCount; i++) {
        fscanf(fDeliveries, "%d %d %d %f %f %f %s\n",&deliverySource[i],&deliveryDest[i],&deliveryDistance[i],&deliveryTime[i],&deliveryRevenue[i],&deliveryProfit[i],deliveryDate[i]);
    }

    fclose(fDeliveries);

    printf("Data loaded successfully!\n");

    leastDistanceRoute();
}

//to avoid infinite loops
int getSafeInput() {

    int input;
    int result;

    while (1) {

        result = scanf("%d", &input);

        if (result==1) {

            while (getchar() != '\n');
            return input;
        }
        else if (result==0) {

            printf("Error: Invalid input. Please enter a number! ");

            while (getchar() != '\n');

        }
    }
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void pauseProgram() {

    printf("\nPress Enter to continue...");
    getchar();
}
