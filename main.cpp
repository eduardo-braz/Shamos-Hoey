/* *****************************************************************
Trabalho PAA - Abril de 2020
Implementação de um método em O(n log n) para calcular o par de
pontos mais próximos dentre n pontos.
------------------------------------------------
Pontifícia Universidade Católica de Minas Gerais
Departamento de Ciência da Computação
Instituto de Ciências Exatas e Informática
Curso de Engenharia de Computação
Professor: Silvio Jamil Ferzoli Guimaraes

Alunos: Diogo Alves de Oliveira Silva | Eduardo Braz de Campos

Obs.: O metodo escolhido foi baseado no algoritmo de Shamos-Hoey
***************************************************************** */
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>

float MenorDist; // Variavel menor distancia final

struct Ponto{
    int x, y;
};

// Declaração de Funcoes -------------------------------------------
float MaisProxCentral(Ponto MatrizCentral[], short int k, float d);
float menorDistancia(Ponto px[], Ponto py[], unsigned short int n);
float pontoProximo(Ponto p[], unsigned short int n);
float quadratico (Ponto p[], unsigned short int n);
float dist (Ponto p1, Ponto p2);
int comparaEixoY(const void* a, const void* b);
int comparaEixoX(const void* a, const void* b);
// -----------------------------------------------------------------

// dist calcula distancia ponto (x1,y1) ao ponto (x2, y2)
float dist (Ponto p1, Ponto p2)
{
float dist;
dist = pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2); // [ (x-x')^2 + (y-y')^2 ]

dist = sqrt(dist);

return dist;
}

// Compara par a par de pontos, ordem O(n^2)
// Parametros: matriz com par de pontos p[] e quantidade de pontos "n"
float quadratico (Ponto p[], unsigned short int n)
{
    MenorDist = FLT_MAX;
    float aux;

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
                aux = dist(p[i], p[j]);
                if ( aux < MenorDist)  // Se a distancia dos pontos atuais for menor que a armazenada, entao esta se torna a menor
                    MenorDist = aux;
        }
    }

return MenorDist;
}

/* As funcoes comparaEixoX e comparaEixoY sao usadas para ordenacao em
cada eixo, com o auxilo da funcao qsort()
*/
int comparaEixoX(const void* a, const void* b)
{
    Ponto *p1 = (Ponto *)a;
    Ponto *p2 = (Ponto *)b;

    if (p1->x > p2->x) {
      return 1;
   } else if (p1->x < p2->x) {
      return -1;
   } else {
      return 0;
   }

}

int comparaEixoY(const void* a, const void* b)
{
    Ponto *p1 = (Ponto *)a;
    Ponto *p2 = (Ponto *)b;

    if (p1->y > p2->y) {
      return 1;
   } else if (p1->y < p2->y) {
      return -1;
   } else {
      return 0;
   }

}

// Retorna a menor distancia em relação ao eixo X
float pontoProximo(Ponto p[], unsigned short int n)
{
    Ponto px[n], py[n];

	for (int i=0; i<n; i++){
		px[i] = p[i];
		py[i] = p[i];
	}

	// Ordena os pontos
	qsort(px, n, sizeof(Ponto), comparaEixoX);
	qsort(py, n, sizeof(Ponto), comparaEixoY);

    return menorDistancia(px, py, n);
}

// Encontra a menor distancia
float menorDistancia(Ponto px[], Ponto py[], unsigned short int n)
{
    // Quando num pontos <= 3, usa-se o metodo quadratico
    if (n <= 3)
        return quadratico(px, n);

    // Calculo do ponto central
    int meio = n/2;
    Ponto pontoCentral = px[meio];

    // Divisao e conquista
    // Calcula a menor distancia dos lados esquerdo e direito do ponto central
    // em relação ao eixo Y e supondo que todas as coordenadas x sao distintas.
    Ponto distPyEsq[meio], distPyDir[n-meio]; // Pontos esquerdo e direito ordenados

    short int iEsq=0, iDir=0; // auxiliares indexadores

    for (int i=0; i<n; i++) {
        if (py[i].x <= pontoCentral.x && iEsq<meio)
            distPyEsq[iEsq++] = py[i];
        else
            distPyDir[iDir++] = py[i];
	}

    // Considerando que a linha vertical passa pelo ponto central
    // entao distEsq =  menor distancia a esquerda do ponto central e
    // distDir = menor a direita

    float distEsq = menorDistancia(px, distPyEsq, meio);
    float distDir = menorDistancia((px + meio), distPyDir , (n-meio));

    // Seleciona a menor distancia dos pontos da direita ou esquerda
    if (distDir < distEsq) {
        MenorDist = distDir;
    } else {
        MenorDist = distEsq;
    }

    // Faixa com os pontos proximos do ponto central
    Ponto MatrizCentral[n];
    short int k = 0;
    for (short int i = 0; i < n; i++) {
        if (abs(py[i].x - pontoCentral.x) < MenorDist){
            MatrizCentral[k] = py[i];
            k++;
        }
    }

    // Retorna a menor distancia dentro da matriz central
    return MaisProxCentral(MatrizCentral, k, MenorDist);
}

/* Funcao para encontrar a distancia entre os pontos mais próximos da MatrizCentral.
Os pontos são ordenados em relação ao eixo Y, e tem um limite superior
na distancia minima.
*/
float MaisProxCentral(Ponto MatrizCentral[], short int k, float d)
{
    float menor = d;

    for (int i = 0; i < k; i++) {
        for (int j = i+1; (j < k) && ((MatrizCentral[j].y - MatrizCentral[i].y) < menor); j++) {
            float aux = dist(MatrizCentral[i],MatrizCentral[j]);
            if ( aux < menor)
                menor = aux;
        }
    }
return menor;
}

int main()
{
    unsigned short int n = 7;       // Tamanho dos vetores
    // Matriz p[] possui os pares de pontos
    Ponto p[] = {{0, 3}, {3, 4}, {-2, -1}, {1, -2}, {4, 2}, {15, 15}, {20, -10}};

    float pnt = pontoProximo(p, n);
    printf("A distancia mais proxima dos pontos = %.4f\n", pnt);

    return 0;
}
