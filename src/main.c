#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void forkexample(int num1, int num2, int num2_mitad)
{
  int fd1[2];
  pipe(fd1);

  if (fork() == 0)
  {
    //-----------Child Process 1-----------
    printf("Hello from Child1! %d\n", getpid());
    // Close read from pipe1
    close(fd1[0]);
    unsigned long int result_child = 0;
    for (int i = 0; i <= num2_mitad; i++)
    {
      result_child += i;
    }
    write(fd1[1], &result_child, sizeof(result_child));
    exit(0);
  }
  else
  {
    unsigned long int result_parent = 0;
    for (int i = num2_mitad; i <= num2; i++)
    {
      result_parent += i;
    }
    close(fd1[1]);
    unsigned long int result_child;
    read(fd1[0], &result_child, sizeof(result_child));
    unsigned long int suma_total = result_child + result_parent + num1;

    pid_t cpid = wait(NULL);
    printf("Hello from Parent!, pid: %d, value1: %ld, value2: %ld, sumatotal: %ld\n", getpid(), result_child, result_parent, suma_total);
  }
}

int main()
{
  int num1, num2;
  scanf("%d %d", &num1, &num2);
  int num2_mitad = num2 / 2;
  forkexample(num1, num2, num2_mitad);
  return 0;
}
