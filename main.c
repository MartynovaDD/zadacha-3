#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <float.h>
void AutoTest(void);
int func(FILE* restrict);

void AutoTest(void){
    FILE* input_file;
    FILE* output_file;
    int m = 0;
    input_file=fopen("test.txt", "r");
    func(input_file);
    fclose(input_file);
    output_file=fopen("data.txt", "r");
    fscanf(output_file, "%d", &m);
    fclose(output_file);
    if (m == 1){
        printf("Autotest passed\n");
    }
    else{
        printf("Autotest failed\n");
    }
}




int func(FILE* input_file){
    FILE* output_file;
    char s[2];
    int** a;
    int* temp;
    int m=0, n=0, flag=0, f=0, fl=0, k=0, i=0, num=0, v = 0, fR = 0;
    int max = DBL_MIN;
    if (!input_file){
        printf("Error! Cannot open file !\n");
        return -1;
    }
    else{
        if (fscanf(input_file, "%d\n", &num)!=1){
            printf("Error! Cannot read data from test.txt\n");
            fclose(input_file);
            return -1;
        }
        else{
            num=0;
            rewind(input_file);
            while (flag==0){
                if (fscanf(input_file, "%c", &s[0])==1){
                    if(isdigit(s[0])==1){
                        f=1;
                    }
                    if(((s[0]==' ') || (s[0]=='\n'))&& (f==1)){
                        k++;
                        num++;
                        f=0;
                    }
                    if(s[0]=='\n'){
                        m++;
                        if(k>=n){
                            n=k;
                        }
                        k=0;
                    }
                }
                else{
                    flag=1;
                    num++;
                    k++;
                    if(k>=n){
                        n=k;
                    }
                }
            }
            m++;
            a = (int**)malloc(m * sizeof(int*));
            for (int ii=0; ii<m; ii++){
                a[ii]=(int*)malloc((n+1)*sizeof(int));
            }
            flag=0;
            k=0;
            rewind(input_file);
            while (flag==0){
                if (fscanf(input_file, "%c", &s[0])==1){
                    if(isdigit(s[0])==1){
                        f=1;
                    }
                    if(((s[0]==' ') || (s[0]=='\n'))&& (f==1)){
                        k++;
                        f=0;
                    }
                    if(s[0]=='\n'){
                        a[i][0]=k;
                        i++;
                        k=0;
                    }
                }
                else{
                    flag=1;
                    k++;
                    a[i][0]=k;
                }
            }
            rewind(input_file);
            for (i=0; i<m; i++){
                for (int j=1; j<=a[i][0]; j++){
                    fscanf(input_file, "%d", &a[i][j]);
                }
            }
            flag=0;
            f=0;


            for (i=0; i<m; i++){
                if(i==0){
                    for (int j=1; j<=a[i][0]; j++){
                        if(a[0][j] > max){
                                max = a[0][j];
                                fR = j;
                        }
                    }
                }
                else{
                    for (int j=1; j<=a[i][0]; j++){
                            if(a[i][j] > max){
                                max = a[i][j];
                                v = j;
                            }
                    }
                    if (v!=fR){
                    fl = 1;
                    }
                }
                max = DBL_MIN;
            }
            if (fl == 0){
                    for (int i=0; i < m; i++){
                        for(int j = fR; j < a[i][0]; j++){
                            a[i][j] = a[i][j+1];
                        }
                        temp = (int*)realloc(a[i], (n)*sizeof(int));
                        if(temp){
                            a[i]=temp;
                        }
                    }
                    for (int i=0; i < m; i++){
                        a[i][0] = a[i][0]-1;
                    }
            }
            output_file=fopen("data.txt", "w");
            for (i=0; i<m; i++){
                for (int j=1; j<=a[i][0]; j++){
                    printf("%d ", a[i][j]);
                    fprintf(output_file,"%d ", a[i][j]);
                }
                printf("\n");
                fprintf(output_file,"\n");
            }
            fclose(output_file);
            for (int ii=0; ii<m; ii++){
                free(a[ii]);
            }
            free(a);
            return 1;
        }
    }
}



int main(void){
    FILE* input_file;
    input_file=fopen("file.txt", "r");
    AutoTest();
    func(input_file);
    fclose(input_file);
    return 0;
}

