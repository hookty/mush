#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 2048
#define MAX_WORDS 128

void run_command(char **words)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        execvp(words[0], words);
        perror("execvp failed");
        exit(1);
    }
    else
    {
        wait(NULL);
    }
}

int main()
{
    char line[MAX_LINE_LENGTH];
    char *words[MAX_WORDS + 1]; // +null
    char *word;
    int i;

    while (1)
    {
        printf("mush> ");
        fgets(line, MAX_LINE_LENGTH, stdin);

        i = 0;
        word = strtok(line, " \n\t\r");
        while (word != NULL)
        {
            words[i] = word;
            i++;
            word = strtok(NULL, " \n\t\r");
        }
        words[i] = NULL;

        if (strcmp(words[0], "exit") == 0)
        {
            exit(0);
        } else if (strcmp(words[0], "cd") == 0)
        {
            if (chdir(words[1]) != 0)
            {
                perror("chdir failed");
            }
        }
        else
        {
            run_command(words);
        }
    }

    return 0;
}
