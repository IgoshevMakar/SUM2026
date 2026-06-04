#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define MAX 3
INT P[MAX];
BOOL IsParty;

void Swap(int *i, int *j)
{
  int time_p;

  time_p = *j;
  *j = *i;
  *i = time_p;
}
VOID Store(VOID)
{
  int i;
  FILE *F;
  F = fopen("Prem.txt", "a");
  if (F == NULL)
    return;
  for (i = 0; i < MAX; i++)
    fprintf(F, " %d, ", P[i]);
  fprintf(F, "%d - parity: %s\n", P[MAX - 1], IsParty ? "even" : "odd");
  fclose(F);
}

int GO( INT Pos )
{
  int i;
  if (Pos == MAX)
  {
    Store();
    return;
  }
  else
  {
    for (i = Pos; i < MAX; i++)
    {
      Swap(&P[Pos], &P[i]);
      IsParty = !IsParty;
      GO(Pos + 1);
      //Swap(&P[Pos], &P[i]);
    }
    IsParty = !IsParty;
  }
}
void main( void )
{
  int i;
  for (i = 0; i < MAX; i++)
    P[i] = i + 1;
  GO(0);
}




