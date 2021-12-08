#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void forkexample(int num1, int num2, int num2_mitad)
{
  int fd1[2], fd2[2];

  pipe(fd1);
  pipe(fd2);

  if (fork() == 0)
  {
    //-----------Child Process 1-----------
    printf("Hello from Child1! %d\n", getpid());
    // Close read from pipe1
    close(fd1[0]);
    unsigned long int value1 = 0;
    for (int i = 0; i <= num2_mitad; i++)
    {
      value1 += i;
    }
    write(fd1[1], &value1, sizeof(value1));
    exit(0);
  }
  else
  {
    if (fork() == 0)
    {
      //-----------Child Process 2-----------
      printf("Hello from Child2! %d\n", getpid());
      // Close read from pipe2
      close(fd2[0]);
      unsigned long int value2 = 0;
      for (int i = num2_mitad; i <= num2; i++)
      {
        value2 += i;
      }

      write(fd2[1], &value2, sizeof(value2));
      exit(0);
    }
    close(fd1[1]);
    close(fd2[1]);
    unsigned long int buf_read[2];

    read(fd1[0], &buf_read[0], sizeof(unsigned long int));
    read(fd2[0], &buf_read[1], sizeof(unsigned long int));

    unsigned long int suma_total = buf_read[0] + buf_read[1] + num1;

    pid_t cpid = wait(NULL);
    pid_t cpid2 = wait(NULL);
    printf("Hello from Parent!, pid: %d, value1: %ld, value2: %ld, sumatotal: %ld\n", getpid(), buf_read[0], buf_read[1], suma_total);
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
