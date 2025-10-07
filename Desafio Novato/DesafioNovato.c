#include <stdio.h>
#include <stdlib.h>

#define MAX 5
int resMenu;
typedef struct
{
  char nome[2];

} Peca;
typedef struct
{
  Peca itens[MAX];
  int inicio;
  int fim;
  int total;
} Fila;
void inserir(Fila *f, Peca p)
{
  if (f->total == MAX)
  {
    printf("Fila cheia. Não é possível inserir.\n");
    return;
  }

  f->itens[f->fim] = p;
  f->fim = (f->fim + 1) % MAX;
  f->total++;
}
int filaCheia(Fila *f)
{
  return f->total == MAX;
}
int filaVazia(Fila *f)
{
  return f->total == 0;
}
void inicializarFila(Fila *f)
{
  f->inicio = 0;
  f->fim = 0;
  f->total = 0;
}
void remover(Fila *f, Peca *p)
{
  if (filaVazia(f))
  {
    printf("Fila vazia. Não é possível remover.\n");
    return;
  }

  *p = f->itens[f->inicio];
  f->inicio = (f->inicio + 1) % MAX;
  f->total--;
}
void mostrarFila(Fila *f)
{
  printf("Fila: ");
  for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX)
  {
    printf("[%s, %d] ", f->itens[idx].nome, idx);
  }
  printf("\n");
}
void mostrarMenu()
{
  printf("===== MENU =====\n");
  printf("1. Jogar uma peça \n");
  printf("2. Inserir nova peça \n");
  printf("3. Mostrar fila\n");
  printf("0. Sair do game");
  scanf("%d", &resMenu);
}
int main()
{
  Fila f;
  inicializarFila(&f); // Inicializa a fila

  do
  {
    mostrarMenu();
    if (resMenu == 1)
    {
      if (filaVazia(&f))
      {
        printf("\n");
        printf("A fila está vazia!\n");
        printf("\n");
      }else{
      // Remove uma pessoa da fila
      Peca removida;
      remover(&f, &removida); // Aqui usamos a função de remoção
      printf("Peca removida: %s\n", removida.nome);
      printf("\n");
    }

    }
    else if (resMenu == 2)
    {
      Peca nova;
      printf("Digite o nome da peça(1 caractere): ");
      scanf("%s", nova.nome);

      inserir(&f, nova);
      mostrarFila(&f);
    }
    else if (resMenu == 3){
      if (filaVazia(&f))
      {
        printf("A fila está vazia!\n");
        printf("\n");
      }else{
      mostrarFila(&f);
    }
    }

  } while (resMenu != 0);
  printf("Saindo...");

  return 0;
}