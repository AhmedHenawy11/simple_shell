#include <sys/wait.h>

#include <sys/types.h>

#include <unistd.h>

#include <stdlib.h>

#include <stdio.h>

#include <string.h>

int komal_cd(char **args);

int komal_help(char **args);

int komal_exit(char **args);

char *built_in_string[] =

{

  "cd",

  "help",

  "exit"

};

int (*built_in_function[]) (char **) =

{

&komal_cd,

&komal_help,

&komal_exit

};

int komal_builtins()

{

  return sizeof(built_in_string) / sizeof(char *);

}

  int komal_cd(char **args)

{

  if (args[1] == NULL)

{

fprintf(stderr, "komal: expected argument to 'cd'\n");

  }

else

{

  if (chdir(args[1]) != 0)

{

perror("komal");

   }

  }

  return 1;

}

int komal_help(char **args)

{

  int i;

printf("This is simple C shell build by Komal Batool\n");

printf("Type program names and arguments, and hit enter.\n");

printf("The following are built in:\n");

  for (i = 0; i < komal_builtins(); i++)

{

printf(" %s\n", built_in_string[i]);

}

printf("Use the man command for information on other programs.\n");

return 1;

}

int komal_exit(char **args)

{

return 0;

}

int komal_launch(char **args)

{

pid_t pid;

  int status;

pid = fork();

  if (pid == 0)

{

  if (execvp(args[0], args) == -1)

{

perror("komal");

  }

exit(EXIT_FAILURE);
 
  } else if (pid < 0)

{

  perror("komal");

}

  else

{

  do

{

waitpid(pid, &status, WUNTRACED);

    } while (!WIFEXITED(status) && !WIFSIGNALED(status));

  }

  return 1;

}

int komal_execute(char **args)

{

  int i;

  if (args[0] == NULL)

{

  return 1;

  }

  for (i = 0; i < komal_builtins(); i++) {

    if (strcmp(args[0], built_in_string[i]) == 0) {

      return (*built_in_function[i])(args);

  }

  }

  return komal_launch(args);

}

  char *komal_read_line(void)

{

#ifdef komal_USE_STD_GETLINE

  char *line = NULL;

ssize_t bufsize = 0;

  if (getline(&line, &bufsize, stdin) == -1)

{

if (feof(stdin))

{

  exit(EXIT_SUCCESS);

  }

else

{

perror("komal: getline\n");

exit(EXIT_FAILURE);

}

  }

  return line;

#else

#define komal_RL_BUFSIZE 1024

  int bufsize = komal_RL_BUFSIZE;

  int position = 0;

  char *buffer = malloc(sizeof(char) * bufsize);

  int c;

  if (!buffer) {

fprintf(stderr, "komal: allocation error\n");

  exit(EXIT_FAILURE);

  }

  while (1)

{

  c = getchar();

  if (c == EOF)

{

exit(EXIT_SUCCESS);

}

else if (c == '\n')

{

  buffer[position] = '\0';

  return buffer;

 } else {

  buffer[position] = c;

  }

  position++;

  if (position >= bufsize)

{

bufsize += komal_RL_BUFSIZE;

  buffer = realloc(buffer, bufsize);

  if (!buffer)

{

fprintf(stderr, "komal: allocation error\n");

exit(EXIT_FAILURE);

   }

  }

}

#endif

}

#define komal_TOK_BUFSIZE 64

#define komal_TOK_DELIM " \t\r\n\a"

char **komal_split_line(char *line)

{

  int bufsize = komal_TOK_BUFSIZE, position = 0;

  char **tokens = malloc(bufsize * sizeof(char*));

  char *token, **tokens_backup;

  if (!tokens)

{

fprintf(stderr, "komal: allocation error\n");

exit(EXIT_FAILURE);

  }

  token = strtok(line, komal_TOK_DELIM);

  while (token != NULL)

{

  tokens[position] = token;

  position++;
 
  if (position >= bufsize)

{

bufsize += komal_TOK_BUFSIZE;

  tokens_backup = tokens;

  tokens = realloc(tokens, bufsize * sizeof(char*));

if (!tokens)

{

free(tokens_backup);

fprintf(stderr, "komal: allocation error\n");

exit(EXIT_FAILURE);

    }

  }

    token = strtok(NULL, komal_TOK_DELIM);

  }

  tokens[position] = NULL;

  return tokens;

}

void komal_loop(void)

{

  char *line;
 
  char **args;

  int status;

  do

{

printf("> ");

  line = komal_read_line();

args = komal_split_line(line);

  status = komal_execute(args);

  free(line);

  free(args);

  } while (status);

}

int main(int argc, char **argv)

{

komal_loop();

  return EXIT_SUCCESS;

}