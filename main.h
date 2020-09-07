#ifndef _MAIN_H_
#define _MAIN_H_

#include <unistd.h>

#define log "log"

struct worker_info
{
    pid_t worker_pid;
    int fifo_id;
};

struct docfile_line_info
{
    struct docfile_line_info *line_list_next;
    int lchars_counter;
    char *docfile_line;
};

#endif /* _MAIN_H_ */

