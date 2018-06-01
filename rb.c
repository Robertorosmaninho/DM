#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){

char Reflex;
char Irreflex;
char Simetri;
char Anti_s;
char Assime;
char Trans;

//Abre o Arquivo
FILE *entrada = fopen(argv[1], "r");

//Testa se o arquivo existe
  if(entrada == NULL){
    printf("Arquivo não pode ser aberto!\n");
    exit(1);
  }

//Le o tamanho do Conjunto R
int tamanho;
fscanf(entrada, "%d", &tamanho);

//Le os elementos do Conjunto R
int *Conjunto_R = (int *)calloc(tamanho, sizeof(int));
if(Conjunto_R == NULL){
  printf("Sem memória para conjunto R\n");
}
for(int i = 0; i < tamanho; i++){
  fscanf(entrada, "%d", &Conjunto_R[i]);
}

//Cria Matriz Principal de tamanho_m
int **MATRIZ_PRINCIPAL = (int **)calloc(tamanho, sizeof(int *));
for(int i = 0; i < tamanho; i++){
  MATRIZ_PRINCIPAL[i] = (int *)calloc(tamanho, sizeof(int));
}
if(MATRIZ_PRINCIPAL == NULL){
  printf("Sem memória para Matriz Principal\n");
}

//Le todas as relacoes do arquivo e armazena na matriz principal
int x, y;
while (!feof(entrada)) {
  fscanf(entrada,"%d %d", &x, &y);
  for(int i = 0; i < tamanho; i++){
    if(Conjunto_R[i] == x){
      x = i;
    }
    if(Conjunto_R[i] == y){
      y = i;
    }
  }
  MATRIZ_PRINCIPAL[x][y] = 1;
}

//Cria Matriz Auxiliar de maior tamanho possivel (tamanho*tamanho)
int **MATRIZ_AUXILIAR = (int **)calloc(tamanho*tamanho, sizeof(int *));
for(int i = 0; i < tamanho*tamanho; i++){
  MATRIZ_AUXILIAR[i] = (int *)calloc(2, sizeof(int));
}
if(MATRIZ_PRINCIPAL == NULL){
  printf("Sem memória para Matriz Auxiliar\n");
}

printf("Propriedades\n");

//Teste de Reflexiva
int aux = 0, aux2 = 0, j = 0;

for(int i = 0; i < tamanho; i++){
  if(MATRIZ_PRINCIPAL[i][i] == 1){
    aux++;
  }
}

int inicio = 0;

if(aux == tamanho){
  Reflex = 'V';
  Irreflex = 'F';
}else if(aux == 0){
  Irreflex = 'V';
  Reflex = 'F';
}else{
  Irreflex = 'F';
  Reflex = 'F';

  for(int i = 0; i < tamanho; i++){
    if(MATRIZ_PRINCIPAL[i][i] == 1){
      MATRIZ_AUXILIAR[aux2][j] = Conjunto_R[i];
      MATRIZ_AUXILIAR[aux2][j+1] = Conjunto_R[i];
      aux2++;
    }
  }

  inicio = aux2;

  for(int i = 0; i < tamanho; i++){
    if(MATRIZ_PRINCIPAL[i][i] == 0){
      MATRIZ_AUXILIAR[aux2][j] = Conjunto_R[i];
      MATRIZ_AUXILIAR[aux2][j+1] = Conjunto_R[i];
      aux2++;
    }
  }
}

//Saida Reflexiva e Irreflexiva
if(Reflex == 'V' && Irreflex == 'F'){
  printf("1. Reflexiva: %c\n", Reflex);
  printf("2. Irreflexiva: %c\n", Irreflex);
  printf("    ");
  for(int i = 0; i < tamanho; i++){
    printf("(%d,%d); ", Conjunto_R[i], Conjunto_R[i]);
  }
  printf("\n");
}else if(Reflex == 'F' && Irreflex == 'V'){
  printf("1. Reflexiva: %c\n", Reflex);
    printf("    ");
  for(int i = 0; i < tamanho; i++){
    printf("(%d,%d); ", Conjunto_R[i], Conjunto_R[i]);
  }
  printf("\n");
  printf("2. Irreflexiva: %c\n", Irreflex);
}else{
  printf("1. Reflexiva: %c\n", Reflex);
  printf("    ");
  for(int i = inicio; i < tamanho; i++){
    printf("(%d,%d); ", MATRIZ_AUXILIAR[i][j], MATRIZ_AUXILIAR[i][j+1]);
  }
  printf("\n");
  printf("2. Irreflexiva: %c\n", Irreflex);
  printf("    ");
  for(int i = 0; i < inicio; i++){
    printf("(%d,%d); ", MATRIZ_AUXILIAR[i][j], MATRIZ_AUXILIAR[i][j+1]);
  }
  printf("\n");
}

