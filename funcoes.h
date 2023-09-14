#ifndef FUNCOES_H
#define FUNCOES_H

float modulo(float *);
float produtoInterno(float *, float *);
void produtoVetorial(float *, float *, float *);
void equacoesParametricas(float, float, float, float, float, float, float, float, float, float, float, float, float, float);
void distanciaPontoPonto(float, float, float, float, float, float, float);
void distanciaPontoReta(float, float, float, float, float, float, float, float, float, float);
void projecaoDoPontoVetor(float *, float *, float *, float *);
void subtraiVetor(float *, float *, float *);
void criaVetorDiretor(float *, float *, float *,float *);
void intersecaoVetorPlano(float *, float *, float *);
void criaPlanoGeral(float *, float *, float *, float *, float *, float *);
char* equacaoGeral(float *, float *);
void pegaVetorNormal(const char *, float *);
void projecaoDoPontoPlano(float *, float *, float *, float *); 

#endif