#include <stdio.h>

#include <iostream>

using namespace std;

class vector {
 private:
  // Defininindo as propriedades do registro.
  int *vetor;
  unsigned int tamanho;
  unsigned int capacidade;

 public:
  // Criando vetor com uma capacidade definida.
  vector(unsigned int capacidade, int inicial) {
    vetor = new int[capacidade];
    this->tamanho = 0;
    this->capacidade = capacidade;
  }

  // Criando a lista vazia.
  vector(unsigned int tamanho, int inicial) {
    vetor = new int[tamanho];
    capacidade = tamanho;
    this->tamanho = tamanho;

    for (unsigned int i = 0; i < tamanho; i++) {
      vetor[i] = inicial;
    }
  }

  // #Operações de Coleção# //

  // Inserir um elemento na coleção.
  void inserir_elemento(int elemento) {
    if (tamanho < capacidade) {
      tamanho++;
      vetor[tamanho] = elemento;
    } else {
      // Realocando Vetor. +1 Posição.
      vetor = (int *)(realloc(vetor, sizeof(int)));
    }
  }

  // Remover elemento na coleção.
  bool remover_elemento(int elemento) {
    if (verificar_pertinencia(elemento) == true) {
    } else {
      return false;
    }
  }

  // Verificar se um elemento está contido na coleção.
  bool verificar_pertinencia(int elemento) {
    for (unsigned int i = 0; i < tamanho; i++) {
      if (vetor[i] == elemento) {
        return true;
      } else {
        return false;
      }
    }
  }

  // #Operações de Lista# //

  // Inserir um elemento na lista para um índice específico

  bool inserir(int elemento, unsigned int indice) {}

  // Remover um elemento da lista através do índice.
  bool remover(unsigned int indice) {
    if (indice >= tamanho) {
      return false;
    } else {
      for (unsigned int i = indice + 1; i < tamanho; i++) {
        vetor[i - 1] = vetor[i];
      }
      tamanho--;
    }
  }

  // Obter elemento-índice.
  int obter_elemento_indice(int elemento) {
    for (unsigned int i = 0; i < tamanho; i++) {
      if (vetor[i] == elemento) {
        return vetor[elemento], elemento;
      } else {
        return false;
      }
    }
  }

  // Obter elemento através do índice.
  int obter_elemento(unsigned int indice) {
    if (indice > tamanho) {
      return false;
    } else {
      return vetor[indice];
    }
  }
};

int main() { return 0; }