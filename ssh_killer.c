#include <stdio.h>
#include "clib.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
        char *data;
        const char *spliter = "\n\0";
        char **line;
        char **word;
        int i = 0;
        int j = 0;
        while(1)
        {
                system("echo \"$(ps aux | grep ssh)\" > /home/lahbabi1chems3eddine/ssh_killer/log_port_22\0");
                data = read_file("/home/lahbabi1chems3eddine/ssh_killer/log_port_22\0");
                line = strsplit_v1(data, spliter);
                while(line[i] != '\0')
                {
                        if(strcontains(strdup(line[i]), strdup(argv[0])) == 0)
                                continue;
                        word = strsplit_v1(line[i], " \0");
                        while(word[j] != '\0')
                        {
                                if((atoi(word[j]) != 0))
                                {
                                        printf("Killing process with pid %d ...\0", atoi(word[j]));
                                        system(strconcatenate(strdup("kill -9 \0"), strdup(word[j])));
                                        printf("[done]\n\0");
                                        break;
                                }
                                j++;
                        }
                        j = 0;
                        i++;
                }
                i = 0;
        }
        return 0;
}
