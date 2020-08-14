#include "vector.hpp"

#include <limits>

#include "stdlib.h"

// Construir lista vazia, mas com capacidade máxima informada.
vector::vector(unsigned int capacidade) {
  vetor = new int[capacidade];
  tamanho = 0;
  this->capacidade = capacidade;
}

// Construir lista com "tamanho" cópias do valor "inicial".
vector::vector(unsigned int tamanho, int inicial) {
  vetor = new int[tamanho];
  capacidade = tamanho;
  this->tamanho = tamanho;

  for (unsigned int i = 0; i < tamanho; i++) {
    vetor[i] = inicial;
  }
}

// --- Métodos de "Coleção" ---

// Inserir "elemento" na coleção. Sempre deve executar a inserção.
// FIXME Fazer realocação quando não houver espaço.
// NOTE  Observe que aumentar em apenas uma unidade não nos alivia da pressão
// que tínhamos antes...
void vector::inserir(int elemento) {
  // TODO Reorganizar o código
  if (tamanho < capacidade) {
    vetor[tamanho] = elemento;
    tamanho++;
    capacidade++;

  } else {
    // TODO Realocar o vetor e inserir "elemento"
    vetor = (int *)realloc(vetor, capacidade * sizeof(int));
    vetor[tamanho] = elemento;
    tamanho++;
  }
}

// Remover "elemento" da coleção.
// Retornar indicativo de sucesso da remoção.
// NOTE Necessário preservar a ordem relativa dos que restarem.
bool vector::remover(int elemento) {
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
bool vector::pertence(int elemento) {
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

// Inserir "elemento" na lista de forma que ele passe a constar no índice
// "indice". NOTE Necessário preservar a ordem relativa dos demais elementos.
void vector::inserir_em(unsigned int indice, int elemento) {
  // TODO Implementação.
  if (indice > tamanho) {
    return;
  } else {
    if (tamanho < capacidade) {
      for (unsigned int i = tamanho; i > indice; i--) {
        vetor[i] = vetor[i - 1];
      }
      vetor[indice] = elemento;
      tamanho++;
    } else {
      return;
    }
  }
}

// Remover o elemento associado a "indice".
// Retornar indicativo de sucesso da remoção.
bool vector::remover_de(unsigned int indice) {
  if (indice >= tamanho) {
    return false;
  } else {
    for (unsigned int j = indice + 1; j < tamanho; j++) {
      vetor[j - 1] = vetor[j];
    }
    tamanho--;
    return true;
  }
}

// Retornar o valor associado ao índice "indice".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<int>::max()`
//      (forma de obter o maior valor representável).
int vector::obter_elemento_em(unsigned int indice) {
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
unsigned int vector::obter_indice_de(int elemento) {
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
