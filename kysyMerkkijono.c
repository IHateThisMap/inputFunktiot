#include <string.h>     //strlen() ja strcpy()

void kysyMerkkijono(char ch[], int maxLeng){
    char isoOsoite[256];
    do{
        if(scanf("%255[^\n]s", isoOsoite) != 1 || (strlen(isoOsoite) > maxLeng)) {
            while(fgetc(stdin) != '\n');
            printf("\n%ssyota 1-%d merkkia, kiitos%s: ", YEL, maxLeng, NRM);
        }else break;
    }while(1);
    strcpy(ch, isoOsoite);
}