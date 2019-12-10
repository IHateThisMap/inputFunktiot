#include <stdio.h>
#include <stdlib.h>     //strtoul()
#include <ctype.h>      //isdigit()              (tama kuitenkin tuntuu toimivan ihan hyvin ilmankin taman ctype.h:n includettamista. vaikka .gcc antaa varoitusta)

double kysyDouble(int minVal, int maxVal)
{
    double syote = maxVal+1;

    while(syote<minVal || syote>maxVal){
        //oletan etta käyttäjä ei halua syöttää yli 29 merkkiä pitkiä lukuja ohjelmaan.
        syote = 0;    //nollataan "syote" muuttuja
        int maxPituus = 30;
        char ch[maxPituus]; //(+1 tahan arrayhyn etta lopetusmerkki '\0' mahtuu varmasti myos mukaan)
        
        scanf("%29[^\n]s", ch);        //scannaa käyttäjän syöttämän merkkijonon. Toimii moitteittomasti
        while(fgetc(stdin) != '\n'); 
        etsiFloatPoint(ch, maxPituus); 
        syote = strtod(ch, NULL);                //Tallentaa ch muuttujan char[] muotoisen merkkijonon, double muotoiseen "syote" nimiseen muutujaan, tietysti muuttaen sen char->double.
        
        //if((ch[2] != '\0') && (syote == -1)) syote = minVal-1;           //jos merkkijono ch on pidempi kuin 2 merkkia pitka JA jonon ensinmainen merkki on ->
        if (syote<minVal || syote>maxVal || ch[0]=='\0'){          //tarkistetaan saatiinko kayttajalta kelvollisen/halutun kokoinen luku.
            syote = maxVal+1;
            printf("Syoton tulee olla jokin kymmenjarjestelman luku valilta %d-%d.\n\n", minVal,  maxVal);
            printf("Syota luku valilta %d-%d: ", minVal, maxVal);
        }else printf("\n\n");
        
    }return syote;
}

void etsiFloatPoint(char ch[], int pituus){
    if(!isdigit(ch[0]) || ((ch[0] == '-' || ch[0]=='.') && !isdigit(ch[1]))){     //Jos merkkijonosta ei saada kelvollista numeroa niin kasitellaan sita seuraavanlaisesti 
        bool dec = false;   // on tosi jos merkkijonossa on huomattu '.'

        for(int i = 0; i < pituus ; i++) {      //tällä for loopilla siirretän i indexi sinne asti mistä, merkkijonosta löydetään haluttuja merkkejä
            if(isdigit(ch[i]) || ch[i] == '-' || ch[i] == '.'){ //jos merkki on numeraalinen tai ensinmäinen merkki on '-'(tai '.') niin ruvetaan kasittelemaan merkkiojnoa seuraavanlaisesti
                int a = 0;
                ch[a] = ch[i]; //tallennetaan merkkijonon ensinmainen numero tai '-'(tai '.') merkki merkkijonon alkuun..
                if(ch[a] == '.') dec = true;//hypataan yli ensinmaisesta merkista silta varalta etta se on miinus tai '.' merkki.(kasittelemalla se tuossa ylapuolella olevalla parilla rivilla, ja kasvattamalla a arvoa taas tassa.)
                for(a++; a+i < pituus; a++){           //tällä for loopilla edetaan eteen päin kasitellen merkkijonoa, niin pitkään kun hyväksyttäviä merkkejä löytyy
                    if(isdigit(ch[a+i])){          //jos merkkijono jatkuu numeroina..
                        ch[a] = ch[a+i];    //tallennetaan merkkijonon numeroita uusille aikaisemmin merkkijonossa esiintyneille paikoille.
                    }else{
                        if(ch[a+i] == '.' && dec == false){
                            ch[a] = ch[a+i];
                            dec = true;
                        }else{      //jos ei numeraalinen merkki ei ole piste tai piste on jo käytetty aikaisemmin niin->
                            ch[a] = '\0';         //niin tulostetaan sen paalle lopetusmerkki '\0'.
                            return; //i = pituus;
                        }
                    }
                } 
            } else if (ch[i] == '\0'){  //jos huomataan merkkijonon paattyneen ennen ensinmaisenkaan numeraalisen merkin loytymista. Asetetaan merkkijonon ensinmaiseksi ja ainoaksi merkiksi 'a' josta alempi funktio huomaa etta merkkijonosta ei saatu numeroa.
                ch[0] = '\0';           // myos pohjoismaiset aakkoset ja muut erikoismerkit rekisteroityvat merkkijonoon lopetusmerkkina '\0',
                return;                 //tama else if lauseke siis tejkee ohjelmasta hieman kevyemman, mutta johtaa siihen etta erikoismerkit ASCII merkkeihin kuulumattomat merkit saavat ohejlman luulevan merkkijonon paattyneen.
            }                           //ja vaikka niitten jalkeen, merkkijonossa olisi viela kayttokelpoisia numeroita, ne jaavat huomioimatta.
        }
    }
}