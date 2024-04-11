#include <GL/glut.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "projeto.h"

#define MAX_SUBITEMS 6
#define ITEM_WIDTH 50
#define ITEM_HEIGHT 5
#define SUBITEM_WIDTH 45
#define SUBITEM_HEIGHT 5

typedef struct {
    char nome[30];
    float x, y, largura, altura;
    bool mouseSobreSubItem;
    SubItemSelecionado tipo; // Novo campo
} SubItem;

typedef struct {
    char nome[20];
    bool isExpandido;
    float x, y, largura, altura;
    SubItem subItens[MAX_SUBITEMS];
} ItemMenu;

float mouseX, mouseY;
bool mouseSobrePlano = false;
bool mouseSobreDistancias = false;

ItemMenu menuPlano = {
    "Plano",
    false,
    -90, 60, ITEM_WIDTH, ITEM_HEIGHT,
    {
        {"Equacao geral do plano", -80, 60 - 1 * SUBITEM_HEIGHT, SUBITEM_WIDTH, SUBITEM_HEIGHT, false, EQUACAO_GERAL_DO_PLANO},
        {"Ponto/ vetor normal", -80, 60 - 2 * SUBITEM_HEIGHT, SUBITEM_WIDTH, SUBITEM_HEIGHT, false, POR_PONTO_VETOR_NORMAL},
        {"Ponto/ 2 vetores", -80, 60 - 3 * SUBITEM_HEIGHT, SUBITEM_WIDTH, SUBITEM_HEIGHT, false, POR_PONTO_2_VETORES},
    }
};

ItemMenu menuDistancias = {
    "Distancias",
    false,
    -90, 60 - 4 * SUBITEM_HEIGHT, ITEM_WIDTH, ITEM_HEIGHT,
    {
        {"Dois Pontos", -80, 60 - 5 * SUBITEM_HEIGHT, SUBITEM_WIDTH, SUBITEM_HEIGHT, false, DOIS_PONTOS},
        {"Ponto/ Reta", -80, 60 - 6 * SUBITEM_HEIGHT, SUBITEM_WIDTH, SUBITEM_HEIGHT, false, PONTO_RETA},
        {"Ponto/ Plano", -80, 60 - 7 * SUBITEM_HEIGHT, SUBITEM_WIDTH, SUBITEM_HEIGHT, false, PONTO_PLANO},
        {"Duas Retas", -80, 60 - 8 * SUBITEM_HEIGHT, SUBITEM_WIDTH, SUBITEM_HEIGHT, false, DUAS_RETAS},
        {"Reta/ Plano", -80, 60 - 9 * SUBITEM_HEIGHT, SUBITEM_WIDTH, SUBITEM_HEIGHT, false, RETA_PLANO},
        {"Dois Planos", -80, 60 - 10 * SUBITEM_HEIGHT, SUBITEM_WIDTH, SUBITEM_HEIGHT, false, DOIS_PLANOS}
    }
};

bool dentroDoRetangulo(float x, float y, float largura, float altura) {
    return (mouseX >= x) && (mouseX <= x + largura) && (mouseY >= y) && (mouseY <= y + altura);
}

bool dentroDoSubItem(SubItem subitem) {
    return dentroDoRetangulo(subitem.x, subitem.y, subitem.largura, subitem.altura);
}

void acaoSubItem(SubItemSelecionado subItem) {
    subItemAtual = subItem;
    glutSetWindow(subJanela2);
    glutPostRedisplay();
}

void desenhaDestaque(float x, float y, float largura, float altura) {
    glColor3f(0.9, 0.3, 0.3); // cor vermelha para destaque
    glPushMatrix(); // Usa push e pop para não afetar outras transformações
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + largura, y);
        glVertex2f(x + largura, y + altura);
        glVertex2f(x, y + altura);
    glEnd();
    glPopMatrix();
}

void desenhaTexto(char *texto, float x, float y) {
    glColor3f(1.0, 1.0, 1.0); // cor branca
    glRasterPos2f(x, y);
    for (int i = 0; texto[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, texto[i]);
    }
}

void desenhaItemMenu(ItemMenu item, bool mouseSobreItem) {
    // Desenha o nome do menu
    desenhaTexto(item.nome, item.x, item.y);

    if (mouseSobreItem) {
        desenhaDestaque(item.x, item.y, item.largura, item.altura);
    }
}

