#include <stdio.h>
#include <stdlib.h>     //strtoull()

/*
    Palauttaa käyttäjältä kysytyn positiivisen kokonailuvun muodossa unsigned int.

    Ottaa parametreinä luvun minimi ja maksimi arvot. Joitten ulkopuolelle jääviä käyttäjän syötteitä ei hyväksytä.
        Jos syötettä ei hyväksytä niin sitä kysytään uudestaan.
        HUOM. maxVal saa olla korkeintaan ULONG_LONG_MAX-1 .

    (vähän modifoitu tähän tehtävään sopivammaksi
    tätä voisi vielä optimoida jonkin verran paremmaksi mutta saa nyt kelvata tähännn.)*/
unsigned int kysyPosInt(unsigned int minVal, unsigned long long maxVal){
    unsigned long long syote = maxVal+1;
    int maxPituus = 25;
    char ch[maxPituus+1]; 
    do{
        syote = 0;
        if(fgets(ch, maxPituus, stdin) == NULL || (strlen(ch) > maxPituus)) {
            while(fgetc(stdin) != '\n');
            printf("%s\nsyota vahemman(1-%d) merkkeja, kiitos%s: ", YEL, maxPituus, NRM);
        }else{
            etsiPosInt(ch, maxPituus);
            if (ch[0] != '\0')
                {syote = strtoull(ch, NULL, 10);}
            
            if (syote < minVal || syote > maxVal || ch[0] == '\0')
                {printf("%s\nSyoton tulee olla kokonaisluku valilta %u-%llu.%s\n\n", YEL, minVal, maxVal, NRM);}
            else return syote;
        }
    }while(1);
}


/*
    jos merkkijonon ensinmanen merkki ei ole numero niin koitetaan etsia merkkionosta numeroa. Jos numero loytyy niin siirretaan se merkkijonon alkuun
        ihan vain karsimassa kayttajan kirjoitusvirheita. 
        esim jos kayttaja tarkoitti syottaa luvun "2019" ja vahingossa syottikin "dwadwadaw joo 2019 jee !!1!111!!!", niin tama funktio etsiis iseltä tuon "2019" kokonaisluvun ja sijoittaa sen merkkijonon kärkeen.
        Jos huomaa löydetyn luvun olevan negatiivinen, asettaa lopetusmerkin, heti merkkijonon alkuun.
            sama juttu, jos löydetään desimaalinumeroita(poislukien esim. "jee =)(?)()(=  700.000" -> "700")(esim2. "wasd23.4wasd" -> "45sd23.4wasd" -> '\0''5''s''d''2''3''.''4''w''a''s''d'
            
    Muuttujen selityksi:
        int i:
            indeksin laskuri merkkijonon alusta siihe npisteeseen kunnes löydetään numeroita
            
        int a:
            indeksin laskuri siitä pisteestä kun löydettiin ensinmäinen numeraalinen merkki, eteen päin
            
    (miinuksien ja pisteiden tunnistus monimutkaisti tätä funktiota hieman. mutta kyllä siinä ihan logiikka on ja selkiää jos jaksaa katsella vähän aikaa..:D)
        taidan nyt kuitenkin jättää nuo kommentit tähän funktioon*/
void etsiPosInt(char ch[], unsigned int pituus){  
    for(int i = 0; i < pituus ; i++) {
        if (isdigit(ch[i])) {                   //jos merkki on numeraalinen niin ruvetaan kasittelemaan merkkiojnoa seuraavanlaisesti
            for(int a = 0; a+i < pituus; a++){                  //siirrytaan tahan for loopiin jossa siirretaan numeroita merkkijonon alkuun kunnes numerot loppuu tai merkkijonon pituus loppuu.
                if(ch[a+i] == '.' && isdigit(ch[a+i+1])){
                    ch[a+i] = '\0';                 //asetetaan pisteen kohdalle lopetusmerkki.
                    for(a++; a+i < pituus; a++){    //ja tarkistetaan että eihän pisteen toiselle puolelle olla yritetty laittaa muita numeroita kuin nollia, tai muita ei numeraalisia merkkejä
                        if(!isdigit(ch[a+i])) return;   //jos pisteen jälkeen ei numeroita, niin hyvä. Lopetetaan merkkijonon käsittely.
                        else if(ch[a+i] != '0'){        //jos on muita numeroita kuin nollia, 
                            ch[0] = '\0';               //niin ei hyväksytä käyttäjän syötettä(asettamalla merkkijonon alkuun lopetusmerkki)
                            return;                     //ja lopetetaan merkkijonon käsittely
                        }
                    }
                }else if (isdigit(ch[a+i])) ch[a] = ch[a+i];    //tallennetaan merkkijonon numeroita uusille aikaisemmin merkkijonossa esiintyneille paikoille.
                else {
                    ch[a] = '\0';         //kun jokin merkki ei ole numeraalinen merkki, niin tulostetaan sen paalle lopetusmerkki '\0'.
                    return;
                }
            } 
        } else if (ch[i] == '\0' || (isdigit(ch[i+1]) && (ch[i] == '.' || ch[i] == '-') )){//jos huomataan merkkijonon paattyneen ennen ensinmaisenkaan numeraalisen merkin loytymista.. (tai jos huomataan kayttajan yritteneen syottaa <1, float point luku(tai negatiivinen luku), niin..)
            ch[0] = '\0';   //asetetaan merkkijonon alkuun lopetusmerkki, josta alempi funktio huomaa etta merkkijonosta ei saatu numeroa.
            return;
        }
    }
}
















