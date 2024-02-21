#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 32
#define MAX_LINE_LENGTH 1024

// Built-in functions
int echo(int argc, char **argv);
int cd(int argc, char **argv);
int pwd(int argc, char **argv);
int export(int argc, char **argv);
int unset(int argc, char **argv);
int env(int argc, char **argv);
int exit_shell(int argc, char **argv);

// Built-in function prototypes
typedef int (*builtin_func)(int argc, char **argv);

// Built-in function table
builtin_func builtins[] = {
    &echo,
    &cd,
    &pwd,
    &export,
    &unset,
    &env,
    &exit_shell
};

// Number of built-in functions
int num_builtins = sizeof(builtins) / sizeof(builtin_func);

// Parse command line into arguments
char **parse_args(char *line) {
    char **args = malloc(sizeof(char *) * MAX_ARGS);
    char *arg;
    int i = 0;

    arg = strtok(line, " ");
    while (arg != NULL) {
        args[i++] = arg;
        arg = strtok(NULL, " ");
    }

    args[i] = NULL;
    return args;
}

// Execute a command
int execute_command(char **args) {
    pid_t pid;
    int status;

    // Check for built-in functions
    for (int i = 0; i < num_builtins; i++) {
        if (strcmp(args[0], builtins[i]->__name__) == 0) {
            return builtins[i](argc, argv);
        }
    }

    // Fork a child process
    pid = fork();
    if (pid == 0) {
        // Child process
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        waitpid(pid, &status, 0);
        return status;
    } else {
        // Fork failed
        perror("fork");
        return EXIT_FAILURE;
    }
}

// Main loop
int main() {
    char line[MAX_LINE_LENGTH];
    char **args;
    int status;

    // Main loop
    while (1) {
        // Print prompt
        printf("minishell> ");

        // Read command line
        fgets(line, MAX_LINE_LENGTH, stdin);

        // Parse command line
        args = parse_args(line);

        // Execute command
        status = execute_command(args);

        // Free memory
        free(args);
    }

    return 0;
}
// Built-in Functions

// Echo
int echo(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        printf("%s", argv[i]);
        if (i < argc - 1) {
            printf(" ");
        }
    }
    printf("\n");
    return 0;
}

// Change directory
int cd(int argc, char **argv) {
    if (argc == 1) {
        chdir(getenv("HOME"));
    } else {
        chdir(argv[1]);
    }
    return 0;
}

// Print working directory
int pwd(int argc, char **argv) {
    char cwd[MAX_LINE_LENGTH];
    getcwd(cwd, MAX_LINE_LENGTH);
    printf("%s\n", cwd);
    return 0;
}

// Export environment variable
int export(int argc, char **argv) {
    if (argc == 1) {
        // List all environment variables
        for (char **env = environ; *env != NULL; env++) {
            printf("%s\n", *env);
        }
    } else {
        // Set environment variable
        setenv(argv[1], argv[2], 1);
    }
    return 0;
}

// Unset environment variable
int unset(int argc, char **argv) {
    if (argc == 1) {
        printf("Usage: unset <variable>\n");
        return 1;
    } else {
        unsetenv(argv[1]);
    }
    return 0;
}

// Print environment variables
int env(int argc, char **argv) {
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
    return 0;
}

// Exit shell
int exit_shell(int argc, char **argv) {
    exit(EXIT_SUCCESS);
}
