// SHAE C Unix Shell
// Authentic C - Unix-style command shell

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_ARGS 64
#define BUFFER_SIZE 1024

const char *PAPER = "\033[48;2;242;238;229m";
const char *INK = "\033[38;2;25;23;18m";
const char *OXIDE = "\033[38;2;179;52;27m";
const char *RESET = "\033[0m";

void print_prompt(void) {
    printf("%s%sSHAE%s> %s%s", OXIDE, INK, RESET, PAPER, RESET);
    fflush(stdout);
}

int execute_command(char **args) {
    if (args[0] == NULL) return 1;
    
    if (strcmp(args[0], "exit") == 0) {
        return 0;
    }
    
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "shae: expected argument to cd\n");
        } else if (chdir(args[1]) != 0) {
            perror("shae");
        }
        return 1;
    }
    
    if (strcmp(args[0], "help") == 0) {
        printf("%sSHAE Unix Shell%s\n", INK, RESET);
        printf("Built-in commands: cd, help, exit\n");
        printf("External commands are executed via execvp\n");
        return 1;
    }
    
    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("shae");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("shae");
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
    return 1;
}

char **tokenize(char *line) {
    int bufsize = MAX_ARGS;
    int pos = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;
    
    token = strtok(line, " \t\r\n\a");
    while (token != NULL) {
        tokens[pos] = token;
        pos++;
        if (pos >= bufsize) {
            bufsize += MAX_ARGS;
            tokens = realloc(tokens, bufsize * sizeof(char*));
        }
        token = strtok(NULL, " \t\r\n\a");
    }
    tokens[pos] = NULL;
    return tokens;
}

char *read_line(void) {
    char *line = readline("");
    if (line && *line) {
        add_history(line);
    }
    return line;
}

int main(int argc, char **argv) {
    char *line;
    char **args;
    int status;

    printf("%s═══ SHAE C Unix Shell ═══%s\n", OXIDE, RESET);
    printf("Type 'help' for built-in commands, 'exit' to quit\n\n");

    do {
        print_prompt();
        line = read_line();
        args = tokenize(line);
        status = execute_command(args);
        
        free(line);
        free(args);
    } while (status);

    return EXIT_SUCCESS;
}
