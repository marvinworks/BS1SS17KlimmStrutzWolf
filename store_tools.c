#include <string.h>
#include <stdbool.h>
#include "store_tools.h"

int get(char key[], char resp[]) {
    int substrLEN = strlen(key);
    char results[BUFSIZ];
    strcpy(resp, "");


    //WILDCARD CHECK
    if(strchr(key, '*') && strchr(key, '?')) {
        strcpy(resp, "Error on get: Do not combine ? and *.\n");
        return -1;
    }

    else if (strchr(key, '*')) {

        //Ascii Nummer für * = 42
        if (key[0] == 42) {
            key++;
            substrLEN = strlen(key);
            //printf("Substring: %s\n", key);

            for (int i = STORELENGTH-1; i >= 0; i--) {
                //printf("Index %i: %s\n", i, kv[i].key);
                int storestrLEN = strlen(kv[i].key);
                if(substrLEN > 0) {
                    if (storestrLEN >= substrLEN) {
                        //printf("Index %i: %s\n", i, kv[i].key);
                        for (int j = 1; j <= strlen(key); j++) {

                            if (kv[i].key[storestrLEN-j] != key[substrLEN-j]) {
                                break;
                            }
                            //printf("%c\n", kv[i].key[storestrLEN-j]);

                            //hinzufuegen zu results
                            if(j == substrLEN) {
                                strcat(resp, kv[i].value);
                                strcat(resp, "\n");
                            }
                        }
                    }
                }
                //um mit dem befehl "*" alles ausgeben zu lassen
                else {
                    if(strlen(kv[i].value)>0) {
                        strcat(resp, kv[i].value);
                        strcat(resp, "\n");
                    }
                }
            }
        }

        else {
            key[substrLEN-1] = 0;
            substrLEN = strlen(key);
            //printf("Substring: %s\n", key);

            for (int i = STORELENGTH-1; i >= 0; i--) {

                int storestrLEN = strlen(kv[i].key);
                if(substrLEN > 0) {
                    if (storestrLEN >= substrLEN) {
                        for (int j = 0; j < strlen(key); j++) {

                            if (kv[i].key[j] != key[j]) {
                                break;
                            }

                            //hinzufuegen zu results
                            if(j == substrLEN-1) {
                                //printf("Index %i: %s\n", i, kv[i].key);
                                strcat(resp, kv[i].value);
                                strcat(resp, "\n");
                            }
                        }
                    }
                }
            }
        }


        return 1;
    }

    else if (strchr(key, '?')) {
        //printf("String enthaelt ein ?\n");

        //Ascii Nummer für ? = 63
        if (key[0] == 63) {
            key++;
            substrLEN = strlen(key);
            //printf("Substring: %s\n", key);

            for (int i = STORELENGTH-1; i >= 0; i--) {
                //printf("Index %i: %s\n", i, kv[i].key);
                int storestrLEN = strlen(kv[i].key);
                if(substrLEN > 0) {
                    if (storestrLEN == substrLEN+1) {
                        //printf("Index %i: %s\n", i, kv[i].key);
                        for (int j = 1; j <= strlen(key); j++) {

                            if (kv[i].key[storestrLEN-j] != key[substrLEN-j]) {
                                break;
                            }
                            //printf("%c\n", kv[i].key[storestrLEN-j]);

                            //hinzufuegen zu results
                            if(j == substrLEN) {
                                strcat(resp, kv[i].value);
                                strcat(resp, "\n");
                            }
                        }
                    }
                }
                    //um mit dem befehl "?" alles ausgeben zu lassen
                else {
                    if(strlen(kv[i].value) > 0 && strlen(kv[i].key) == 1) {
                        strcat(resp, kv[i].value);
                        strcat(resp, "\n");
                    }
                }
            }
        }

        else {
            key[substrLEN-1] = 0;
            substrLEN = strlen(key);
            //printf("Substring: %s\n", key);

            //HIER
            for (int i = STORELENGTH-1; i >= 0; i--) {

                int storestrLEN = strlen(kv[i].key);
                if(substrLEN > 0) {
                    if (storestrLEN == substrLEN+1) {
                        for (int j = 0; j < strlen(key); j++) {

                            if (kv[i].key[j] != key[j]) {
                                break;
                            }

                            //hinzufuegen zu results
                            if(j == substrLEN-1) {
                                //printf("Index %i: %s\n", i, kv[i].key);
                                strcat(resp, kv[i].value);
                                strcat(resp, "\n");
                            }
                        }
                    }
                }
            }
        }

        return 1;
    }

    else {
        for (int i = 0; i < STORELENGTH; i++) {
            if (strcmp(kv[i].key, key) == 0) {
                //strcpy(resp, "Der gesuchte Value ist '");
                //strcat(resp, kv[i].value);
                //strcat(resp, "'.\n");
                strcpy(resp, kv[i].value);
                strcat(resp, "\n");
                return 1;
            }
        }
    }

    strcpy(resp, "Error on get: Key not found.\n");
    return -1;
}


