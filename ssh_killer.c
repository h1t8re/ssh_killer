#include <stdio.h>
#include "clib.h"

int main(int argc, char *argv[])
{
        system("echo \"$(ps aux | grep ssh)\" > ps_ssh.log\0");
        char *ps_ssh_log = read_file_v1("./ps_ssh.log\0");
        printf("%s\n", ps_ssh_log);
        return 0;
}
