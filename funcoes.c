#include <ctype.h> 
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

float modulo(float ponto[])
{
   return sqrt(pow(ponto[0], 2) + pow(ponto[1], 2) + pow(ponto[2], 2));
}

float produtoInterno(float vetor1[], float vetor2[])
{
   return vetor1[0] * vetor2[0] + vetor1[1] * vetor2[1] + vetor1[2] * vetor2[2];
}

void produtoVetorial(float vetor1[], float vetor2[], float resultante[])
{
   resultante[0] = vetor1[1] * vetor2[2] - vetor1[2] * vetor2[1];
   resultante[1] = vetor1[2] * vetor2[0] - vetor2[2] * vetor1[0];
   resultante[2] = vetor1[0] * vetor2[1] - vetor1[1] * vetor2[0];
}

void equacoesParametricas(float x0, float y0, float z0, float h, float a0, float b0, float c0, float t, float a1, float b1, float c1, float x, float y, float z)
{
   x = x0 + a0 * h + a1 * t;
   y = y0 + b0 * h + b1 * t;
   z = z0 + c0 * h + c1 * t;
}

void distanciaPontoPonto(float x0, float y0, float z0, float x1, float y1, float z1, float d)
{
   d = sqrt(pow(x1-x0, 2) + pow(y1 - y0, 2) + pow(z1 - z0, 2));
}

/*void distanciaPontoReta(float x0, float y0, float z0, float x1, float y1, float z1, float a, float b, float c, float d)
{  
   float m1, m2, i, j, k;
   produtoVetorial(a, b, c, x1-x0, y1-y0, z1-z0, i, j, k);
   modulo(i, j, k, m1);
   modulo(a, b, c, m2);
   d = m1 / m2;
}*/

//Função para calcular o ponto de um vetor mais próximo a um ponto no espaço
void projecaoDoPontoVetor(float vetor1[], float vetor2[], float vetor3[], float resultante[])
{
   //vetor1 = Ponto na reta, vetor2 = vetor diretor, ponto fora da reta
   // Cálculo do valor do escalar para o ponto mais próximo
   float escalar = (vetor2[0] * (vetor1[0] - vetor3[0]) + vetor2[1] * (vetor1[1] - vetor3[1]) + vetor2[2]*(vetor1[2]- vetor3[2])) 
   / (vetor2[0] * vetor2[0] + vetor2[1] * vetor2[1] + vetor2[2] * vetor2[2]);

   // Cálculo das coordenadas do ponto na reta, mais próximo de P
   resultante[0] = vetor3[0] + vetor2[0] * escalar;
   resultante[1] = vetor3[1] + vetor2[1] * escalar;
   resultante[2] = vetor3[2] + vetor2[2] * escalar;
}

void subtraiVetor(float vetor1[], float vetor2[], float resultante[])
{
   resultante[0] = vetor2[0] - vetor1[0];
   resultante[1] = vetor2[1] - vetor1[1];
   resultante[2] = vetor2[2] - vetor1[2];
}

//Função para criar uma representção segmentária do vetor diretor no espaço
void criaVetorDiretor(float vetor[], float pontoVetor[], float vInicio[], float vFim[]) 
{
   //multiplica o escalar -20 com o vetor incial
   vInicio[0] = pontoVetor[0] + vetor[0] * 20;
   vInicio[1] = pontoVetor[1] + vetor[1] * 20;
   vInicio[2] = pontoVetor[2] + vetor[2] * 20;
   //multiplica o escalar 20 com o vetor final
   vFim[0] = pontoVetor[0] + vetor[0] * -20;
   vFim[1] = pontoVetor[1] + vetor[1] * -20;
   vFim[2] = pontoVetor[2] + vetor[2] * -20;
}

void intersecaoVetorPlano(float vetorNormal[3], float pontoPlano[3], float intersecao[3]) 
{
   float escalar = (vetorNormal[0] * pontoPlano[0] + vetorNormal[1] * pontoPlano[1] + vetorNormal[2] * pontoPlano[2]) 
   / (vetorNormal[0]*vetorNormal[0] + vetorNormal[1]*vetorNormal[1] + vetorNormal[2]*vetorNormal[2]);

   intersecao[0] = escalar * vetorNormal[0];
   intersecao[1] = escalar * vetorNormal[1];
   intersecao[2] = escalar * vetorNormal[2];
}