int put(char key[], char value[], char resp[]) {
    int emptyIndex = -1;
    strcpy(resp, "");
    for (int i = 0; i < STORELENGTH; i++) {
        // Falls der Key existiert: Ueberschreiben, alten Wert zurueckgeben und return true
        if (strcmp(kv[i].key, key) == 0) {
            //Clientausgabe
            strcpy(resp, "Beim Key '");
            strcat(resp, kv[i].key);
            strcat(resp, "' wird der Value '");
            strcat(resp, kv[i].value);
            strcat(resp, "' mit dem Value '");
            strcat(resp, value);
            strcat(resp, "' überschrieben.\n");


            strcpy(kv[i].value, value);
            return 1;
        }
        // Einen leeren Index aufheben, falls der Key nicht existiert
        if(strcmp(kv[i].key,"") == 0){
        emptyIndex = i;
        }

    }

    // Wenn es einen leeren Index gab, dort rein speichern.
    //TODO: Abfrage, ob die Stelle an Emptyindex noch da ist!
    if (emptyIndex > -1) {
        strcpy(kv[emptyIndex].key, key);
        strcpy(kv[emptyIndex].value, value);

        //Clientausgabe
        strcpy(resp, "Der Key '");
        strcat(resp, key);
        strcat(resp, "' mit dem Value '");
        strcat(resp, value);
        strcat(resp, "' wird eingefügt.\n");
        return 1;
    }
    strcpy(resp, "Error on put: Action not successfull\n");
    return -1;
}


int delete(char key[], char resp[]) {
    strcpy(resp, "");
    for (int i = 0; i < STORELENGTH; i++) {
        if (strcmp(kv[i].key, key) == 0) {
            //Clientausgabe
            strcpy(resp, "Der Key '");
            strcat(resp, kv[i].key);
            strcat(resp, "' mit dem Value '");
            strcat(resp, kv[i].value);
            strcat(resp, "' wird gelöscht.\n");

            strcpy(kv[i].value, "");
            strcpy(kv[i].key, "");
            return 0;
        }
    }

    strcpy(resp, "Error on delete: Key not found.\n");
    return -1;
}


int fillStore(char resp[]) {
    int respIT = 0;
    char tmpkey[BUFSIZ];
    char tmpval[BUFSIZ];
    char tempresp[BUFSIZ];
    while (true) {
        if(resp[respIT] == NULL){
            break;
        }
            while (resp[respIT] != NULL && resp[respIT] != 10) {
                char tmppush[2];
                tmppush[0] = resp[respIT];
                tmppush[1] = '\0';
                strcat(tmpkey, tmppush);
                respIT++;
        }
            respIT++;
            while (resp[respIT] != 10 && resp[respIT] != NULL) {
                char tmppush2 [2];
                tmppush2[0] = resp[respIT];
                tmppush2[1] = '\0';
                strcat(tmpval, tmppush2);
                respIT++;
            }
            respIT++;
            put(tmpkey, tmpval, tempresp);
            bzero(tmpkey, sizeof(tmpkey));
            bzero(tmpval, sizeof(tmpval));
    }
}


