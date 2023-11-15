#include "main.h"
#include <stdarg.h>
#include <stddef.h>

extern char **environ;

char *my_getenv(const char *name) {
    size_t name_length;
    char **env;
    if (name == NULL || environ == NULL) {
        return NULL;
    }

    name_length = _strlen(name);

    env = environ;
    while (*env != NULL) {
        if (strncmp(*env, name, name_length) == 0 && (*env)[name_length] == '=') {
            return &(*env)[name_length + 1];
        }
        env++;
    }

    return NULL;
}



char *_strdup(const char *s) {
    size_t len = _strlen(s) + 1;
    char *dup = malloc(len);

    if (dup != NULL) {
        _strcpy(dup, s);
    }

    return dup;
}
int _tolower(int c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}
int _strcasecmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && _tolower(*s1) == _tolower(*s2)) {
        s1++;
        s2++;
    }

    return _tolower(*s1) - _tolower(*s2);
}

char *_strcpy(char *dest, const char *src) {
    char *d = dest;
    while ((*d++ = *src++))
        ;
    return dest;
}

char *_strcat(char *dest, const char *src) {
    char *d = dest;
    while (*d)
        d++;
    while ((*d++ = *src++))
        ;
    return dest;
}

int _fprintf(FILE *stream, const char *format, ...) {
    va_list args;
    char buffer[1024];
 
    va_start(args, format);


    vsnprintf(buffer, sizeof(buffer), format, args);

    write(fileno(stream), buffer, strlen(buffer));

    va_end(args);
    return 0;
}




int _printf(const char *format, ...) {
    va_list args;
    char buffer[1024];

    va_start(args, format);


    vsnprintf(buffer, sizeof(buffer), format, args);

    write(STDOUT_FILENO, buffer, strlen(buffer));

    va_end(args);
    return 0;
}



int _strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

size_t _strlen(const char *s) {
    const char *p = s;
    while (*p)
        p++;
    return p - s;
}

int _vsnprintf(char *str, size_t size, const char *format, va_list args) {
    int count = 0;
    int written = 0;

    while (format[count] && written < (int)size - 1) {
        if (format[count] == '%' && format[count + 1] == 's') {
            const char *arg = va_arg(args, const char *);
            int len = _strlen(arg);
            if (written + len < (int)size) {
                while (*arg)
                    str[written++] = *arg++;
            } else {
                while (written < (int)size - 1)
                    str[written++] = '*';
                break;
            }
            count += 2;
        } else {
            str[written++] = format[count++];
        }
    }

    str[written] = '\0';

    return written;
}