#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "entrada.h"
#include "desenho3D.h"
#include "projeto.h"
#include "opcoes.h"

int subJanela1, subJanela2;
SubItemSelecionado subItemAtual = NENHUM;

void switchCase()
{
	switch (subItemAtual)  
	{
        case EQUACAO_GERAL_DO_PLANO:
				equacaoGeralDoPlano();
            break;
        case POR_PONTO_VETOR_NORMAL:
				pontoVetorNormal();
            break;
        case POR_PONTO_2_VETORES:
				//pontoDoisVetores();
            break;
        case DOIS_PONTOS:
            doisPontos();
            break;
        case PONTO_RETA:
				pontoReta();
            break;
        case PONTO_PLANO:
		  		//pontoPlano();
            break;
        case DUAS_RETAS:
				//duasRetas();
            break;
        case RETA_PLANO:
				//retaPlano();
            break;
        case DOIS_PLANOS:
				//doisPlanos();
            break;
    }
}

void desenhaSubJanela1()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.01, 0.03, 0.08, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	desenhaMenu();
	glutSwapBuffers();
}

// Função callback chamada para fazer o desenho
void desenhaSubJanela2()
{
	int limite = 22;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glTranslated(0, 0, -75);
	glScaled(zoom, zoom, zoom);
	glRotated(anguloX, 1.0, 0.0, 0.0);
	glRotated(anguloY, 0.0, 1.0, 0.0);
	glRotated(30.0, 1, -1, 0.0);
	espacoCartesiano(limite);
	switchCase();

	glutSwapBuffers();
}

void inicializa()
{
	glClearColor(0.94f, 0.89f, 0.81f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

// Função callback chamada quando o tamanho da janela é alterado 
void redimensiona(GLsizei largura, GLsizei altura)
{
	int divisa = largura * 0.32;

	glutSetWindow(subJanela1);
	glutPositionWindow(0, 0);
	glutReshapeWindow(divisa, altura);
	glViewport(0, 0, divisa, altura);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
	glutPostRedisplay();

	glutSetWindow(subJanela2);
	glutPositionWindow(divisa, 0);
	glutReshapeWindow(largura - divisa, altura);
	glViewport(0, 0, largura - divisa, altura);
	inicializa();
	if (largura - divisa > altura)
		gluPerspective(30.0, (float)(largura - divisa) / (float)altura, 0.1, 500.0);
	else
		gluPerspective(30.0, (float)altura / (float)(largura - divisa), 0.1, 500.0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(300, 100);
	int mainWindow = glutCreateWindow("Planos e Distancias");
	glutDisplayFunc(desenhaSubJanela1);
	glutReshapeFunc(redimensiona);

	int divisa = 800 * 0.32;

	subJanela1 = glutCreateSubWindow(mainWindow, 0, 0, divisa, 600);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(tecladoEspecial);
	glutDisplayFunc(desenhaSubJanela1);
   glutMouseFunc(mouseSubJanela1);
	glutPassiveMotionFunc(movimentoMouse);

	subJanela2 = glutCreateSubWindow(mainWindow, divisa, 0, 800 - divisa, 600);
	glutDisplayFunc(desenhaSubJanela2);
	glutMouseFunc(mouse);
   glutMotionFunc(mouseMove);

	glutMainLoop();
}