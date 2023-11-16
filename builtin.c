#include "main.h"
#include <stddef.h>


int _strncmp(const char *s1, const char *s2, size_t n) {
    while (n > 0 && (*s1 != '\0' || *s2 != '\0')) {
        if (*s1 != *s2) {
            return *(unsigned char *)s1 - *(unsigned char *)s2;
        }
        s1++;
        s2++;
        n--;
    }
    return 0;
}

char *_getenv(const char *name) {
    size_t name_length;
    char **env;

    if (name == NULL || environ == NULL) {
        return NULL;
    }

    name_length = _strlen(name);

    env = environ;
    while (*env != NULL) {
        if (_strncmp(*env, name, name_length) == 0 && (*env)[name_length] == '=') {
            return &(*env)[name_length + 1];
        }
        env++;
    }

    return NULL;
}


char *_strdup(char *str)
{
	int i, l;
	char *new;

	if (!str)
	{
		return (NULL);
	}
	for (l = 0; str[l] != '\0';)
	{
		l++;
	}
	new = malloc(sizeof(char) * l + 1);
	if (!new)
	{
		return (NULL);
	}
	for (i = 0; i < l; i++)
	{
		new[i] = str[i];
	}
	new[l] = str[l];
	return (new);
}

int _putchar(char c)
{
	return (write(1, &c, 1));
}
int _tolower(int c) {
	if (c >= 'A' && c <= 'Z')
		return c - 'A' + 'a';
	else
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

int _vsnprintf(char *str, size_t size, const char *format, va_list args) {
    int written = 0;
    int result;

    if (str == NULL || format == NULL || size == 0) {
        return -1;
    }

    result = vsnprintf(str, size, format, args);

    if (result >= 0 && (size_t)result < size) {
        written = result;
    } else {
        str[size - 1] = '\0';
        written = size - 1;
    }

    return written;
}
int _fprintf(FILE *stream, const char *format, ...) {
    va_list args;
    char buffer[1024];

    va_start(args, format);


    _vsnprintf(buffer, sizeof(buffer), format, args);

    write(fileno(stream), buffer, _strlen(buffer));

    va_end(args);
    return 0;
}



int _printf(const char *format, ...) {
  va_list args;
  int num_printed = 0;
  va_start(args, format);
  while (*format) {
    if (*format == '%') {
      switch (*++format) {
        case 'd':
          num_printed += _fprintf(stdout, "%d", va_arg(args, int));
          break;
        case 'f':
          num_printed += _fprintf(stdout, "%f", va_arg(args, double));
          break;
        case 's':
          num_printed += _fprintf(stdout, "%s", va_arg(args, char *));
          break;
        default:
          _fprintf(stdout, "%%");
          num_printed += 1;
          break;
      }
    } else {
      _putchar(*format);
      num_printed += 1;
    }

    format++;
  }

  va_end(args);

  return num_printed;
}

size_t _strlen(const char *str) {
    const char *s = str;
    while (*s != '\0') {
        s++;
    }
    return s - str;
}
int _strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}