#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Allocates memory for the returning string.
char* replicar(char* origin, int index1, int index2, int cantidadRepes){

  int stringLength = strlen(origin);

  // Worst case scenario, we need (strlen(origin) * cantidadRepes) + 1 bytes of memory.

  char* toReturn = calloc((stringLength * cantidadRepes) + 1, sizeof(char));

  int i = 0;
  int reps = 0;
  int index = 0;

  while(i < stringLength){
    toReturn[index] = origin[i];

    i++;
    index++;
    if(i > index2 && (reps < cantidadRepes - 1)){
      i = index1;
      reps++;
    }
  }

  return toReturn;
}

int main(){

  char* original = "Hola";
  char* copy = replicar(original, 1, 2, 3);
  printf("String: %s \n", copy);
  free(copy);
}
