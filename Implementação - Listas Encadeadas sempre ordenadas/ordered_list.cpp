#include "ordered_list.hpp"

#include <limits>

// Construir lista vazia, mas com capacidade máxima informada.
ordered_list::ordered_list() {
  this->primeiro = nullptr;
  this->tamanho = 0;
}

// Construtor de um nó, onde a informação do próximo, no momento construção, é
// opcional
ordered_list::no_encadeado::no_encadeado(int valor, no_encadeado* proximo) {
  this->valor = valor;
  this->proximo = proximo;
}

// Construir lista com "tamatamanhonho" cópias do valor "inicial".
ordered_list::ordered_list(unsigned int tamanho, int inicial) {
  this->tamanho = tamanho;
  this->primeiro = nullptr;
  for (unsigned int i = 0; i < this->tamanho; i++) {
    no_encadeado* novo_no = new no_encadeado(inicial, this->primeiro);
    this->primeiro = novo_no;
  }
}

// --- Métodos de "Coleção" ---

// Inserir "elemento" na coleção. Sempre deve executar a inserção.
void ordered_list::inserir(int elemento) {
  if (this->tamanho == 0) {
    no_encadeado* novo_no = new no_encadeado(elemento);
    this->primeiro = novo_no;
    tamanho++;
  } else {
    no_encadeado* anterior = obter_no_em(this->tamanho - 1);
    no_encadeado* novo_no = new no_encadeado(elemento);
    anterior->proximo = novo_no;
    tamanho++;
  }
  for (unsigned int i = 0; i < this->tamanho - 1; i++) {
    for (unsigned int k = 0; k < (this->tamanho - 1) - i; k++) {
      no_encadeado* no = obter_no_em(k);
      no_encadeado* no_aux = obter_no_em(k + 1);
      if (no_aux->valor < no->valor) {
        if (obter_indice_de(no->valor) == 0) {
          this->primeiro = no_aux;
          no->proximo = no_aux->proximo;
          this->primeiro->proximo = no;
        } else {
          no_encadeado* no_aux_2 = obter_no_anterior_a(no->valor);
          no->proximo = no_aux->proximo;
          no_aux->proximo = no;
          no_aux_2->proximo = no_aux;
        }
      }
    }
  }
}

// Remover "elemento" da coleção.
// Retornar indicativo de sucesso da remoção.
bool ordered_list::remover(int elemento) {
  if (!(this->tamanho > 0)) {
    return false;
  } else {
    if (!pertence(elemento)) {
      return false;
    }
    unsigned int indice_aux = obter_indice_de(elemento);
    if (indice_aux == 0) {
      no_encadeado* removido = obter_no_em(indice_aux);
      this->primeiro->proximo = removido->proximo;
      delete[] removido;
      this->tamanho--;
      return true;
    } else {
      no_encadeado* removido = obter_no_em(indice_aux);
      no_encadeado* anterior = obter_no_em(indice_aux - 1);
      anterior->proximo = removido->proximo;
      delete[] removido;
      this->tamanho--;
      return true;
    }
  }
  return false;
}

// Determinar se "elemento" é um dos elementos ainda na coleção.
bool ordered_list::pertence(int elemento) {
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

// --- Métodos de "Lista" ---

// Remover o elemento associado a "indice".
// Retornar indicativo de sucesso da remoção.
bool ordered_list::remover_de(unsigned int indice) {
  if (!(this->tamanho > 0)) {
    return false;
  }
  if (indice >= this->tamanho) {
    return false;
  } else {
    no_encadeado* removido = obter_no_em(indice);
    remover(removido->valor);
  }
}

// Retornar o valor associado ao índice "indice".
// NOTE Quando o índice for inválido, retornar
// `std::numeric_limits<int>::max()`
//      (forma de obter o maior valor representável).
int ordered_list::obter_elemento_em(unsigned int indice) {
  if (!(this->tamanho > 0)) {
    return std::numeric_limits<int>::max();
  } else {
    if (indice >= this->tamanho) {
      return std::numeric_limits<int>::max();
    } else {
      no_encadeado* no = this->primeiro;
      for (unsigned int i = 0; i < indice; i++) {
        no = no->proximo;
      }
      return no->valor;
    }
  }
}

// Retornar o índice associado a "elemento".
// NOTE Quando o índice for inválido, retornar `std::numeric_limits<unsigned
// int>::max()`
//      (forma de obter o maior valor representável).
unsigned int ordered_list::obter_indice_de(int elemento) {
  if (!(this->tamanho > 0)) {
    return std::numeric_limits<unsigned int>::max();
  } else {
    if (!(pertence(elemento))) {
      // return std::numeric_limits<unsigned int>::max();
    } else {
      unsigned int indice = 0;
      no_encadeado* no = this->primeiro;
      while (no != nullptr) {
        if (no->valor == elemento) {
          return indice;
        }
        no = no->proximo;
        indice++;
      }
    }
  }
}

// --- Métodos Auxiliares ---

// Desejamos obter o próprio nó que esteja no índice informado.
// Deve retornar `nullptr` quando tal nó não existe.
// Auxilia processos que dependem de encontrar nós baseado em um índice.
ordered_list::no_encadeado* ordered_list::obter_no_em(unsigned int indice) {
  if (!(this->tamanho > 0)) {
    return nullptr;
  } else {
    if (indice > this->tamanho) {
      return nullptr;
    } else {
      no_encadeado* no = this->primeiro;
      for (unsigned int i = 0; i < indice; i++) {
        no = no->proximo;
      }
      return no;
    }
  }
}

// Desejamos obter o próprio nó que veja **antes** de algum com o valor
// informado. (ou seja, `anterior.proximo.valor == valor`) Auxilia processos
// que dependem de encontrar nós baseado em um valor. Deve retornar `nullptr`
// quando tal nó não existe.
ordered_list::no_encadeado* ordered_list::obter_no_anterior_a(int valor) {
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