float tamanho(float A[3])
{
   return sqrt(A[0]*A[0] + A[1]*A[1] + A[2]*A[2]);
}

void escala(float A[3], float escala)
{
   for(int i = 0; i < 3; i++) 
   {
      A[i] *= escala;
   }
}

void criaPlanoGeral(float vetorNormal[], float pontoPlano[], float ponto1[], float ponto2[], float ponto3[], float ponto4[]) 
{
   float B[3] = {1.0, 0.0, 0.0};
   float C[3], D[3];

   if(vetorNormal[0] == 1.0 && vetorNormal[1] == 0.0 && vetorNormal[2] == 0.0)
   {
      B[0] = 0.0; 
      B[1] = 1.0;
   }

   produtoVetorial(vetorNormal, B, C);
   produtoVetorial(vetorNormal, C, D);

   float meio = 40.0 / 2.0;
   escala(C, meio/tamanho(C));
   escala(D, meio/tamanho(D));

   for(int i = 0; i < 3; i++)
   {
      ponto1[i] = pontoPlano[i] + C[i];
      ponto2[i] = pontoPlano[i] + D[i];
      ponto3[i] = pontoPlano[i] - C[i];
      ponto4[i] = pontoPlano[i] - D[i];
   }
}

void separaEquacao(const char *equacao, float *a, float *b, float *c, float *d) {
    char numBuffer[50] = {0};
    char varBuffer[10] = {0};
    int i = 0, numIndex = 0, varIndex = 0;
    char sign = '+';

    *a = *b = *c = *d = 0;

    for (i = 0; i <= strlen(equacao); ++i) {
        if (isdigit(equacao[i]) || equacao[i] == '.') {
            numBuffer[numIndex++] = equacao[i];
        } else if (isalpha(equacao[i])) {
            varBuffer[varIndex++] = equacao[i];
        } else if (equacao[i] == '+' || equacao[i] == '-' || equacao[i] == '=' || equacao[i] == '\0') {
            if (numIndex > 0 && varIndex > 0) {
                numBuffer[numIndex] = '\0';
                varBuffer[varIndex] = '\0';
                
                if (strcmp(varBuffer, "x") == 0) {
                    *a = atof(numBuffer) * (sign == '-' ? -1 : 1);
                } else if (strcmp(varBuffer, "y") == 0) {
                    *b = atof(numBuffer) * (sign == '-' ? -1 : 1);
                } else if (strcmp(varBuffer, "z") == 0) {
                    *c = atof(numBuffer) * (sign == '-' ? -1 : 1);
                }

                memset(numBuffer, 0, sizeof(numBuffer));
                memset(varBuffer, 0, sizeof(varBuffer));
                numIndex = 0;
                varIndex = 0;
            } else if (numIndex > 0 && varIndex == 0) {
                numBuffer[numIndex] = '\0';
                *d = atof(numBuffer) * (sign == '-' ? -1 : 1);
                
                memset(numBuffer, 0, sizeof(numBuffer));
                numIndex = 0;
            }
            if (equacao[i] == '+' || equacao[i] == '-') {
                sign = equacao[i];
            }
        }
    }
}

/*char* equacaoGeral(float ponto[3], float vNormal[3]) 
{
   char equacao[30], temp[30];

   // Cálculo do termo D
   float D = -((vNormal[0] * ponto[0]) + (vNormal[1] * ponto[1]) + (vNormal[2] * ponto[2]));
   
   // Constrói a equação levando em conta os sinais
   sprintf(equacao, "%.2fx ", vNormal[0]);

   if (B >= 0) {
      sprintf(temp, "+ %.2fy ", vNormal[1]);
   } else {
      sprintf(temp, "- %.2fy ", -vNormal[1]);
   }
   strcat(equacao, temp);

   if (C >= 0) {
      sprintf(temp, "+ %.2fz ", vNormal[2]);
   } else {
      sprintf(temp, "- %.2fz ", -vNormal[2]);
   }
   strcat(equacao, temp);
   
   if (D >= 0) {
      sprintf(temp, "+ %.2f ", D);
   } else {
      sprintf(temp, "- %.2f ", -D);
   }
   strcat(equacao, temp);
   
   strcat(equacao, "= 0");
   
   return equacao;
}*/

