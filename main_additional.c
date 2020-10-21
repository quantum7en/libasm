# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/stat.h>

ssize_t	ft_write(int fd, const void *buf, size_t count);
ssize_t	ft_read(int fd, void *buf, size_t nbyte);
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(const char *src);

#define BUF 512

void			test_read(int fd1, int fd2, int read_size)
{
	errno = 0;
	
	char	buf1[BUF];
	bzero(buf1, BUF);
	char	buf2[BUF];
	bzero(buf2, BUF);
	int std_err = 0;
	int ft_w_err = 0;
	int flag_err = 0;
	
	int std = read(fd1, buf1, read_size);
	if (std < 0)
	{
		flag_err = 1;
		std_err = errno;
		errno = 0;
	}
	int	ft_w = ft_read(fd2, buf2, read_size);
	if (ft_w < 0)
	{
		flag_err = 1;
		ft_w_err = errno;
		errno = 0;
	}
	if (flag_err)
	{
		if (std_err == ft_w_err)
			printf("\033[48;2;0;250;154m\033[38;2;0;0;0m[OK]\033[0m   ");
		else
			printf("\033[1m\033[48;2;175;135;255m\033[38;2;255;255;255m[KO]\033[0m   ");
	}
	else
	{
		if (std == ft_w && (strcmp(buf1, buf2) == 0))
			printf("\033[48;2;0;250;154m\033[38;2;0;0;0m[OK]\033[0m   ");
		else
			printf("\033[1m\033[48;2;175;135;255m\033[38;2;255;255;255m[KO]\033[0m   ");
	}
	printf("std_len: |%4d|, asm_len: |%4d|, std_err: |%4d|, asm_err: |%4d|\n", std, ft_w, std_err, ft_w_err);
}

void test_write()
{
	int fd;
	char *str = "Hello world\n";

	printf("\033[0;32m\n=== ft_write ===\n\033[0m");

	ft_write(1, str, 12);
	write(1, str, 12);

	ft_write(1, &"", 1);
	ft_write(1, &"\n", 1);
	write(1, &"", 1);
	write(1, &"\n", 1);

	fd = open("write2.txt", O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR);
	ft_write(fd, str, 12);
	write(fd, str, 12);
	close(fd);

	errno = 0;
	ft_write(-1, str, 12);
	printf("errno => %d\n", errno);

	errno = 0;
	write(-1, str, 12);
	printf("errno => %d\n", errno);
	
	fd = open("write.txt", O_WRONLY);
	ft_write(fd, str, 12);
	write(fd, str, 12);
	close(fd);
}

void			test_strdup(char *str)
{
	char *s1 = strdup(str);
	char *s2 = ft_strdup(str);
	if (strcmp(s1, s2) == 0)
		printf("\033[48;2;0;250;154m\033[38;2;0;0;0m[OK]\033[0m   ");
	else
		printf("\033[1m\033[48;2;175;135;255m\033[38;2;255;255;255m[KO]\033[0m   ");
	printf("std: |%s|, asm: |%s| len std: |%ld|, len asm: |%ld|\n", s1, s2, strlen(s1), strlen(s2));
	free(s1);
	free(s2);
}

void			test_strcmp(char *s1, char *s2)
{
	if ((strcmp(s1, s2) == ft_strcmp(s1, s2)) || (strcmp(s1, s2) < 0 && ft_strcmp(s1, s2) < 0) || (strcmp(s1, s2) > 0 && ft_strcmp(s1, s2) > 0))
		printf("\033[48;2;0;250;154m\033[38;2;0;0;0m[OK]\033[0m   ");
	else
		printf("\033[1m\033[48;2;175;135;255m\033[38;2;255;255;255m[KO]\033[0m   ");
	printf("std: |%d|, asm: |%d|\n", strcmp(s1, s2), ft_strcmp(s1, s2));
}

