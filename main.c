#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addAsset(FILE*);
void listAsset(FILE*);


//TODO RECURSIVE FUNCTION FOR ALL FUNCTIONS

int main()
{

    int userAction;
    FILE *fpAssets;

    printf("\t//MoD Asset Tracking System//\n");

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
    } else if(userAction==4){
        deleteAsset();
    }
    return 0;
}

void fileVerification(FILE *fpAssets){
    if(fpAssets==NULL){
        printf("!! ERROR OPENING FILE !!");
        exit(-1);
    }
}

void addAsset(FILE *fpAssets){
    char assetID[4], assetName[50], assetType[10], assetLocation[20];
    float assetValue;

    fpAssets = fopen("assets.txt", "a");
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

    fprintf(fpAssets, "\n%s %s %s %s %.2f", assetID, assetName, assetType, assetLocation, assetValue);
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

}

void deleteAsset(FILE* fpAssets){
    char assetID[4];

    fpAssets = fopen("assets.txt", "r");


    printf("Please ");
}