void desenhaSubItens(ItemMenu item) {
    int count = 0;
    if (strcmp(item.nome, "Plano") == 0) {
        count = 3; // 3 subitens para "Plano"
    } else if (strcmp(item.nome, "Distancias") == 0) {
        count = 6; // 6 subitens para "Distancias"
    }

    for (int i = 0; i < count; i++) {
        // Desenha o texto do subitem
        desenhaTexto(item.subItens[i].nome, item.subItens[i].x + 1, item.subItens[i].y + 2);

        if (item.subItens[i].mouseSobreSubItem) {
            desenhaDestaque(item.subItens[i].x, item.subItens[i].y, item.subItens[i].largura, item.subItens[i].altura);
        }
    }
}

void desenhaDivisoria(){

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2f(-5, 50);
        glVertex2f(-5, -15);
    glEnd();

}

void desenhaMenu(){

    desenhaDivisoria();

    desenhaItemMenu(menuPlano, mouseSobrePlano);
    if (menuPlano.isExpandido) {
        desenhaSubItens(menuPlano);
    }

    desenhaItemMenu(menuDistancias, mouseSobreDistancias);
    if (menuDistancias.isExpandido) {
        desenhaSubItens(menuDistancias);
    }
}

void atualizaSubItensMouseSobre(ItemMenu *menu, int subItemsCount) {
    for (int i = 0; i < subItemsCount; i++) {
        menu->subItens[i].mouseSobreSubItem = dentroDoSubItem(menu->subItens[i]);
    }
}

void movimentoMouse(int x, int y) {
    // Convertendo as coordenadas do sistema da janela para o sistema de coordenadas OpenGL
    // Supondo que a origem (0,0) do OpenGL está no centro da janela e o tamanho da janela é conhecido
    int larguraJanela = glutGet(GLUT_WINDOW_WIDTH);
    int alturaJanela = glutGet(GLUT_WINDOW_HEIGHT);

    // Conversão das coordenadas do mouse para que (0,0) seja o centro da janela
    mouseX = ((float)x - (larguraJanela / 2)) * (100.0 / (larguraJanela / 2));
    mouseY = ((alturaJanela / 2) - (float)y) * (100.0 / (alturaJanela / 2));

    // Atualização dos estados de mouse sobre itens e subitens
    mouseSobrePlano = dentroDoRetangulo(menuPlano.x, menuPlano.y, menuPlano.largura, menuPlano.altura);
    mouseSobreDistancias = dentroDoRetangulo(menuDistancias.x, menuDistancias.y, menuDistancias.largura, menuDistancias.altura);

    if (menuPlano.isExpandido) {
        atualizaSubItensMouseSobre(&menuPlano, 3);
    }

    if (menuDistancias.isExpandido) {
        atualizaSubItensMouseSobre(&menuDistancias, 6);
    }

    glutPostRedisplay();
}

void acaoCliqueSubItem(ItemMenu *menu, int subItemsCount) {
    for (int i = 0; i < subItemsCount; i++) {
        if (dentroDoSubItem(menu->subItens[i])) {
            acaoSubItem(menu->subItens[i].tipo);
        }
    }
}

void mouseSubJanela1(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Converte a posição do clique para coordenadas OpenGL
        int larguraJanela = glutGet(GLUT_WINDOW_WIDTH);
        int alturaJanela = glutGet(GLUT_WINDOW_HEIGHT);
        mouseX = ((float)x - (larguraJanela / 2)) * (100.0 / (larguraJanela / 2));
        mouseY = ((alturaJanela / 2) - (float)y) * (100.0 / (alturaJanela / 2));

        // Verifica se o clique foi sobre os itens principais do menu
        if (dentroDoRetangulo(menuPlano.x, menuPlano.y, menuPlano.largura, menuPlano.altura)) {
            menuPlano.isExpandido = !menuPlano.isExpandido;
        } else if (dentroDoRetangulo(menuDistancias.x, menuDistancias.y, menuDistancias.largura, menuDistancias.altura)) {
            menuDistancias.isExpandido = !menuDistancias.isExpandido;
        }

        // Trata cliques nos subitens, se necessário
        if (menuPlano.isExpandido) {
            acaoCliqueSubItem(&menuPlano, 3);
        }

        if (menuDistancias.isExpandido) {
            acaoCliqueSubItem(&menuDistancias, 6);
        }

        glutPostRedisplay();
    }
}