//Fecho reflexivo
j = 0;
int **FECHO_REFLEXIVO = (int **)calloc(tamanho, sizeof(int *));
for(int i = 0; i < tamanho; i++){
  FECHO_REFLEXIVO[i] = (int *)calloc(2, sizeof(int));
}

for(int i = 0; i < tamanho; i++){
  FECHO_REFLEXIVO[i][j] = Conjunto_R[i];
  FECHO_REFLEXIVO[i][j+1] = Conjunto_R[i];
}

//Fecho Simetrico
aux = 0;
for(int i = 0; i < tamanho; i++){
  for(j = 0; j < tamanho; j++){
    if((MATRIZ_PRINCIPAL[i][j] == 1 && MATRIZ_PRINCIPAL[j][i] == 0 )||(MATRIZ_PRINCIPAL[i][j] == 1 && MATRIZ_PRINCIPAL[j][i] == 1)||(MATRIZ_PRINCIPAL[i][j] == 0 && MATRIZ_PRINCIPAL[j][i] == 1)){
      aux++;
    }
  }
}
int Simetrica=aux;

int **FECHO_SIMETRICO = (int **)calloc(Simetrica, sizeof(int *));
for(int i = 0; i < Simetrica; i++){
  FECHO_SIMETRICO[i] = (int *)calloc(2, sizeof(int));
}
aux = 0, aux2 = 0;
for(int i = 0; i < tamanho; i++){
  for(j = 0; j < tamanho; j++){
    if((MATRIZ_PRINCIPAL[i][j] == 1 && MATRIZ_PRINCIPAL[j][i] == 0 )||(MATRIZ_PRINCIPAL[i][j] == 1 && MATRIZ_PRINCIPAL[j][i] == 1)||(MATRIZ_PRINCIPAL[i][j] == 0 && MATRIZ_PRINCIPAL[j][i] == 1)){
      FECHO_SIMETRICO[aux][aux2] = Conjunto_R[i];
      FECHO_SIMETRICO[aux][aux2+1] = Conjunto_R[j];
      aux++;
    }
  }
}


//Simetria
aux = 0, aux2=0;
for(int i = 0; i < tamanho; i++){
  for(j = 0; j < tamanho; j++){
    if((MATRIZ_PRINCIPAL[i][j] == 0 && MATRIZ_PRINCIPAL[j][i] == 1)){
      MATRIZ_AUXILIAR[aux][aux2] = Conjunto_R[i];
      MATRIZ_AUXILIAR[aux][aux2+1] = Conjunto_R[j];
      aux++;
    }
  }
}

j = 0;
if(aux == 0){
  Simetri = 'V';
  printf("3. Simétrica: %c\n", Simetri);
}else{
  Simetri = 'F';
  printf("3. Simétrica: %c\n", Simetri);
  printf("    ");
  for(int i = 0; i < aux; i++){
    printf("(%d, %d);", MATRIZ_AUXILIAR[i][j], MATRIZ_AUXILIAR[i][j+1]);
  }
  printf("\n");
}


//Anti-Simetria
aux = 0, aux2 = 0;
int aux4 = 0;

for(int i = 0; i < tamanho; i++){
  for(j = 0; j < tamanho; j++){
    if((MATRIZ_PRINCIPAL[i][j] == 1 && MATRIZ_PRINCIPAL[j][i] == 1)){
      if(Conjunto_R[i] == Conjunto_R[j]){
        aux++;
      }else{
        MATRIZ_AUXILIAR[aux2][aux4] = Conjunto_R[i];
        MATRIZ_AUXILIAR[aux2][aux4+1] = Conjunto_R[j];
        aux2++;
      }
    }
  }
}
int aux3 = 0;
if(aux2 == 0){
  Anti_s = 'V';
  printf("4. Anti-simétrica: %c\n", Anti_s);
}else{
  Anti_s = 'F';
  printf("4. Anti-simétrica: %c\n", Anti_s);
  printf("    ");
  for (int i = 0; i < aux2; i++) {
    if(MATRIZ_AUXILIAR[i][aux4] != -1 && MATRIZ_AUXILIAR[i][aux4+1] != -1){
    printf("(%d,%d) e ", MATRIZ_AUXILIAR[i][aux4], MATRIZ_AUXILIAR[i][aux4+1]);
    for(int k = 0; k < aux2; k++){
      if(MATRIZ_AUXILIAR[i][aux4+1] == MATRIZ_AUXILIAR[k][aux4]){
        printf("(%d,%d); ", MATRIZ_AUXILIAR[k][aux4], MATRIZ_AUXILIAR[k][aux4+1]);
        MATRIZ_AUXILIAR[k][aux4] = -1;
        MATRIZ_AUXILIAR[k][aux4+1] = -1;
        break;
      }
    }
    MATRIZ_AUXILIAR[i][aux4] = -1;
    MATRIZ_AUXILIAR[i][aux4+1] = -1;
    }
  }
  printf("\n");
}

