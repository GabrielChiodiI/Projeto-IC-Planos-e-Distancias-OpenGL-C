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
    -55, 20, ITEM_WIDTH, ITEM_HEIGHT,
    {
        {"Equacao geral do plano", -50, 16, SUBITEM_WIDTH, SUBITEM_HEIGHT, false, EQUACAO_GERAL_DO_PLANO},
        {"Ponto/ vetor normal", -50, 16 - SUBITEM_HEIGHT, SUBITEM_WIDTH, SUBITEM_HEIGHT, false, POR_PONTO_VETOR_NORMAL},
        {"Ponto/ 2 vetores", -50, 16 - 2 * SUBITEM_HEIGHT, SUBITEM_WIDTH, SUBITEM_HEIGHT, false, POR_PONTO_2_VETORES},
    }
};

ItemMenu menuDistancias = {
    "Distancias",
    false,
    -55, 4, ITEM_WIDTH, ITEM_HEIGHT,
    {
        {"Dois Pontos", -50, 0, SUBITEM_WIDTH, SUBITEM_HEIGHT, false, DOIS_PONTOS},
        {"Ponto/ Reta", -50, 0 - SUBITEM_HEIGHT, SUBITEM_WIDTH, SUBITEM_HEIGHT, false, PONTO_RETA},
        {"Ponto/ Plano", -50, 0 - 2 * SUBITEM_HEIGHT, SUBITEM_WIDTH, SUBITEM_HEIGHT, false, PONTO_PLANO},
        {"Duas Retas", -50, 0 - 3 * SUBITEM_HEIGHT, SUBITEM_WIDTH, SUBITEM_HEIGHT, false, DUAS_RETAS},
        {"Reta/ Plano", -50, 0 - 4 * SUBITEM_HEIGHT, SUBITEM_WIDTH, SUBITEM_HEIGHT, false, RETA_PLANO},
        {"Dois Planos", -50, 0 - 5 * SUBITEM_HEIGHT, SUBITEM_WIDTH, SUBITEM_HEIGHT, false, DOIS_PLANOS}
    }
};

bool dentroDoRetangulo(ItemMenu item) {
    return (mouseX >= item.x) && (mouseX <= item.x + item.largura) 
           && (mouseY >= item.y) && (mouseY <= item.y + item.altura);
}

bool dentroDoSubItem(SubItem subitem) {
    return (mouseX >= subitem.x) && (mouseX <= subitem.x + subitem.largura) 
           && (mouseY >= subitem.y) && (mouseY <= subitem.y + subitem.altura);
}

void acaoSubItem(SubItemSelecionado subItem) {
    subItemAtual = subItem;
    glutSetWindow(subJanela2);
    glutPostRedisplay();
}

void desenhaDestaque(float x, float y, float largura, float altura) {
    glColor3f(0.9, 0.3, 0.3);  // cor vermelha para destaque
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + largura, y);
        glVertex2f(x + largura, y + altura);
        glVertex2f(x, y + altura);
    glEnd();
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

void desenhaMenu() {
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
    mouseX = (float)x / 10 - 60;
    mouseY = 60 - (float)y / 10;

    mouseSobrePlano = dentroDoRetangulo(menuPlano);
    mouseSobreDistancias = dentroDoRetangulo(menuDistancias);

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
    mouseX = (float)x / 10 - 60;
    mouseY = 60 - (float)y / 10;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (dentroDoRetangulo(menuPlano)) {
            menuPlano.isExpandido = !menuPlano.isExpandido;
            glutPostRedisplay();
        } else if (dentroDoRetangulo(menuDistancias)) {
            menuDistancias.isExpandido = !menuDistancias.isExpandido;
            glutPostRedisplay();
        }

        if (menuPlano.isExpandido) {
            acaoCliqueSubItem(&menuPlano, 3);
        }

        if (menuDistancias.isExpandido) {
            acaoCliqueSubItem(&menuDistancias, 6);
        }
    }
}