void			test_strcpy(char *src)
{
	char	s1[BUF];
	char	s2[BUF];
	bzero(s1, BUF);
	bzero(s2, BUF);
	strcpy(s1, src);
	ft_strcpy(s2, src);
	if ((strcmp(s1, s2)) == 0)
		printf("\033[48;2;0;250;154m\033[38;2;0;0;0m[OK]\033[0m   ");
	else
		printf("\033[1m\033[48;2;175;135;255m\033[38;2;255;255;255m[KO]\033[0m   ");
	printf("std: |%s|, asm: |%s|\n", s1, s2);
}

void			test_strlen(char *src)
{
	if (strlen(src) == ft_strlen(src))
		printf("\033[48;2;0;250;154m\033[38;2;0;0;0m[OK]\033[0m   ");
	else
		printf("\033[1m\033[48;2;175;135;255m\033[38;2;255;255;255m[KO]\033[0m   ");
	printf("std: %-4ld, asm: %-4ld\n", strlen(src), ft_strlen(src));
}

int			main(void)
{
	char longstr[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce tellus metus, finibus quis sagittis quis, volutpat a justo. Nunc et pellentesque quam. Fusce aliquam aliquam libero, sed pulvinar nullam.";
	printf("-----------------------ft_strlen----------------------\n");
	test_strlen("");
	test_strlen("Hello, world!");
	test_strlen(longstr);
	
	printf("\n-----------------------FT_STRCPY----------------------\n");
    test_strcpy("Hello");
    test_strcpy("Hello world; test1; test2; test3; test4; test5");
	test_strcpy("");
	test_strcpy("lolkek");
	test_strcpy(longstr);
	
	printf("\n-----------------------FT_STRCMP----------------------\n");
	test_strcmp("Hello", "");
	test_strcmp("", "World");
	test_strcmp("Hello", "Hel");
	test_strcmp("Hel", "Hello");
	test_strcmp("", "");
	test_strcmp("Hello", "Hello");
	test_strcmp(longstr, longstr);
	test_strcmp(" ", "");
	test_strcmp("Helloo", "Hello");
	test_strcmp("", " ");
	test_strcmp("Hello", "Helloo");

	printf("\n-----------------------FT_STRDUP----------------------\n");
	test_strdup("");
	test_strdup("lolkek");
	test_strdup(longstr);
	
	printf("\n-----------------------FT_WRITE----------------------\n");
	test_write();

	printf("\n-----------------------FT_READ----------------------\n");
	int fd1, fd2;
	fd1 = open("write.txt", O_RDONLY);
	fd2 = open("write.txt", O_RDONLY);
	test_read(fd1, fd2, BUF);
	test_read(fd1, fd2, 0);
	test_read(fd1, fd2, 1);
	test_read(fd1, fd2, 10);
	test_read(fd1, fd2, -1);
	test_read(fd1, fd2, 5);
	test_read(-1, -1, 0);
	test_read(-1, -1, -1);
	test_read(-1, -1, 10);
	test_read(200, 200, 0);
	test_read(200, 200, -1);
	test_read(200, 200, 10);

	printf("----FT_READ STDOUT----\n");
	char	s1[BUF];
	char	s2[BUF];
	printf("enter string for standard read: \n");
	int std_re = read(0, s2, BUF);
	printf("std str: %s", s2);
	printf("std return value: %d\n", std_re);
	printf("enter string for asm ft_read: \n");
	int ft_re = ft_read(0, s1, BUF);
	printf("my: %s", s1);
	printf("asm return value: %d\n", ft_re);
	if (ft_re == std_re)
		printf("\033[48;2;0;250;154m\033[38;2;0;0;0m[OK]\033[0m   ");
	else
		printf("\033[1m\033[48;2;175;135;255m\033[38;2;255;255;255m[KO]\033[0m   ");
	printf("STDIN READ: std: %-4d, asm: %-4d\n", std_re, ft_re);
	
	return (0);
}