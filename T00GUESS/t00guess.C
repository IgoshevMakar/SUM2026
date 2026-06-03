/* Igoshev Makar, 10-6, 01.06.2026 */
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void main( void )
{
  int a = 0, b = 100, mid;
  char sd[40];

  MessageBox(NULL, "chose nomber 1-100", "start game", MB_OK);
  while (b - a > 1)
  {
    mid = (a + b) / 2;
    sprintf(sd, "your nomber more than %i", mid);
    if (MessageBox(NULL, sd, "start game", MB_YESNOCANCEL) == IDYES)
      a = mid + 1;
    else
      if (MessageBox(NULL, sd, "start game", MB_YESNOCANCEL) == IDNO)
        b = mid - 1;
      else
      {
        sprintf(sd, "your nomber is %i", mid);
        MessageBox(NULL, sd, "start game", MB_OK);
      }
      return 0;
    
  }

}