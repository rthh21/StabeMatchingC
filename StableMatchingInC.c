// gr. 161 - pb. 6 - STAN MARIUS ANDREI 
/*
    Datele de intrare sunt "n", matricea prioritatilor firmelor si matricea prioritatilor candidatilor (intre cele 2 exista un \n).
    In fiecare matrice, prioritatile sunt asezate pe coloane, de sus in jos in ordinea dorintelor
    ----------------------------------------------------------------
    Complexitate: O(n^2)
    ----------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    // deschidem fisierele
    FILE *in = fopen("index.in","r");
    if (in == NULL) {
        printf("Nu s-a putut deschide fisierul index.in!\n");
        fclose(in);
        return 1;
    }
    FILE *out = fopen("index.out","w+");
    if (out == NULL) {
        printf("Nu s-a putut deschide fisierul index.in!\n");
        fclose(out);
        return 1;
    }
    
    //citim datele si alocam dinamic
    int n;
    fscanf(in,"%d",&n);
    int **firme = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        firme[i] = (int *)malloc(n * sizeof(int));
        if (firme[i] == NULL) {
            printf("Erroare la alocarea memoriei!\n");
            fclose(in);
            fclose(out);
            return 1;
        }
        for (int j = 0; j < n; j++) {
            char c;
            fscanf(in, " %c", &c);
            firme[i][j] = c - 'q';
        }
    }
    fseek(in, 1, SEEK_CUR);
    int **candidat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        candidat[i] = (int *)malloc(n * sizeof(int));
        if (candidat[i] == NULL) {
            printf("Erroare la alocarea memoriei!\n");
            fclose(in);
            fclose(out);
            return 1;
        }
        for (int j = 0; j < n; j++) {
            char c;
            fscanf(in, " %c", &c);
            candidat[i][j] = c - 'A';
        }
    }
    // initiaizam vectorii necesari
    int *freeS = (int *)malloc(n*sizeof(int));
    int *freeD = (int *)malloc(n*sizeof(int));
    if (freeS == NULL) {
        printf("Erroare la alocarea memoriei!\n");
        fclose(in);
        fclose(out);
        return 1;
    }
    if (freeD == NULL) {
        printf("Erroare la alocarea memoriei!\n");
        fclose(in);
        fclose(out);
        return 1;
    }
    for(int i=0;i<n;i++){
        freeS[i]=-1;
        freeD[i]=-1;
    }
    int *offset = (int *)calloc(n,sizeof(int));
    if (offset == NULL) {
        printf("Erroare la alocarea memoriei!\n");
        fclose(in);
        fclose(out);
        return 1;
    }
    // restul variabilelor necesare
    int firmeLibere = n;
    int j=0;
    
    //incepem stable matching-ul
    while(firmeLibere>0){
        int firmecnt;
        for(firmecnt=0;firmecnt<n;firmecnt++){
            if(freeS[firmecnt] == 1){
                offset[firmecnt]--;
            }else{
                if(freeD[firme[j+offset[firmecnt]][firmecnt]] == -1){
                    freeD[firme[j+offset[firmecnt]][firmecnt]] = firmecnt;
                    freeS[firmecnt] = 1;
                    firmeLibere--;
                }
                if(freeD[firme[j+offset[firmecnt]][firmecnt]] != -1){
                    int pozitiaDorita,pozitiaActuala=0;
                    for(pozitiaDorita=0;pozitiaDorita<n;pozitiaDorita++)
                        if(candidat[pozitiaDorita][firme[j+offset[firmecnt]][firmecnt]] == firmecnt)
                            break;
                    for(pozitiaActuala=0;pozitiaActuala<n;pozitiaActuala++)
                        if(candidat[pozitiaActuala][firme[j+offset[firmecnt]][firmecnt]] == freeD[firme[j+offset[firmecnt]][firmecnt]])
                            break;
                    if(pozitiaDorita < pozitiaActuala){
                        freeS[freeD[firme[j+offset[firmecnt]][firmecnt]]] = -1;
                        freeD[firme[j+offset[firmecnt]][firmecnt]] = firmecnt;
                        freeS[firmecnt] = 1;
                    }
                }
            }
        }  
        j++;
    }
    
    //printam in fisier rezultatele
    fprintf(out,"Candidat -> Firma\n");
    fprintf(out,"------------------\n");
    for (int i = 0; i < n; i++){
        fprintf(out,"%c        ->",'q'+i);
        fprintf(out,"    %c\n",'A' + freeD[i]);
    }
    
    //eliberam memoria si inchidem fisierele
    for (int i = 0; i < n; i++) {
        free(firme[i]);
    }
    free(firme);
    for (int i = 0; i < n; i++) {
        free(candidat[i]);
    }
    free(candidat);
    fclose(in);
    fclose(out);
    
    return 0;
}