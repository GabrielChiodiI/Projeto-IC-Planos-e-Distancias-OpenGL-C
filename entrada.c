#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "opcoes.h"

char textoTemporario[20], texto[20];
int cursorPos = 0;
int ativa = 0; 
float anguloX = 0.0, anguloY = 0.0;
float zoom = 1.0;
bool mousePressionado = false;
int mouseXAnterior, mouseYAnterior;


void desenhaCaixaDeTextoAtiva() 
{
   glColor3f(1.0, 1.0, 1.0); // cor branca
   glBegin(GL_QUADS);
      glVertex2f(-50, 45);
      glVertex2f(50, 45);
      glVertex2f(50, 55);
      glVertex2f(-50, 55);
   glEnd();

   glColor3f(0.0, 0.0, 0.0); // cor preta
   glRasterPos2f(-48, 50);
   for (int i = 0; i < cursorPos; i++)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, textoTemporario[i]);
}

void desenhaCaixaDeTextoInativa() 
{
   glColor4f(1.0, 1.0, 1.0, 0.9); // cor cinza
   glBegin(GL_QUADS);
      glVertex2f(-50, 45);
      glVertex2f(50, 45);
      glVertex2f(50, 55);
      glVertex2f(-50, 55);
   glEnd();
}

void teclado(unsigned char tecla, int x, int y)
{
   if (tecla == 13)
   {
      strcpy(texto, textoTemporario);
      memset(textoTemporario, 0, sizeof(textoTemporario));
      ativa = !ativa; 
   }else if (tecla == 8 && cursorPos > 0)
   { // Tecla BACKSPACE
      memmove(&textoTemporario[cursorPos - 1], &textoTemporario[cursorPos], strlen(textoTemporario) - cursorPos + 1);
      cursorPos--; // move the cursor position back
   } else if (tecla == 127 && cursorPos < strlen(textoTemporario)) // Tecla DELETE
      memmove(&textoTemporario[cursorPos], &textoTemporario[cursorPos + 1], strlen(textoTemporario) - cursorPos);
   else if (strlen(textoTemporario) < sizeof(textoTemporario) - 1 && (tecla >= 32 && tecla <= 126)) 
   { // only printable characters
      memmove(&textoTemporario[cursorPos + 1], &textoTemporario[cursorPos], strlen(textoTemporario) - cursorPos + 1);
      textoTemporario[cursorPos] = tecla;
      cursorPos++; // move the cursor position forward
   }
   glutPostRedisplay(); // Redesenha a janela
}

void tecladoEspecial(int tecla, int x, int y) 
{
   if (ativa)
   {
      if (tecla == GLUT_KEY_LEFT && cursorPos > 0) 
         cursorPos--; // move cursor position back
      else if (tecla == GLUT_KEY_RIGHT && cursorPos < strlen(textoTemporario))
         cursorPos++; // move cursor position forward
      glutPostRedisplay();
   }
}

void mouse(int button, int state, int x, int y) 
{
   if (button == GLUT_LEFT_BUTTON) 
   {
      if (state == GLUT_DOWN) 
      {
         mousePressionado = true;
         mouseXAnterior = x;
         mouseYAnterior = y;
      } else 
      {
         mousePressionado = false;
      }
   } else if (button == 3) 
   {
      zoom *= 1.1;
      glutPostRedisplay();
   } else if (button == 4) 
   {
      zoom /= 1.1;
      glutPostRedisplay();
   }
}

void mouseMove(int x, int y) 
{
   if (mousePressionado)
   {
      anguloY += (x - mouseXAnterior);
      anguloX += (y - mouseYAnterior);
      mouseXAnterior = x;
      mouseYAnterior = y;
      glutPostRedisplay();
   }
}