/* Tämä versio näkee pisteet('.'), vain "ei numeeraalisina merkkeinä" */
/*jos merkkijonon ensinmanen merkki ei ole numero niin koitetaan etsia merkkionosta numeroa. Jos numero loytyy niin siirretaan se merkkijonon alkuun
void etsiPosInt(char ch[], unsigned int pituus){//ihan vain karsimassa kayttajan kirjoitusvirheita. esim jos kayttaja tarkoitti syottaa luvun "2019" ja vahingossa syotti "dwadwadaw joo 2019 jee !!1!111!!!", niin tama funktio korjaa sen.
    for(int i = 0; i < pituus ; i++) {
        if (isdigit(ch[i])) { //jos merkki on numeraalinen niin ruvetaan kasittelemaan merkkiojnoa seuraavanlaisesti
            for(int a = 0; a+i < pituus; a++){           //siirrytaan tahan for loopiin jossa siirretaan numeroita merkkijonon alkuun kunnes numerot loppuu tai merkkijonon pituus loppuu.
                if (isdigit(ch[a+i])) ch[a] = ch[a+i];    //tallennetaan merkkijonon numeroita uusille aikaisemmin merkkijonossa esiintyneille paikoille.
                else {
                    ch[a] = '\0';         //kun jokin merkki ei ole numeraalinen merkki, niin tulostetaan sen paalle lopetusmerkki '\0'.
                    i = pituus;
                }
            } 
        } else if (ch[i] == '\0' || ( ch[i] == '-' && isdigit(ch[i+1]) )){//jos huomataan merkkijonon loppuneen TAI käyttäjän syöttämän luvun olevan negatiivinen, niin ei hyväksytä sitä ja lopetetaan merkkijonon käsittely
            ch[0] = '\0';   //asetetaan merkkijononalkuun lopetusmerkki, josta alempi funktio huomaa etta merkkijonosta ei saatu numeroa.
            return;
        }   
    }
}*/











/* Vanha versio */
/* unsigned int kysyPosInt(unsigned int minVal, unsigned long long maxVal){
    //if(maxVal == ULONG_LONG_MAX) maxVal--;  //lisäisi virheen sietoa, mutta koska käyttäjä ei kuitenkaan maxVal arvoa niin ei oikeastaan tarvetta tälle.
    unsigned long long syote = maxVal+1;
    int maxPituus = 50;
    char ch[maxPituus]; 
    do{
        syote = 0;
        //scanf("%[^\n]*s", ch, maxPituus-1);        //toimii muuten, paitsi muuttaa chn merkit tyhjiksi jos kayttajan syotto liian pitka
        scanf("%49[^\n]s", ch);
        while(fgetc(stdin) != '\n'); 
        etsiPosKokonaisluku(ch, maxPituus);
        if (ch[0] != '\0') 
            {syote = strtoull(ch, NULL, 10);}
        
        if (syote < minVal || syote > maxVal || ch[0] == '\0')
        {printf("%sSyoton tulee olla kokonaisluku valilta %u-%llu.%s\n\n", YEL, minVal, maxVal, NRM);}
        else printf("\n");
    }while(syote < minVal || syote > maxVal || ch[0] == '\0');
    return syote;
} */