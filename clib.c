#include <stdio.h>
#include <stdlib.h>

const int strlen(const char *str)
{
	int length = 0;
	while(*(str+(length*sizeof(char))) != '\0')
		length++;
	return length;
}

const char *strdup(const char *str)
{
	int str_len = 0;
	char *str_dup = (char *)malloc(sizeof(char));
	while( *(str+(str_len*sizeof(char))) != '\0' )
	{
		*(str_dup+(str_len*sizeof(char))) = *(str+(str_len*sizeof(char)));
		str_len++;
	}
	*(str_dup+(str_len*sizeof(char))) = '\0';
	return str_dup;
}

/* strlen(str0) > strlen(str1) */
const int strcontains(const char *str0, const char *str1)
{
	int i = 0;
	int j = 0;
	while(*(str0+((i+j)*sizeof(char))) == (*(str1+(j*sizeof(char)))))
	{
		j++;
		if(j == strlen(str1))
			return 0;
		if(*(str0+((i+j)*sizeof(char))) != '\0')
			return 1;
		if(*(str1+(j*sizeof(char))) == '\0')
		{
			j = 0;
			i++;
		}
	}
	return 1;
}

const int strcmp(const char *str0, const char *str1)
{
	if(strlen(str0) != strlen(str1))
		return 1;
	int i = 0;
	while((*(str0+(i*sizeof(char))) == (*(str1+(i*sizeof(char))))) & (*(str0+(i*sizeof(char))) != '\0'))
	{
		i++;
		if(i == strlen(str1))
			return 0;
	}
	return 1;
}

const char *strconcatenate(const char *str0, const char *str1)
{
        int length0 = strlen(str0);
        int length1 = strlen(str1);
        char *res = strdup(str0);
        int i = 0;
        while(i < length0+length1) 
        {
                res = (char *)realloc(res, (length0+i+1)*sizeof(char));
                *(res+(length0+i+1)*sizeof(char)) = *(str1+(i*sizeof(char)));
                i++;
        }
        *(res+(length0+i)*sizeof(char)) = '\0';
        return 0;
}

const char *readi()
{
        char *buffer = (char *)malloc(2*sizeof(char));
        char *buffer_buffer_len_content = (char *)malloc(2*sizeof(char));
        char *end_of_line = (char *)malloc(2*sizeof(char));
        int buffer_len = 0;
        *buffer = ' ';
        *(buffer+sizeof(char)) = '\0';
        *end_of_line = '\n';
        *(end_of_line+sizeof(char)) = '\0';
        snprintf(buffer_buffer_len_content, 2*sizeof(char), "%c\0", *(buffer+buffer_len));
        while(strcmp(buffer_buffer_len_content, end_of_line) != 0)
        {
                read(1, &(*(buffer+(buffer_len*sizeof(char)))), sizeof(char));
                snprintf(buffer_buffer_len_content, 2*sizeof(char), "%c\0", *(buffer+(buffer_len*sizeof(char))));
                buffer_len = buffer_len + 1;
                buffer = (char *)realloc(buffer, (buffer_len+2)*sizeof(char));
                *(buffer+(buffer_len*sizeof(char))) = '\0';
        }
        free(buffer_buffer_len_content);
        free(end_of_line);
        return buffer;
}

const char *read_file(const char *restrict file_name)
{
        const char *restrict mode = strdup("r\0");
        FILE *restrict fd = fopen(file_name, mode);
        if(fd == NULL)
                return NULL;
        char *buffer = (char *)malloc(sizeof(char));
        int buffer_len = 0;
        do
        {
                buffer_len = buffer_len +1;
                fread(buffer+((buffer_len-1)*sizeof(char)), sizeof(char), 1, fd);
                buffer = (char *)realloc(buffer, (buffer_len+1)*sizeof(char));
        }while(*(buffer+((buffer_len-1)*sizeof(char))) != EOF);
        *(buffer+((buffer_len-1)*sizeof(char))) = '\0';
        return buffer;
}

const char *read_file_v1(char *file_name)
{
        const char *restrict mode = strdup("r\0");
        FILE *restrict fd = fopen(file_name, mode);
        if(fd == NULL)
                return NULL;
        char *buffer = (char *)malloc(sizeof(char));
        int buffer_len = 0;
        while((buffer[buffer_len] = fgetc(fd)) != EOF)
        {
                buffer_len++;
                buffer = (char *)realloc(buffer, (buffer_len+1)*sizeof(char));
        }
        buffer[buffer_len] = '\0';
        return buffer;
}

const int shift_mask_left(const int mask, const int i)
{
        const int mask_shifted = mask << i;
        return mask_shifted;
}

const int and_operation(const int number, const int mask_shifted)
{
        const int result = number & mask_shifted;
        return result;
}

const int shift_result_right(const int number, const int i)
{
        const int result = number >> i;
        return result;
}

void convert_integer_to_binary(int *restrict array, const int number, const int mask, const int architecture)
{
        int i = 0;
        while(i < architecture)
        {
                const int mask_shifted = shift_mask_left(mask, i);
                const int and_result = and_operation(number, mask_shifted);
                array[i] = shift_result_right(and_result, i);
                i = i +1;
        }
}

double pow(double x, double y)
{
        if(y == 1)
                return x;
        return pow(x*x, y-1);
}

int convert_binary_to_integer(int *array, int architecture)
{
        int number = 0;
        int i = architecture-1;
        while(i >= 0)
        {
                if(array[i] == 1)
                        number = number + pow(2, i+1);
                i = i -1;
        }
        return number;
}
/*need patch */
int find_string_position(const char *buffer, const char *string, const int position)
{
        int i = 0;
        int j = 0;
        int position_found = 0;
        char *str = (char *)malloc(strlen(string)*sizeof(char));
        while(buffer[i+j] != '\0')
        {
                while(j < strlen(string))
                {
                        str[j] = buffer[i+j];
                        j = j +1;
                }
                str[j] = '\0';
                if(strcmp(string, str) == 0)
                {
                        position_found = position_found +1;
                        if(position_found == position)
                                return i-1;
                        i = i +j;
                }else{
                        i = i +1;
                }
                j = 0;
        }
        return 0;
}

char **strsplit_v1(const char *string,const char *spliter)
{
        char **array = (char **)malloc(sizeof(char *));
        char *buffer;
        char *tmp;
        int i = 0;
        int j = 1;
        int k = find_string_position(string, spliter, j);
        int a = 0;
        int c = 0;
        int vk = 0;
        while(string[i] != '\0')
        {
                buffer = (char *)malloc(sizeof(char));
                while((i <= k) & (string[i] != '\0'))
                {
                        buffer[c] = string[i];
                        c = c +1;
                        i = i +1;
                        buffer = (char *)realloc(buffer, (c+2)*sizeof(char));
                }
                if(k > i+strlen(spliter) & (vk == 0))
                {
                        k = k-strlen(spliter);
                        vk = 1;
                }
                i = i + strlen(spliter);
                buffer[c] = '\0';
                array[a] = strdup(buffer);
                j = j +1;
                k = find_string_position(string, spliter, j);
                if(k == 0)
                        k = strlen(string);
                c = 0;
                a = a +1;
                array = (char **)realloc(array, (a+1)*sizeof(char *));
                free(buffer);
        }
        array[a] = '\0';
        return array;
}
