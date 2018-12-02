#include <stdio.h>

int b;
int c = 5;

int main(int ac, char **av)
{
  static int a;

  a = 5;

  printf("my static variable is %i", a);
  return (0);
}
