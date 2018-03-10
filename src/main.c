// EA876A 2018/s1
// Lab01 - Somador de Números
// GABRIELA AKEMI SHIMA - RA135819

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define TAMANHO_MAX 50

float str2float (char *str);
float fatorial(float num);

int main () {

  char string[TAMANHO_MAX], num[TAMANHO_MAX];
  int i = 0, j = 0, k = 0;
  float fat, somatorio = 0, numeros_convertidos[TAMANHO_MAX];
  int estado = 0;

  // printf ("-------------------------\n");
  // printf("Entre com a string: ");
  fgets (string, TAMANHO_MAX, stdin);
  //printf ("string lida: %s \n", string);
  //printf ("-------------------------\n");

  while(string[i] != '\0') {
    switch (estado) {

      case 0 :
        //printf("Estado (0) - estado (%d)  |  string[i] = %c\n", estado, string[i]);
        if(string[i] == ' ') {
          estado = 0;
        }
        else if(('0' <= string[i] && string[i] <= '9') || string[i] == '.')  {
          estado = 1;
        }
        else  {
          estado = 3;
          for(int g = j ; g >= 0; --g) { //limpa o vetor auxiliar [char*]num
            num[g] = 0;
          }
          j = 0;
        }
      break;

      case 1 :
        //printf("Estado (1) - estado (%d)  |  string[i] = %c\n", estado, string[i]);
        if(string[i] == ' ' || string[i] == '\n' || string[i] == '\0') {
          estado = 2;
          num[j] = string[i-1];
          ++j;
          num[j] = '\0';
          numeros_convertidos[k] = str2float(num); //transforma [char*]num em float
          k++;
          //printf("num[%d] = %s foi armazenado em numeros_convertidos[%d] = %.2f\n", j-1, num, k-1, numeros_convertidos[k-1]);
          for(int g = j ; g >= 0; --g) { //limpa o vetor auxiliar [char*]num
            num[g] = 0;
          }
          j = 0;
        }
        else if (('0' <= string[i] && string[i] <= '9') || string[i] == '.') {
          estado = 1;
          num[j] = string[i-1]; //armazeno digito no vetor num
          ++j;
        }
        else if(string[i] == '!'){
          estado = 4;
          num[j] = string[i-1]; //armazeno digito no [char*]vetor num
          ++j;
          numeros_convertidos[k] = str2float(num); //transforma [char*]num em float
          k++;
        }
        else  {
          estado = 3;
          for(int g = j ; g >= 0; --g) { //limpa o vetor auxiliar [char*]num
            num[g] = 0;
          }
          j = 0;
        }
      break;

      case 2 :
        //printf("Estado (2) - estado (%d)  |  string[i] = %c\n", estado, string[i]);
        if(string[i] == ' ' || string[i] == '\n' || string[i] == '\0') {
          estado = 0;
        }
        else if (('0' <= string[i] && string[i] <= '9') || string[i] == '.') {
          estado = 1;
        }
        else  {
          estado = 3;
          for(int g = j ; g >= 0; --g) { //limpa o vetor auxiliar [char*]num
            num[g] = 0;
          }
          j = 0;
        }
      break;

      case 3 :
        //printf("Estado (3) - estado (%d)  |  string[i] = %c\n", estado, string[i]);
        if(string[i] == ' ' || string[i] == '\n' || string[i] == '\0') {
          estado = 0;
        }
        else  {
          estado = 3;
          for(int g = j ; g >= 0; --g) { //limpa o vetor auxiliar [char*]num
            num[g] = 0;
          }
          j = 0;
        }
      break;

      case 4:
        //printf("Estado (4) - estado (%d)  |  string[i] = %c\n", estado, string[i]);
        if(string[i] == ' ' || string[i] == '\n' || string[i] == '\0') {
          estado = 2;
          //printf("numeros_convertidos[%d] = %.2f  |  fatorial: %.2f\n", k-1,numeros_convertidos[k-1], fatorial(numeros_convertidos[k-1]) );
          numeros_convertidos[k-1] = fatorial(numeros_convertidos[k-1]);
          for(int g = j ; g >= 0; --g) { //limpa o vetor auxiliar [char*]num
            num[g] = 0;
          }
          j = 0;
        }
        else  {
          estado = 3;
          numeros_convertidos[k-1] = 0;
          --k;
          for(int g = j ; g >= 0; --g) { //limpa o vetor auxiliar [char*]num
            num[g] = 0;
          }
          j = 0;
        }
      break;
    }
    ++i;
  }

  for(int g = 0 ; g < k; ++g){ //somatório
    somatorio = somatorio + numeros_convertidos[g];
  }
  printf("%.2f\n", somatorio);
  //printf ("\n-------------------------\n");
  //printf("Fim do programa!\n");

  return 0;

}

float str2float (char *num) {
  /*
  Eu tinha feito uma função, mas ela começou a dar erro. Então substituí por
  esse código que encontrei para implementação de um atof. )':
  Source: http://crackprogramming.blogspot.com.br/2012/10/implement-atof.html
  Acessado: 09/03/2018 às 18:03
  */
  if (!num || !*num) {
     return 0;
   }
     float integerPart = 0;
     float fractionPart = 0;
     int divisorForFraction = 1;
     int sign = 1;
     bool inFraction = false;
     /*Take care of +/- sign*/
     if (*num == '-')
     {
         ++num;
         sign = -1;
     }
     else if (*num == '+')
     {
         ++num;
     }
     while (*num != '\0')
     {
         if (*num >= '0' && *num <= '9')
         {
             if (inFraction)
             {
                 /*See how are we converting a character to integer*/
                 fractionPart = fractionPart*10 + (*num - '0');
                 divisorForFraction *= 10;
             }
             else
             {
                 integerPart = integerPart*10 + (*num - '0');
             }
         }
         else if (*num == '.')
         {
             if (inFraction)
                 return sign * (integerPart + fractionPart/divisorForFraction);
             else
                 inFraction = true;
         }
         else
         {
             return sign * (integerPart + fractionPart/divisorForFraction);
         }
         ++num;
     }
     return sign * (integerPart + fractionPart/divisorForFraction);
}

float fatorial(float num) {
  float fat = 1;
  for(int i = 1; i <= num; ++i) {
    fat = fat*i;
  }
  return fat;
}
