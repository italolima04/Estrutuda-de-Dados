#include "ordered_vector.hpp"

#include <limits>

#include "stdlib.h"

// Construir lista vazia, mas com capacidade máxima informada.
ordered_vector::ordered_vector(unsigned int capacidade) {
  vetor = new int[capacidade];
  tamanho = 0;
  this->capacidade = capacidade;
}

// Construir lista com "tamanho" cópias do valor "inicial".
ordered_vector::ordered_vector(unsigned int tamanho, int inicial) {
  vetor = new int[tamanho];
  capacidade = tamanho;
  this->tamanho = tamanho;

  for (unsigned int i = 0; i < tamanho; i++) {
    vetor[i] = inicial;
  }
}

// --- Métodos de "Coleção" ---

// Inserir "elemento" na coleção. Sempre deve executar a inserção.
// NOTE  Observe que aumentar em apenas uma unidade não nos alivia da pressão
// que tínhamos antes...

void insertion_sort(int *vetor, int tamanho) {
  int valor = 0, j;
  for (unsigned int i = 1; i < tamanho; i++) {
    valor = vetor[i];
    j = i - 1;
    while (j >= 0 && valor < vetor[j]) {
      vetor[j + 1] = vetor[j];
      j--;
    }
    vetor[j + 1] = valor;
  }
}

void ordered_vector::inserir(int elemento) {
  // TODO Implementação.
  if (tamanho < capacidade) {
    vetor[tamanho] = elemento;
    tamanho++;
    capacidade++;
    insertion_sort(vetor, tamanho);

  } else {
    // TODO Realocar o vetor e inserir "elemento"
    vetor = (int *)realloc(vetor, capacidade * sizeof(int));
    vetor[tamanho] = elemento;
    tamanho++;
    insertion_sort(vetor, tamanho);
  }
}

// Remover "elemento" da coleção.
// Retornar indicativo de sucesso da remoção.
// NOTE Necessário preservar a ordem relativa dos que restarem.
bool ordered_vector::remover(int elemento) {
  // TODO Implementação.
  if (!(tamanho > 0)) {
    return false;
  } else {
    for (unsigned int i = 0; i < tamanho; i++) {
      if (vetor[i] == elemento) {
        for (unsigned int j = i + 1; j < tamanho; j++) {
          vetor[j - 1] = vetor[j];
        }
        tamanho--;
        return true;
      }
    }
  }
  return false;
}

// Determinar se "elemento" é um dos elementos ainda na coleção.
bool ordered_vector::pertence(int elemento) {
  // TODO Implementação.
  if (!(tamanho > 0)) {
    return false;
  } else {
    for (unsigned int i = 0; i < tamanho; i++) {
      if (vetor[i] == elemento) {
        return true;
      } else {
        return false;
      }
    }
  }
}

// --- Métodos de "Lista" ---

// Remover o elemento associado a "indice".
// Retornar indicativo de sucesso da remoção.
bool ordered_vector::remover_de(unsigned int indice) {
  // TODO Implementação.
  if (indice >= tamanho) {
    return false;
  } else {
    for (unsigned int j = indice + 1; j < tamanho; j++) {
      vetor[j - 1] = vetor[j];
    }
    tamanho--;
    return true;
  }
  return false;
}

// Retornar o valor associado ao índice "indice".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<int>::max()`
//      (forma de obter o maior valor representável).
int ordered_vector::obter_elemento_em(unsigned int indice) {
  // TODO Implementação.
  if (tamanho > 0) {
    if (indice >= tamanho) {
      return std::numeric_limits<int>::max();
    } else {
      return vetor[indice];
    }
  } else {
    return std::numeric_limits<int>::max();
  }
}

// Retornar o índice associado a "elemento".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<unsigned
// int>::max()`
//      (forma de obter o maior valor representável).
unsigned int ordered_vector::obter_indice_de(int elemento) {
  // TODO Implementação.
  if (tamanho > 0) {
    for (unsigned int i = 0; i < tamanho; i++) {
      if (vetor[i] == elemento) {
        return i;
      }
    }
  } else {
    return std::numeric_limits<unsigned int>::max();
  }
}
