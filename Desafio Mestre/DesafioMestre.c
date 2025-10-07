#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5
#define MAXPILHA 3
int resMenu;
int contadorID=0;
typedef struct
{
  char nome[2];
  int id;
} Peca;

typedef struct
{
  Peca itens[MAX];
  int inicio;
  int fim;
  int total;
} Fila;

typedef struct
{
  Peca pilhas[MAXPILHA];
  int topo;
} Pilha;
  //FILA
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
    printf("[%s, %d] ", f->itens[idx].nome, f->itens[idx].id);
  }
  printf("\n");
}
//PILHA
Peca gerarPecaAleatoria (){
  Peca nova;
  char tipos[]= {'L', 'O', 'T', 'I'};

  nova.nome[0] = tipos[rand()%4];
  nova.nome[1] = '\0';    
  nova.id = contadorID++;
  return nova;
}
void inicializarPilha(Pilha *p)
{
  p->topo = -1;
}
int pilhaVazia(Pilha *p)
{
  return p->topo == -1;
}
int pilhaCheia(Pilha *p)
{
  return p->topo == MAXPILHA - 1;
}
void push(Pilha *p, Peca nova)
{
  if (pilhaCheia(p))
  {
    printf("Pilha cheia. Não é possível inserir\n");
    return;
  }
  p->topo++;
  p->pilhas[p->topo] = nova;
}
void pop(Pilha *p, Peca *removida)
{
  if (pilhaVazia(p))
  {
    printf("Pilha cheia. Não é possível remover\n");
    return;
  }
  *removida = p->pilhas[p->topo];
  p->topo--;
}
void peek(Pilha *p, Peca *visualizar)
{
  if (pilhaVazia(p))
  {
    printf("Pilha cheia. Não tem nada para visualizar\n");
    return;
  }
  *visualizar = p->pilhas[p->topo];
}
void mostrarPilha(Pilha *p)
{
  printf("Pilha de reserva  (Topo -> Base: ) ");
  for (int i = p->topo; i >= 0; i--)
  {

    printf("[%s %d]", p->pilhas[i].nome, p->pilhas[i].id);
    
  }
  printf("\n");
};
int mostrarMenu(Fila *f, Pilha *p){
      printf("===== Estado Atual =====\n");

  mostrarFila(f);
  mostrarPilha(p);
  printf("\n");
  printf("\n");
  printf("Opções\n");
  
  printf("1. Jogar peca da frente da fila\n");
  printf("2. Enviar peca da fila para reserva (pilha) \n");
  printf("3. Usar peca reserva (pilha)\n");
  printf("4. Trocar peca da frente da fila com o topo da pilha\n");
  printf("5. Trocar os 3 primeiros da fila com as 3 pecas da pilha\n");
  printf("0. Sair do game");
  scanf("%d", &resMenu);
  return resMenu;
}






int main()
{
  srand(time(NULL)); // garante números diferentes a cada execução
  Fila f;
  Pilha p;
  inicializarFila(&f); // Inicializa a fila
  inicializarPilha(&p);

  for (int i = 0; i < 4; i++)
{
  inserir(&f, gerarPecaAleatoria());
}

for (int i = 0; i < 3; i++)
{
  push(&p, gerarPecaAleatoria());
}
  do
  {
    mostrarMenu(&f,&p);
    // MOSTRAR O PRIMEIRO ITEM DA LISTA
    if (resMenu == 1)
    {
      if (filaVazia(&f))
      {
        printf("\n");
        printf("A fila está vazia!\n");
        printf("\n");
      }else{
      
      mostrarFila(&f);
      printf("O primeiro item: [%s %d]\n", f.itens[f.inicio].nome, f.itens[f.inicio].id);
      }
    }
    else if (resMenu == 2)
    {
      if (pilhaCheia(&p))
      {
        printf("A pilha está cheia, use uma peça para abrir espaço.\n");
        printf("\n");
        continue;
      }
      Peca removida;
      remover(&f, &removida);
      push(&p, removida);
      printf("\n");  
      printf("===== Novo Estado =====\n");
      mostrarFila(&f);
      mostrarPilha(&p);
    }
    else if (resMenu == 3)
    {
      if (pilhaVazia(&p))
      {
        printf("Você não tem reservas está vazia!\n");
        printf("\n");
      }
      else
      {
        Peca removida;
        pop(&p, &removida);
        printf("Peça reserva usada: %s\n", removida.nome);
      }
    }else if (resMenu == 4)
    { 
        if (filaVazia(&f) || pilhaVazia(&p)) {
    printf("Não é possível trocar, a fila ou a pilha estão vazias.\n");
    continue; // volta para o menu
    }
        Peca temp;
      temp = f.itens[f.inicio];
f.itens[f.inicio] = p.pilhas[p.topo];
p.pilhas[p.topo] = temp;
    }else if (resMenu == 5)
{
    if (f.total < 3 || p.topo < 2)
    {
        printf("Não há peças suficientes para trocar (precisa de 3 em cada).\n");
        continue;
    }

    // Trocar os 3 primeiros da fila com as 3 peças da pilha
    for (int i = 0; i < 3; i++)
    {
        int idxFila = (f.inicio + i) % MAX; // índice circular da fila
        int idxPilha = p.topo - i;          // de cima pra baixo na pilha

        // troca simples
        Peca temp = f.itens[idxFila];
        f.itens[idxFila] = p.pilhas[idxPilha];
        p.pilhas[idxPilha] = temp;
    }

    printf("===== Novo Estado =====\n");
    printf("As 3 primeiras peças da fila foram trocadas com as 3 peças da pilha!\n");
    mostrarFila(&f);
    mostrarPilha(&p);
}
    
  }
  while (resMenu != 0);
  printf("Saindo...");

  return 0;
}