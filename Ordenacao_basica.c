#include <stdio.h>

int verificar_ordenacao(int vetor[], int tamanho_vetor)
{
    for (int i = 1; i < tamanho_vetor; ++i)
    {
        if (vetor[i - 1] > vetor[i])
        {
            return 0;
        }
    }

    return 1;
}

int insertion_sort(int v[], int tam)
{
    int i, j, valor;
    for (i = 1; i < tam; i++)
    {
        valor = v[i];
        j = i - 1;

        while (j >= 0 && valor < v[j])
        {
            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = valor;
    }
    return 0;
}

int selection_sort(int vetor[], int tam)
{
    int i, j, aux, menor = 0;

    for (i = 0; i < tam - 1; i++)
    {
        menor = i;
        for (j = i + 1; j < tam; j++)
        {
            if (vetor[j] < vetor[menor])
            {
                menor = j;
            }
        }

        if (i != menor)
        {
            aux = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = aux;
        }
    }
    return 0;
}

int bubble_sort(int ve[], int tam)
{
    int i, k, aux;
    for (i = 0; i < tam - 1; i++)
    {
        for (k = 0; k < (tam - 1) - i; k++)
        {
            if (ve[k + 1] < ve[k])
            {
                aux = ve[k + 1];
                ve[k + 1] = ve[k];
                ve[k] = aux;
            }
        }
    }
    return 0;
}


switch (expression)
{
case /* constant-expression */:
    /* code */
    break;

default:
    break;
}


int main()
{
    int tam, i, j, k;

    printf("Defina o Tamanho do Vetor: ");
    scanf("%d", &tam);
    int vetor[tam];

    for (k = 0; k < tam; k++)
    {
        scanf("%d", &vetor[k]);
    }

    //printf("Insertion Sort: ");
    //insertion_sort(vetor, tam);
    //printf("Selection Sort:");
    //selection_sort(vetor, tam);
    // printf("Bubble Sort: ");
    selection_sort(vetor, tam);

    for (i = 0; i < tam; i++)
    {
        printf("%d", vetor[i]);
    }

    int resultado = verificar_ordenacao(vetor, tam);
    printf("\n");
    printf("%d\n", resultado);

    return 0;
}
