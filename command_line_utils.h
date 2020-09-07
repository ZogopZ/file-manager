#ifndef _COMMAND_LINE_UTILS_H_
#define _COMMAND_LINE_UTILS_H_

struct command_line_options
{
    int num_of_results;
    int name_length;
    char doc_file_name[0];
};

int get_arg_w_val(void);

void set_arg_w_val(int new_value);

int get_arg_doc(void);

int parse_cmd_line_args(int argc, char** argv);

#endif /* _COMMAND_LINE_UTILS_H_ */
