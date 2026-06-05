#include <stdio.h>
#include <stdlib.h>
#include <wndows.h>


typedef DOUBLE DBL;

#define MAX 3
DBL A[MAX][MAX];
INT N;

INT P[MAX];
BOOL IsParity;

BOOL LoadMatrix( CHAR *FileName )
{
  FILE *F;
  INT i, j;

  N = 0;
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  fscanf(F, "%d", &N);
  if (N < 0)
    N = 0;
  else
    if (N > MAX)
      N = MAX;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      fcanf(F, "%lf", &A[i][j]);

  fclose(F);
  return TRUE;
}
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
      Swap(&P[Pos], &P[i]);
    }
    IsParty = !IsParty;
  }
}

void main( void )
{

}
