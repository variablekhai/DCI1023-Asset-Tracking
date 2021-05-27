#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1000

void addAsset(FILE*);
void listAsset(FILE*);
void deleteAsset();

int main()
{

    int userAction, exit;
    FILE *fpAssets;

    printf("\t//MoD Asset Tracking System//\n");

    while(exit!=1){

    printf("\n\tMain Menu\n"
           "1. Add new asset\n"
           "2. List all assets\n"
           "3. Update existing asset\n"
           "4. Delete existing asset\n"
           "5. Exit system\n"
           "\nWhat would you like to do? : ");
    scanf("%d", &userAction);

    if(userAction==1){
        addAsset(fpAssets);
    } else if(userAction==2){
        listAsset(fpAssets);
    } else if(userAction==3){
        updateAsset();
    } else if(userAction==4){
        deleteAsset();
    } else {
        exit = 1;
    }

    }

    return 0;
}

void fileVerification(FILE *fpAssets){
    if(fpAssets==NULL){
        printf("!! ERROR OPENING FILE !!");     //Error file handler
        exit(-1);
    }
}

void addAsset(FILE *fpAssets){
    char assetID[4], assetName[50], assetType[10], assetLocation[20];
    float assetValue;

    fpAssets = fopen("assets.txt", "a");        //Open file to append new data
    fileVerification(fpAssets);

    printf("Enter asset ID : ");
    scanf("%s", &assetID);
    printf("Enter asset name : ");
    scanf("%s", &assetName);
    printf("Enter type of asset (VEHICLE/WEAPON) : ");
    scanf("%s", &assetType);
    printf("Enter asset location : ");
    scanf("%s", &assetLocation);
    printf("Enter asset value : ");
    scanf("%f", &assetValue);

    fprintf(fpAssets, "\n%s %s %s %s %.2f", assetID, assetName, assetType, assetLocation, assetValue); //Insert data to file
    fclose(fpAssets);
}

void listAsset(FILE* fpAssets){
    fpAssets = fopen("assets.txt", "r");
    char stringLine[255], *stringToken, *assetID, *assetName, *assetType, *assetLocation;
    float assetValue;
    printf("==============================================\n");
    printf("ID NAME TYPE LOCATION VALUE\n");
    printf("==============================================\n");
    while(!feof(fpAssets)){
        fgets(stringLine, 255, fpAssets);

        stringToken = strtok(stringLine, " ");

        for(int i=0;i<5;i++){
            if(i==0){
                assetID = stringToken;
            } else if(i==1){
                assetName = stringToken;
            } else if(i==2){
                assetType = stringToken;
            } else if(i==3) {
                assetLocation = stringToken;
            } else {
                assetValue = atof(stringToken);
            }
            stringToken = strtok(NULL, " ");
        }
        printf("%s %s %s %s %.2f\n", assetID, assetName, assetType, assetLocation, assetValue);
    }
    fclose(fpAssets);
}

void updateAsset(){
    FILE* fpAssets;
    FILE* fpTemp;
    char buffer[BUFFER_SIZE];
    char newLine[BUFFER_SIZE];

    int line, count, i=1, ret;

    fpAssets = fopen("assets.txt", "r");

    while(!feof(fpAssets)){
        fgets(buffer, BUFFER_SIZE, fpAssets);
        printf("%d. %s", i, buffer);
        i++;
    }

    rewind(fpAssets);

    printf("\nEnter the line number to update asset : ");
    scanf("%d", &line);

    fflush(stdin);

    printf("\nEnter new data asset for line '%d' :", line);
    fgets(newLine, BUFFER_SIZE, stdin);

    fpTemp = fopen("replace.tmp", "w");

    if (fpAssets == NULL || fpTemp == NULL){
        printf("Unable to open file\n");
        exit(-1);
    }

    count=0;
    while((fgets(buffer, BUFFER_SIZE, fpAssets)) != NULL){
        count++;

        if (count == line){
            fputs(newLine, fpTemp);
        } else {
            fputs(buffer, fpTemp);
        }
    }

    fclose(fpAssets);
    fclose(fpTemp);

    ret = remove("assets.txt");
    rename("replace.tmp", "assets.txt");

    if(ret==0){
        printf("Succesfully updated data!\n");
    } else {
        printf("Failed to update data!\n");
    }

}

void deleteAsset(){
    FILE* fpNewAssets;
    FILE* fpAssets;
    char buffer[BUFFER_SIZE];
    int count=1, line, ret, i=1;

    fpAssets = fopen("assets.txt", "r");
    fpNewAssets = fopen("assetsTMP.tmp", "w");

    while(!feof(fpAssets)){                                   //Display list of assets
        fgets(buffer, BUFFER_SIZE, fpAssets);
        printf("%d. %s", i, buffer);
        i++;
    }

    printf("\nPlease enter the line no. to delete : ");       //Enter the line that wants to get deleted
    scanf("%d", &line);

    rewind(fpAssets);                                         //Point filePointer back to start of file

    while((fgets(buffer, BUFFER_SIZE, fpAssets)) != NULL){    //Write all the contents from old file to new file, skipping the deleted line
        if (line != count)
            fputs(buffer, fpNewAssets);

        count++;
    }

    fclose(fpAssets);                               //Close all file
    fclose(fpNewAssets);

    remove("assets.txt");                           //Delete old file
    ret = rename("assetsTMP.tmp", "assets.txt");    //Rename new file to old file name

        if(ret == 0){                                           //Error handling
            printf("\nAsset deleted succesfully !\n");
        }
        else {
        printf("Error: unable to delete data !\n");
        fprintf(stderr, "System error (%d): %s\n", errno, strerror(errno));
        }

}
