#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str);
char	*ft_strcpy(char *dest, const char *src);
int	ft_strcmp(const char *s1, const char *s2);
ssize_t	ft_write(int fd, const void *buf, size_t n);
ssize_t	ft_read(int fd, void *buf, size_t n);
char	*ft_strdup(const char *s);


int main(void)
{
	// STRLEN TEST
	printf("--------------------\nFT_STRLEN TEST\n--------------------\n");
	char	*a1 = "libasm";
	char	*a2 = "";
	printf("ft_strlen(\"%s\"): %zu\n", a1, ft_strlen(a1));
	printf("strlen(\"%s\")   : %zu\n", a1, strlen(a1));
	printf("--------------------\n");
	printf("ft_strlen(empty): %zu\n", ft_strlen(a2));
        printf("strlen(empty)   : %zu\n", strlen(a2));
	printf("--------------------\n");

	// STRCPY TEST
	printf("--------------------\nFT_STRCPY TEST\n--------------------\n");
	char	b1[10] = "";
        char	b2[10] = "";
        char	b3[] = "yeye";
	printf("strcpy(\"\", \"%s\"): %s\n", b3, strcpy(b1, b3));
	printf("ft_strcpy(\"\", \"%s\"): %s\n", b3, ft_strcpy(b2, b3));
	printf("--------------------\n");

	// STRCMP TEST
	printf("--------------------\nFT_STRCMP TEST\n--------------------\n");

	const char	*c1 = "abc";
	const char	*c2 = "abc";
	const char	*c3 = "abd";
	const char	*c4 = "ab";
	const char	*c5 = "";
	const char	*c6 = "a";
	const char	*c7 = "ABC";

	printf("strcmp(\"%s\", \"%s\") = %d\n", c1, c2, strcmp(c1, c2));
	printf("ft_strcmp(\"%s\", \"%s\") = %d\n", c1, c2, ft_strcmp(c1, c2));
	printf("--------------------\n");
	printf("strcmp(\"%s\", \"%s\") = %d\n", c1, c3, strcmp(c1, c3));
	printf("ft_strcmp(\"%s\", \"%s\") = %d\n", c1, c3, ft_strcmp(c1, c3));
	printf("--------------------\n");
	printf("strcmp(\"%s\", \"%s\") = %d\n", c1, c4, strcmp(c1, c4));
	printf("ft_strcmp(\"%s\", \"%s\") = %d\n", c1, c4, ft_strcmp(c1, c4));
	printf("--------------------\n");
	printf("strcmp(\"%s\", \"%s\") = %d\n", c5, c5, strcmp(c5, c5));
	printf("ft_strcmp(\"%s\", \"%s\") = %d\n", c5, c5, ft_strcmp(c5, c5));
	printf("--------------------\n");
	printf("strcmp(\"%s\", \"%s\") = %d\n", c5, c6, strcmp(c5, c6));
	printf("ft_strcmp(\"%s\", \"%s\") = %d\n", c5, c6, ft_strcmp(c5, c6));
	printf("--------------------\n");
	printf("strcmp(\"%s\", \"%s\") = %d\n", c6, c5, strcmp(c6, c5));
	printf("ft_strcmp(\"%s\", \"%s\") = %d\n", c6, c5, ft_strcmp(c6, c5));
	printf("--------------------\n");
	printf("strcmp(\"%s\", \"%s\") = %d\n", c1, c7, strcmp(c1, c7));
	printf("ft_strcmp(\"%s\", \"%s\") = %d\n", c1, c7, ft_strcmp(c1, c7));
	printf("--------------------\n");

	// WRITE TEST
	printf("--------------------\nFT_WRITE TEST\n--------------------\n");
	char	*d = "libasm write test";

	// Normal write
	errno = 0;
	printf("ft_write(1, \"%s\", 17):\n", d);
	ssize_t ret1 = ft_write(1, d, 17);
	printf("\nreturn value = %zd, errno = %d\n\n", ret1, errno);

	errno = 0;
	printf("write(1, \"%s\", 17):\n", d);
	ssize_t ret2 = write(1, d, 17);
	printf("\nreturn value = %zd, errno = %d\n", ret2, errno);
	printf("--------------------\n");

	// Invalid fd
	errno = 0;
	printf("ft_write(-1, \"%s\", 17):\n", d);
	ssize_t ret3 = ft_write(-1, d, 17);
	printf("\nreturn value = %zd, errno = %d (%s)\n\n",
		ret3, errno, strerror(errno));

	errno = 0;
	printf("write(-1, \"%s\", 17):\n", d);
	ssize_t ret4 = write(-1, d, 17);
	printf("\nreturn value = %zd, errno = %d (%s)\n",
		ret4, errno, strerror(errno));
	printf("--------------------\n");

	// READ TEST
	printf("--------------------\nFT_READ TEST\n--------------------\n");

	char	buf1[43];
	char	buf2[43];
	char	*file_name = "./test/test.txt";
	int	fd;

	fd = open(file_name, O_RDONLY);
	errno = 0;
	printf("ft_read() 42 bytes from fd = open(\"%s\"):\n", file_name);
	ssize_t r1 = ft_read(fd, buf1, 42);
	if (r1 >= 0)
		buf1[r1] = '\0';
	printf("return value = %zd, errno = %d, buf = \"%s\"\n\n",
		r1, errno, buf1);
	close(fd);

	fd = open(file_name, O_RDONLY);
	printf("read() 42 bytes from fd = open(\"%s\"):\n", file_name);
	errno = 0;
	ssize_t r2 = read(fd, buf2, 42);
	if (r2 >= 0)
		buf2[r2] = '\0';
	printf("return value = %zd, errno = %d, buf = \"%s\"\n",
		r2, errno, buf2);
	close(fd);
	printf("--------------------\n");

	// Invalid fd
	errno = 0;
	printf("ft_read() 10 bytes from fd = -1:\n");
	ssize_t r3 = ft_read(-1, buf1, 10);
	printf("return value = %zd, errno = %d (%s)\n\n",
		r3, errno, strerror(errno));

	errno = 0;
	printf("read() 10 bytes from fd = -1:\n");
	ssize_t r4 = read(-1, buf1, 10);
	printf("return value = %zd, errno = %d (%s)\n",
		r4, errno, strerror(errno));
	printf("--------------------\n");

	// STRDUP TEST
	printf("--------------------\nFT_STRDUP TEST\n--------------------\n");

	char *s1 = "libasm";
	char *s2 = "";
	char *s3 = "Loooooooooooooooooooooooooooooonnnnnnnnnnnnnnnnnnnnnnnnnnnnnnngggg";

	errno = 0;
	char *d1 = ft_strdup(s1);
	printf("ft_strdup(\"%s\") = \"%s\", errno = %d\n",
		s1, d1, errno);

	errno = 0;
	char *d2 = strdup(s1);
	printf("strdup(\"%s\")    = \"%s\", errno = %d\n",
		s1, d2, errno);
	printf("--------------------\n");

	errno = 0;
	char *d3 = ft_strdup(s2);
	printf("ft_strdup(empty) = \"%s\", errno = %d\n", d3, errno);

	errno = 0;
	char *d4 = strdup(s2);
	printf("strdup(empty)    = \"%s\", errno = %d\n", d4, errno);
	printf("--------------------\n");

	errno = 0;
	char *d5 = ft_strdup(s3);
	printf("ft_strdup(\"%s\") = \"%s\", errno = %d\n", s3, d5, errno);

	errno = 0;
	char *d6 = strdup(s3);
	printf("strdup(\"%s\")    = \"%s\", errno = %d\n", s3, d6, errno);

	free(d1);
	free(d2);
	free(d3);
	free(d4);
	free(d5);
	free(d6);

	printf("--------------------\n");

	return (0);
}