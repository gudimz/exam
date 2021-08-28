#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

/*
*This for test
*Start!!!
*/

#ifdef TEST_SH
# define TEST		1
#else
# define TEST		0
#endif

/*
*This for test
*End!!!
*/

size_t ft_strlen(char *str) {
	size_t len = 0;

	while(str[len]) {
		++len;
	}
	return len;
}

void ft_error_fatal(char *message) {
	write(2, message, ft_strlen(message));
	exit(1);
}

void ft_error_builtin(char *message, char *path) {
	if (!path) {
		write(2, message, ft_strlen(message));
	} else {
		write(2, message, ft_strlen(message));
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
	}
}

void ft_cd(char **line) {
	size_t i = 0;
	while (line[i]) {
		++i;
	}
	if (i != 2) {
		ft_error_builtin("error: cd: bad arguments\n", NULL);
		return;
	}
	if (chdir(line[1])) {
		ft_error_builtin("error: cd: cannot change directory to ", line[1]);
	}

}

int main(int argc, char **argv, char **env) {
	int i = 1;
	char **line = NULL;
	size_t size = 0;
	size_t len = 0;
	int is_pipe = 0;
	int fd[2];
	int save_0 = 0;
	int save_1 = 0;
	pid_t pid = 0;
	int opened = 0;
	int status = 0;

	if (argc < 2) {
		return 0;
	}
	while (i < argc) {
		if (!strcmp(argv[i], ";") || !strcmp(argv[i], "|")) {
			++i;
			continue;
		}
		size = 0;
		while (argv[i + size] && strcmp(argv[i + size], ";") && strcmp(argv[i + size], "|")) {
			++size;
		}
		if (!(line = (char **)malloc(sizeof(char *) * (size + 1)))) {
			ft_error_fatal("error: fatal\n");
		}
		line[size] = NULL;
		len = 0;
		while (len < size) {
			line[len] = argv[i];
			++len;
			++i;
		}
		if (argv[i] && !strcmp(argv[i], "|")) {
			is_pipe = 1;
		} else {
			is_pipe = 0;
		}
		if (opened) {
			save_0 = dup(0);
			dup2(fd[0], 0);
			close(fd[0]);
		}
		if (is_pipe) {
			if (pipe(fd)) {
				ft_error_fatal("error: fatal\n");
			}
			save_1 = dup(1);
			dup2(fd[1], 1);
			close(fd[1]);
		}
		pid = fork();
		if (pid < 0) {
			ft_error_fatal("error: fatal\n");
		} else if (pid == 0) {
			if (!strcmp(line[0], "cd")) {
				ft_cd(line);
			} else if (execve(line[0], line, env)) {
				ft_error_builtin("error: cannot execute ", line[0]);
			}
			exit(0);
		} else {
			waitpid(pid, &status, 0);
		}
		if (opened) {
			dup2(save_0, 0);
			close(save_0);
			opened = 0;
		}
		if (is_pipe) {
			dup2(save_1, 1);
			close(save_1);
			opened = 1;
		}
		free(line);
	}

/*
*This for test
*Start!!!
*/
    if (TEST)
		while (1);
/*
*This for test
*End!!!
*/
	return 0;
}