//Assimetria
if(Irreflex == 'V' && Anti_s == 'V'){
  Assime = 'V';
}else{
  Assime = 'F';
}
printf("5. Assimétrica: %c\n", Assime);

//Fecho Transitivo

int **FECHO_TRANSITIVO = (int **)calloc(tamanho, sizeof(int *));
int **MATRIZ_AUXILIAR2 = (int **)calloc(tamanho, sizeof(int *));

for(int i = 0; i < tamanho; i++){
  FECHO_TRANSITIVO[i] = (int *)calloc(tamanho, sizeof(int));
  MATRIZ_AUXILIAR2[i] = (int *)calloc(tamanho, sizeof(int));
    for(int j = 0; j < tamanho; j++){
      FECHO_TRANSITIVO[i][j] = MATRIZ_PRINCIPAL[i][j];
      MATRIZ_AUXILIAR2[i][j] = MATRIZ_PRINCIPAL[i][j];
    }
}

int b = tamanho;

while(b--){
  for(int i = 0; i < tamanho; i++){
    for(int j = 0; j < tamanho; j++){
      for(int l = 0; l < tamanho; l++){
        MATRIZ_AUXILIAR2[i][j] += FECHO_TRANSITIVO[i][l] * MATRIZ_PRINCIPAL[l][j];
      }
    }
  }

  for(int i = 0; i < tamanho; i++){
    for(int j = 0; j < tamanho; j++){
      FECHO_TRANSITIVO[i][j] = MATRIZ_AUXILIAR2[i][j];
    }
  }

}
aux=0;
for(int i = 0; i < tamanho; i++){
  for(int j = 0; j < tamanho; j++){
    if(FECHO_TRANSITIVO[i][j] && !MATRIZ_PRINCIPAL[i][j]){
      aux++;
    }
  }
}

//Transitividade
if(aux){
  Trans = 'F';
  printf("6. Transitiva: %c\n", Trans);
  printf("    ");
  for(int i = 0; i < tamanho; i++){
    for(int j = 0; j < tamanho; j++){
      if(FECHO_TRANSITIVO[i][j] && !MATRIZ_PRINCIPAL[i][j]){
        printf("(%d, %d); ", Conjunto_R[i], Conjunto_R[j]);
      }
    }
  }
  printf("\n");
}else{
  Trans = 'V';
  printf("6. Transitiva: %c\n", Trans);
}

printf("\n");

//Relaçao de Equivalencia
if(Reflex == 'V' && Simetri == 'V' && Trans == 'V'){
  printf("Relação de equivalência: V\n");
}else{
  printf("Relação de equivalência: F\n");
}


//Relacao de Ordem Parcial
if(Reflex == 'V' && Anti_s== 'V' && Trans == 'V'){
  printf("Relação de ordem parcial: V\n");
}else{
  printf("Relação de equivalência: F\n");
}

printf("\n");

//Imprimir Fechos
j = 0;
printf("Fecho reflexivo da relação = {");
for(int i = 0; i < tamanho; i++){
  if(i > 0){printf(",");}
  printf("(%d,%d)", FECHO_REFLEXIVO[i][j], FECHO_REFLEXIVO[i][j+1]);
}
printf("}\n");

printf("Fecho simétrico da relação = {");
for(int i = 0; i < Simetrica; i++){
  if(i > 0){printf(",");}
  printf("(%d,%d)", FECHO_SIMETRICO[i][j], FECHO_SIMETRICO[i][j+1]);
}
printf("}\n");

printf("Fecho transitivo da relação = {");
for(int i = 0; i < tamanho; i++){
  for(int j = 0; j < tamanho; j++){
    if(FECHO_TRANSITIVO[i][j]){
      if(i > 0){printf(",");}
      printf("(%d,%d)", Conjunto_R[i], Conjunto_R[j]);
    }
  }
}
printf("}\n");

//Libera os calloc da matriz principal
for(int i = 0; i < tamanho; i++){
  free(MATRIZ_PRINCIPAL[i]);
  free(FECHO_REFLEXIVO[i]);
  free(MATRIZ_AUXILIAR2[i]);
  free(FECHO_TRANSITIVO[i]);

}
free(MATRIZ_PRINCIPAL);
free(FECHO_REFLEXIVO);
free(MATRIZ_AUXILIAR2);
free(FECHO_TRANSITIVO);

for(int i = 0; i < tamanho*tamanho; i++){
  free(MATRIZ_AUXILIAR[i]);
}
free(MATRIZ_AUXILIAR);

for(int i = 0; i < Simetrica; i++){
  free(FECHO_SIMETRICO[i]);
}
free(FECHO_SIMETRICO);

  return 0;
}
