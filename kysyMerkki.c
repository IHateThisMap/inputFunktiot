//palauttaa merkin. "Jatkaa" merkin syöttämisen odottelemista siinä tapauskessa jos käyttäjä vain painaa entteriä.
char lueMerkki(){
    char painettuNappi;
    do {painettuNappi = getchar();}
    while (painettuNappi == '\n'); 

    while (fgetc(stdin) != '\n');     //tyhjentää input bufferin
    return (painettuNappi);
}