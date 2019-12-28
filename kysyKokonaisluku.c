#include <stdio.h>
#include <stdlib.h>     //strtoll()

int kysyKokonaisluku(int minVal, int maxVal);



int kysyKokonaisluku(int minVal, int maxVal){
    long long syote = maxVal+1;
    int maxPituus = 25;
    char ch[maxPituus+1]; 
    do{
        syote = 0;
        if(fgets(ch, maxPituus, stdin) == NULL || (strlen(ch) > maxPituus)) {
            while(fgetc(stdin) != '\n');
            printf("\n\nsyota vahemman(1-%d) merkkeja, kiitos: ", maxPituus);
        }else{
            etsiKokonaisluku(ch, maxPituus);
            if (ch[0] != '\0')
                {syote = strtoll(ch, NULL, 10);}
            
            if (syote < minVal || syote > maxVal || ch[0] == '\0')
                {printf("\nSyoton tulee olla kokonaisluku valilta %d-%d.\n\n", minVal, maxVal);}
            else return syote;
        }
    }while(1);
}


void etsiKokonaisluku(char ch[], int pituus){  
    for(int i = 0; i < pituus ; i++) {
        if (isdigit(ch[i])) {
            int a = 0;
            if(ch[0] == '-') a = 1 ;

            for(NULL; a+i < pituus; a++){      //siirrytaan tahan for loopiin jossa siirretaan numeroita merkkijonon alkuun kunnes numerot loppuu tai merkkijonon pituus loppuu.
                if(ch[a+i] == '.' && isdigit(ch[a+i+1])){       
                    ch[a+i] = '\0';                             //
                                                                //
                    for(a++; a+i < pituus; a++){                //Tällä tarkistetaan pisteen löytyessä, että eihän sen jälkeen numerojonossamme ole muita numeroita kuin '0'
                        if(!isdigit(ch[a+i])) return;           //sekä lopetetaan merkkijonon kopioiminen siihen.
                                                                //
                        else if(ch[a+i] != '0'){                //
                            ch[0] = '\0';                       //
                            return;                             //
                        }                                       //
                    }                                           //
                }                                               
                else if(isdigit(ch[a+i]))   ch[a] = ch[a+i];     //tallennetaan merkkijonon _numeroita_ uusille aikaisemmin merkkijonossa esiintyneille paikoille.
                else {
                    ch[a] = '\0';                               //kun jokin merkki ei ole numeraalinen merkki, niin tulostetaan sen paalle lopetusmerkki '\0'.
                    return;                                     //
                }
            } 

        } else if(ch[i] == '\0' || ( isdigit(ch[i+1]) && (ch[i] == '.') ))  {//jos huomataan merkkijonon paattyneen ennen ensinmaisenkaan numeraalisen merkin loytymista.. (tai jos huomataan kayttajan yritteneen syottaa <1, float point luku)
            ch[0] = '\0';
            return;
        } else if(ch[i] == '-' && isdigit(ch[i+1]))     ch[0] = '-';
    }
}