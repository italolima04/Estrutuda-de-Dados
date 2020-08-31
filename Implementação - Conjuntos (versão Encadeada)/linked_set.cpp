#include "linked_set.hpp"

#include <limits>

// Construir lista vazia, mas com capacidade máxima informada.
linked_set::linked_set() {
  this->primeiro = nullptr;
  this->tamanho = 0;
}

// Construtor de um nó, onde a informação do próximo, no momento construção, é
// opcional
linked_set::no_encadeado::no_encadeado(int valor, no_encadeado* proximo) {
  this->valor = valor;
  this->proximo = proximo;
}

// --- Métodos de "Coleção" ---

// Inserir "elemento" na coleção.
// Retornar indicativo de sucesso da inserção.
// NOTE Deve aumentar a capacidade caso necessário.
// NOTE Observe que aumentar em apenas uma unidade não nos alivia da pressão que
// tínhamos antes...
bool linked_set::inserir(int elemento) {
  if (this->tamanho == 0) {
    no_encadeado* novo_no = new no_encadeado(elemento);
    this->primeiro = novo_no;
    this->tamanho++;
    return true;
  } else {
    if (!(pertence(elemento))) {
      no_encadeado* anterior = obter_no_em(tamanho - 1);
      no_encadeado* novo_no = new no_encadeado(elemento);
      anterior->proximo = novo_no;
      this->tamanho++;
      return true;
    } else {
      return false;
    }
  }
}

// Remover "elemento" da coleção.
// Retornar indicativo de sucesso da remoção.
// NOTE Necessário preservar a ordem relativa dos que restarem.
bool linked_set::remover(int elemento) {
  if (!(this->tamanho > 0)) {
    return false;
  } else {
    if (!pertence(elemento)) {
      return false;
    }
    unsigned int indice_aux = obter_indice_de(elemento);
    no_encadeado* removido = obter_no_em(indice_aux);
    if (indice_aux == 0) {
      this->primeiro = removido->proximo;
      delete[] removido;
      this->tamanho--;
      return true;
    } else {
      no_encadeado* anterior = obter_no_em(indice_aux - 1);
      anterior->proximo = removido->proximo;
      delete[] removido;
      +this->tamanho--;
      return true;
    }
  }
  return false;
}

// Determinar se "elemento" é um dos elementos ainda na coleção.
bool linked_set::pertence(int elemento) const {
  if (!(this->tamanho > 0)) {
    return false;
  } else {
    no_encadeado* no = this->primeiro;
    while (no != nullptr) {
      if (no->valor == elemento) {
        return true;
      }
      no = no->proximo;
    }
  }
  return false;
}

// --- Métodos de "Conjunto" ---

// Tornar o próprio conjunto (`this`) o resultado de sua união com o outro
// informado.
void linked_set::uniao_com(linked_set const& conjunto) {
  no_encadeado* no = conjunto.primeiro;
  while (no != nullptr) {
    if (!(pertence(no->valor))) {
      inserir(no->valor);
    }
    no = no->proximo;
  }
}

// Tornar o próprio conjunto (`this`) o resultado de sua intersecção com o outro
// informado.
void linked_set::intersecao_com(linked_set const& conjunto) {
  no_encadeado* no = this->primeiro;
  while (no != nullptr) {
    if (!(conjunto.pertence(no->valor))) {
      remover(no->valor);
    }
    no = no->proximo;
  }
}

// Testar se este conjunto (`this`) está contido no outro informado.
bool linked_set::esta_contido_em(linked_set const& conjunto) const {
  if (this->tamanho == 0) {
    return true;
  } else {
    no_encadeado* no = this->primeiro;
    while (no != nullptr) {
      if (!(conjunto.pertence(no->valor))) {
        return false;
      }
      no = no->proximo;
    }
    return true;
  }
  return false;
}

// --- Métodos Auxiliares ---

// Desejamos obter o próprio nó que esteja no índice informado.
// Deve retornar `nullptr` quando tal nó não existe.
// Auxilia processos que dependem de encontrar nós baseado em um índice.
linked_set::no_encadeado* linked_set::obter_no_em(unsigned int indice) const {
  if (!(this->tamanho > 0)) {
    return nullptr;
  } else {
    no_encadeado* no = this->primeiro;
    for (unsigned int i = 0; i < indice; i++) {
      no = no->proximo;
    }
    return no;
  }
  return nullptr;
}

// Desejamos obter o próprio nó que veja **antes** de algum com o valor
// informado. (ou seja, `anterior.proximo.valor == valor`) Auxilia processos que
// dependem de encontrar nós baseado em um valor. Deve retornar `nullptr` quando
// tal nó não existe.
linked_set::no_encadeado* linked_set::obter_no_anterior_a(int valor) const {
  int aux = 0;
  if (!(this->tamanho > 0)) {
    return nullptr;
  } else {
    no_encadeado* no = this->primeiro;
    while (no != nullptr) {
      aux = no->proximo->valor;
      if (aux == valor) {
        return no;
      }
      no = no->proximo;
    }
  }
  return nullptr;
}

unsigned int linked_set::obter_indice_de(int elemento) {
  if (!(this->tamanho > 0)) {
    return std::numeric_limits<unsigned int>::max();
  } else {
    unsigned int indice = 0;
    no_encadeado* no = this->primeiro;
    while (no != nullptr) {
      if (no->valor == elemento) {
        return indice;
      }
      indice++;
      no = no->proximo;
    }
  }
  return std::numeric_limits<unsigned int>::max();
}
