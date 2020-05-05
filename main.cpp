/* *********************************************
Trabalho PAA - Abril de 2020
Implementação de um método em O(n log n) para calcular o par de pontos mais próximos dentre n pontos.
------------------------------------------------
Pontifícia Universidade Católica de Minas Gerais
Departamento de Ciência da Computação
Instituto de Ciências Exatas e Informática
Curso de Engenharia de Computação
Professor: Silvio Jamil Ferzoli Guimaraes

Alunos: Diogo Alves de Oliveira Silva | Eduardo Braz de Campos

********************************************* */
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
using namespace std;

float d; // Variavel distancia


float dist (int xa, int ya, int xb, int yb) // dist calcula distancia ponto (xa,ya) ao ponto (xb, yb)
{
float dist;
dist = pow((xa - xb),2) + pow((ya - yb),2); // [ (x-x')^2 + (y-y')^2 ]

dist = sqrt(dist);

return dist;
}


float quadratico (int *X, int *Y, int n)  // o par de pontos mais próximos dentre n pontos O(n^2) -- Parametros: vetores X, Y e tamanho "n"
{
    d = FLT_MAX;  // distancia <- INFINITO
    float aux;
for (int i=0; i<n; i++){
    for (int j=i+1; j<n; j++){
        aux = dist(X[i],Y[i], X[j], Y[j]);
        if ( aux < d)  // Se a distancia dos pontos atuais for menor que a armazenada, entao esta se torna a menor
            d = aux;
    }
}
return d;
}

int main()
{
    unsigned short int n = 5;       // Tamanho dos vetores
    int X[n] = {-2, 0, 1, 3, 4};         // Vetor X
    int Y[n] = {-1, 3, -2, 4, 2};        // Vetor Y


    quadratico(X, Y, n);

    cout << d << endl;
    return 0;
}
