#include <GL/glut.h>
#include "funcoes.h"

/*Função que traça uma linha entre um ponto e os eixos coordenados
para facilitar a localização no espaço*/
void retasCoordenadas(float p[3])
{
	if (p[0] < -20 || p[0] > 20 ||
       p[1] < -20 || p[1] > 20 ||
         p[2] < -20 || p[2] > 20)
		return;

	glColor3f(0.40, 0.40, 0.40);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0x00FF);
	glBegin(GL_LINES);
		glVertex3f(0, 0, p[2]);
		glVertex3f(p[0], 0, p[2]);
		glVertex3f(p[0], 0, 0);
		glVertex3f(p[0], 0, p[2]);
		glVertex3f(p[0], 0, p[2]);
		glVertex3f(p[0], p[1], p[2]);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

/*Função que traça uma linha entre dois pontos no espaço*/
void distancia(float p1[], float p2[])
{
	glPointSize(1.0f);
	glColor3f(0.0, 0.0, 0.90);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0x00FF); 
	glBegin(GL_LINES);
		glVertex3fv(p1);
		glVertex3fv(p2);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

void criaPonto(float p[3])
{
	glPointSize(5.0f);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
		glVertex3fv(p);
	glEnd();
	retasCoordenadas(p);
}

void criaVetor(float p1[3], float p2[3])
{
	glPointSize(5.0f);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
		glVertex3fv(p1);
		glVertex3fv(p2);
	glEnd();
	retasCoordenadas(p1);
	retasCoordenadas(p2);
}

void criaPlano(float p1[3], float p2[3], float p3[3], float p4[3])
{
	glPointSize(1.0f);
	glColor4f(0, 0.6, 0, 0.5);
	glBegin(GL_QUADS);
		glVertex3fv(p1);
		glVertex3fv(p2);
		glVertex3fv(p3);
		glVertex3fv(p4);
	glEnd();
}

void geraLinhas(float p1[3], float p2[3], float p3[3], float p4[3], float tamanho)
{	
	int i;
	for(i=0; i<tamanho * 2; i++)
	{

		glTranslated(0, 0, 0);
		glBegin(GL_POINTS);
			glVertex3fv(p1);
			glVertex3fv(p2);
			glVertex3fv(p3);
			glVertex3fv(p4);
		glEnd();
		glDisable(GL_LINE_STIPPLE);
	}

}

void espacoCartesiano(float tamanho)
{
	GLfloat pretoTranslucido[4] = {0.0f, 0.0f, 0.0f, 0.10f};
	int i;
	float d = tamanho / 2;

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
		//X
		glVertex3f(-d, 0, 0);
		glVertex3f(d, 0, 0);
		//Y
		glVertex3f(0, -d, 0);
		glVertex3f(0, d, 0);
		//Z
		glVertex3f(0, 0, d);
		glVertex3f(0, 0, -d);
	glEnd();
	glPointSize(3.0f);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
		glVertex3f(d, 0, 0);
		glVertex3f(d-0.4, 0, -0.4);
		glVertex3f(d-0.4, 0, 0.4);
		glVertex3f(0, d, 0);
		glVertex3f(-0.4, d-0.4, 0);
		glVertex3f(0.4, d-0.4, 0);
		glVertex3f(0, 0, d);
		glVertex3f(-0.4, 0, d-0.4);
		glVertex3f(0.4, 0, d-0.4);
	glEnd();
	d--;
	glBegin(GL_POINTS);
		for(i=-d; i<=d; i++)
		{
		//X
			glVertex3f(i, 0, 0);
		//Y
			glVertex3f(0, i, 0);
		//Z
			glVertex3f(0, 0, i);
		}
	glEnd();
	glBegin(GL_LINES);
		for(i=-d; i<=d; i++)
		{
		//X
			/*glVertex3f(i, 0, -d);
			glVertex3f(i, 0, d);
			glVertex3f(-d, 0, i);
			glVertex3f(d, 0, i);*/
		//Y
			/*glVertex3f(i, -d, 0);
			glVertex3f(i, d, 0);
			glVertex3f(-d, i, 0);
			glVertex3f(d, i, 0);
		//Z
			glVertex3f(0, i, -d);
			glVertex3f(0, i, d);
			glVertex3f(0, -d, i);
			glVertex3f(0, d, i);*/
		}
	glEnd();
}

