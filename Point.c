#include "Ponto.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct ponto {
    float x;
    float y;
};

Ponto *criaPonto(float x, float y) {
    Ponto *p = malloc(sizeof(Ponto));
    if (p != NULL) {
        p->x = x;
        p->y = y;
    }
    return p;
}

void liberaPonto(Ponto *p) {
    free(p);
}

void acessaPonto(Ponto *p, float *x, float *y) {
    if (p != NULL) {
        *x = p->x;
        *y = p->y;
    }
}

void atribuiPonto(Ponto *p, float x, float y) {
    if (p != NULL) {
        p->x = x;
        p->y = y;
    }
}

float distancia(Ponto *p1, Ponto *p2) {
    float dx = p1->x - p2->x;
    float dy = p1->y - p2->y;

    return sqrtf(dx * dx + dy * dy);
}

float distanciaOrigem(Ponto *p) {
    return sqrtf(p->x * p->x + p->y * p->y);
}

void imprimePonto(Ponto *p) {
    printf("(%.3f,%.3f)\n", p->x, p->y);
}

int pontosIguais(Ponto *p1, Ponto *p2) {
    return p1->x == p2->x && p1->y == p2->y;
}