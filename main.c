/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#define NRBANCNOTE 7

struct Bancnote
{
  int value;
  int count;
};

void
sortDesc (struct Bancnote bancnote[NRBANCNOTE])
{
  struct Bancnote temp;
  int i, j;
  for (i = 0; i < NRBANCNOTE - 1; i++)
    {
      for (j = 0; j < NRBANCNOTE - 1 - i; j++)
	{
	  if (bancnote[j].value < bancnote[j + 1].value)
	    {
	      temp = bancnote[j + 1];
	      bancnote[j + 1] = bancnote[j];
	      bancnote[j] = temp;
	    }
	}
    }
}

int main ()
{
  int suma_extragere = 0;
  char new_extragere;

  struct Bancnote bancnote[NRBANCNOTE];
  struct Bancnote bancnote_extragere[NRBANCNOTE];

  int total_bancnote = 0;

  // numele fisierului de intrare
  char input_filename[] = "BANI.IN";

  // deschidere fisier de intrare pentru
  // citire (r) in modul text (t)
  FILE *in = fopen (input_filename, "rt");

  // verific daca fisierul a fost deschis cu succes
  // altfel opresc executia (in cazul acestei probleme)
  if (in == NULL)
    {
      fprintf (stderr, "ERROR: Can't open file %s", input_filename);
      return -1;
    }
  //citesc din fisier pana la sfarsit
  int nr, i, j;
  i = j = 0;
  while (fscanf (in, "%d", &nr) == 1)
    {
      //salvez in tabel
      if (j == 0)
	bancnote[i].count = nr;
      else
	bancnote[i].value = nr;
      j++;
      if (j % 2 == 0)
	{
	  i++;
	  j = 0;
	}
    }

  //inchid fisierul de intrare
  fclose (in);

  //sortez descrescator bancnotele
  sortDesc (bancnote);


  do
    {
        total_bancnote = 0;
      do
      {
          printf("Introduceti suma de bani pe care doriti sa o extrageti de la bancomat: ");
          scanf ("%d", &suma_extragere);
          if (suma_extragere >= 100000 || suma_extragere < 1)
          {
              printf("Suma extrasa trebuie sa fie cuprinsa intre 0 si 100000 \n\n");
          }
        }while (suma_extragere >= 100000 || suma_extragere < 1);
        
        printf ("Doriti sa extrageti %d lei \n", suma_extragere);
        for (i = 0; i < NRBANCNOTE; i++)
        {
            int counter = 0;
            if (suma_extragere >= bancnote[i].value)
            {
                counter = suma_extragere / bancnote[i].value;
                if (counter < bancnote[i].count)
                {
                    bancnote[i].count = bancnote[i].count - counter;
                }
                else
                {
                    counter = bancnote[i].count;
                    bancnote[i].count = 0;
                }
                suma_extragere = suma_extragere - counter * bancnote[i].value;
                total_bancnote = total_bancnote + counter;
            }
            bancnote_extragere[i].count = counter;
            bancnote_extragere[i].value = bancnote[i].value;
        }
        printf ("Numarul minim de bancnote pentru extragerea sumei este: %d \n",
	      total_bancnote);
	      for (i = 0; i < NRBANCNOTE; i++)
	      {
	          if (bancnote_extragere[i].count != 0)
	          {
	              printf ("Bancnote de %d : %d \n", bancnote_extragere[i].value,
	              bancnote_extragere[i].count);
	          }
	      }
	     
	      printf ("Doriti sa faceti o noua extragere (Y/N): ");
	      scanf (" %c", &new_extragere);
    } while (new_extragere == 'Y' || new_extragere == 'y');
    
    for (i = 0; i < NRBANCNOTE; i++)
    {
      printf ("%d - %d\n", bancnote[i].value, bancnote[i].count);
    }

  return 0;
}