void equacaoGeralDoPlano()
{
	char equacao[50] = "3x + 2y − z + 1 = 0";
	float pontoPlano[3] = {4, -2, 9}; 
	float vetorNormal[3] = {3, -2, 9}, ponto1[3], ponto2[3], ponto3[3], ponto4[3];
	criaPlanoGeral(pontoPlano, vetorNormal, ponto1, ponto2, ponto3, ponto4);
	criaPlano(ponto1, ponto2, ponto3, ponto4);
}

void pontoVetorNormal()
{
	char equacao[50] = "3x + 2y − z + 1 = 0";
	float pontoPlano[3] = {4, -2, 9}; 
	float vetorNormal[3] = {3, -2, 9}, ponto1[3], ponto2[3], ponto3[3], ponto4[3];
	float pontoInicioDiretor[3], pontoFimDiretor[3], pontoVetor[3];
	criaPonto(pontoPlano);
	intersecaoVetorPlano(vetorNormal, pontoPlano, pontoVetor);
	criaVetorDiretor(vetorNormal, pontoPlano, pontoInicioDiretor, pontoFimDiretor);
	criaVetor(pontoInicioDiretor, pontoFimDiretor);
	criaPlanoGeral(pontoPlano, vetorNormal, ponto1, ponto2, ponto3, ponto4);
	criaPlano(ponto1, ponto2, ponto3, ponto4);
}
/*
void pontoDoisVetores()
{
	criaPonto();
	criaVetorDiretor(, , );
	criaVetor(, );
	criaVetorDiretor(, , );
	criaVetor(, );
	produtoVetorial(, , );
	criaVetorDiretor(, , );
	criaVetor(, );
	criaPlanoGeral(, , , , , );
	criaPlano(, , , );
}*/

void doisPontos()
{
	float ponto1[3] = {2, -1, 3}, ponto2[3] = {1, 1, 5};

	criaPonto(ponto1);
	criaPonto(ponto2);
	distancia(ponto1, ponto2);
}

void pontoReta()
{
	float pontoForaReta[3] = {2, 1, 4}, pontoReta[3] = {-1, 2, 3}, vetorDiretor[3] = {2, -1, -2};
	float pontoInicioDiretor[3], pontoFimDiretor[3], retaDistanciaPontos[3], pontoProjetado[3];
	criaPonto(pontoForaReta);
	criaPonto(pontoReta);
	criaVetorDiretor(vetorDiretor, pontoReta, pontoInicioDiretor, pontoFimDiretor);
	criaVetor(pontoInicioDiretor, pontoFimDiretor);
	subtraiVetor(pontoReta, pontoForaReta, retaDistanciaPontos);
	projecaoDoPontoVetor(pontoForaReta, vetorDiretor, pontoReta, pontoProjetado);
	criaPonto(pontoProjetado);
	distancia(pontoForaReta, pontoProjetado);
}

/*void pontoPlano()
{
	criaPonto();
	pegaVetorNormal(, );
	criaPlanoGeral(, , , , , );
	criaPlano(, , , );
	projecaoDoPontoPlano(, , , );
	criaPonto();
	distancia(, );
}

void duasRetas()
{
	float pontoForaReta[3] = {2, 1, 4}, pontoReta[3] = {-1, 2, 3}, vetorDiretor[3] = {2, -1, -2};
	float pontoInicioDiretor[3], pontoFimDiretor[3], retaDistanciaPontos[3], pontoProjetado[3];
	criaPonto();
	criaVetorDiretor(, , );
	criaVetor(, );
	criaPonto();
	criaVetorDiretor(, , );
	criaVetor(, );
	distancia(, );
}

void retaPlano()
{
	float pontoReta[3] = {-1, 2, 3}, vetorDiretor[3] = {2, -1, -2};
	float pontoPlano[3] = {1, 1, 1}, vetorNormal[3] = {0, 1, 0};

	criaPonto(pontoReta);
	criaVetorDiretor(vetorDiretor, pontoReta, , );
	criaPonto(pontoPlano);
	pegaVetorNormal(vetorNormal, );
	criaPlanoGeral(, , , , , ); 

}

void doisPlanos()
{
	float pontoReta[3] = {-1, 2, 3}, vetorDiretor[3] = {2, -1, -2};
	float pontoPlano[3] = {1, 1, 1}, vetorNormal[3] = {0, 1, 0};

	criaPonto(pontoReta);
	criaVetorDiretor(vetorDiretor, pontoReta, , );
	criaPonto(pontoPlano);
	pegaVetorNormal(vetorNormal, );
	criaPlanoGeral(, , , , , ); 
}*/

