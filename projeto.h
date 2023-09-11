#ifndef PROJETO_H
#define PROJETO_H

typedef enum
{
    EQUACAO_GERAL_DO_PLANO,
    POR_PONTO_VETOR_NORMAL,
    POR_PONTO_2_VETORES,
    DOIS_PONTOS,
    PONTO_RETA,
    PONTO_PLANO,
    DUAS_RETAS,
    RETA_PLANO,
    DOIS_PLANOS,
    NENHUM,
} SubItemSelecionado;

extern SubItemSelecionado subItemAtual;
extern int subJanela2;

#endif