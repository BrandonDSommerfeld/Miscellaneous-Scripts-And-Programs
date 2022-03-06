/*
 * @brief This file should be called with an argument 
 * specifying the length of the password to be generated
 * Must be greater than 0.
 *
 * The -o flag is used to specify the file to 
 * output the password to, creating it if it does 
 * not already exist, other sent to stdout
 * 
 * Passwords are created using a set of 
 * printable ASCII values which were 
 * chosen to avoid ambiguity
 *
 * @author Brandon Sommerfeld <bdsommerfeld@gmail.com>
 */


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void print_error()
{
  fprintf(stderr, "Usage: len [-o filepath]\n");
}

char random_char ()
{
  char c;
  switch (rand() % 4)
  {
    //Numbers
    case 0:
      return 48 + (rand() % 10);
    //Lowercase
    case 1:
      return 97 + (rand() % 26);
    //Uppercase
    case 2: 
      return 65 + (rand() % 26);
    //Special characters
    default:
      c = rand() % 32;
      if(c < 15) return 33 + c;
      if(c < 22) return 43 + c;
      if(c < 28) return 69 + c;
      return 95 + c;
  }
}

int main (int argc, char **argv)
{
  if(argc != 2 && argc != 4)
  {
    print_error();
    return 1;
  }
  time_t t;
  srand((unsigned int) time(&t));

  unsigned int num_chars;
  char *file_path = NULL;
  int c;
  while((c = getopt(argc, argv, "o:")) != -1)
  {
    switch (c)
    {
      case 'o':
        file_path = optarg;
        break;
      default:
        print_error();
        return 1;
    }
  }
  num_chars = atoi(argv[optind]);
  if(num_chars == 0)
  {
    print_error();
    return 1;
  }
  
  int output_fd = STDOUT_FILENO;
  if(file_path != NULL)
  {
    output_fd = open(file_path, O_CREAT | O_WRONLY | O_TRUNC, 
                     S_IRWXU | S_IRGRP | S_IROTH); 
    if(output_fd < 0)
    {
      fprintf(stderr, "%s\n", strerror(errno));
      return 1;
    }
  }

  for(unsigned int i = 0; i < num_chars; i++)
  {
    char d = random_char();
    dprintf(output_fd, "%c", d);
  }
  dprintf(output_fd, "\n");
  return 0;
}
