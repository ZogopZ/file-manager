#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command_line_utils.h"

int arg_w_val;
int arg_doc;

int get_arg_w_val(void)
{
    return (arg_w_val);
}

void set_arg_w_val(int new_value)
{
    arg_w_val = new_value;
}

int get_arg_doc(void)
{
    return (arg_doc);
}

int parse_cmd_line_args(int argc, char** argv)
{

    // Given arguments >>>./jobExecutor -d docfile -w 5
    if ((strcmp(argv[1], "-d") == 0) && (strcmp(argv[3], "-w") ==0 ) && atoi(argv[4]) && argc == 5)
    {
        arg_doc = 2;
        arg_w_val = atoi(argv[4]);
    }
    // Given arguments >>>./jobExecutor -w 5 -d docfile
    else if ((strcmp(argv[1], "-w") == 0) && (strcmp(argv[3], "-d") ==0 ) && atoi(argv[2]) && argc == 5)
    {
        arg_doc = 4;
        arg_w_val = atoi(argv[4]);
    }
    // Given arguments >>>./jobExecutor -d docfile  (w default 5)
    else if ((strcmp(argv[1], "-d") == 0) && argc == 3)
    {
        arg_doc = 2;
        arg_w_val = 5;
    }
    else
    {
        printf("Wrong Arguments\n");
        return 1;
    }

return 0;
}

