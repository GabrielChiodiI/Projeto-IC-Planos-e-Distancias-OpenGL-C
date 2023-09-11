#ifndef ENTRADA_H
#define ENTRADA_H

extern int ativa;
extern char texto[20];
extern float anguloX, anguloY, zoom;

void desenhaCaixaDeTextoAtiva();
void desenhaCaixaDeTextoInativa();
void teclado(unsigned char, int, int);
void tecladoEspecial(int, int, int);
void mouse(int, int, int, int);
void mouseMove(int, int);

#endif