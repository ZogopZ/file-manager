#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "cli.h"
#include "command_line_utils.h"
#include "doc_utils.h"
#include "main.h"
#include "workers.h"


#define ARRAY_LEN(array) (sizeof((array))/sizeof((array)[0]))       // Get the number of elements within an array

int main(int argc, char **argv)
{    

    int  j, k, worker_fp;
    char *fifo_name1, *fifo_name2;

    if (parse_cmd_line_args(argc, argv) == 1)
    {
        exit(EXIT_FAILURE);
    }
    set_docfile_lines(argv[get_arg_doc()]);                         //Get number of docfile lines/number of paths
    struct docfile_line_info docfile_lines[get_docfile_lines()];    //Path table creation
    memset(docfile_lines, 0, ARRAY_LEN(docfile_lines)*sizeof(struct docfile_line_info));
    store_docfile_lines(argv[get_arg_doc()], docfile_lines);        //Store paths in docfile_lines table
    if (get_docfile_lines() < get_arg_w_val())                      //If number of workers to be created are more than needed
    {                                                               //set the arg_w_val appropriately
        set_arg_w_val(get_docfile_lines());
    }
    int to_worker_fd[get_arg_w_val()];
    int to_handler_fd[get_arg_w_val()];
    struct worker_info workers[get_arg_w_val()];

                                                    //Count the digits of the workers number f
    fifo_name1 = malloc((16 + 1 + count_digits(get_arg_w_val()))
                        *sizeof(char));             //or correct memory allocation add one for \0 character
    fifo_name2 = malloc((17 + 1 + count_digits(get_arg_w_val()))
                        *sizeof(char));

    for (j = 0; j < get_arg_w_val(); j++)
    {
        sprintf(fifo_name1, "to_worker_fifo_%d", j);
        if (mkfifo(fifo_name1, 0666) < 0)           //Create fifo for communication from handler to worker
        {
            perror("Error creating the named pipe");
            exit(EXIT_FAILURE);
        }
        sprintf(fifo_name2, "to_handler_fifo_%d", j);
        if (mkfifo(fifo_name2, 0666) < 0)           //Create fifo for communication from worker to handler
        {
            perror("Error creating the named pipe");
            exit(EXIT_FAILURE);
        }
        workers[j].fifo_id = j;                     //Store workers specific id for fifo usage
        workers[j].worker_pid = fork();             //Store workers specific pid
        if (workers[j].worker_pid < 0)
            perror("fork");
        else if (workers[j].worker_pid == 0)
        {
            sprintf(fifo_name1, "to_worker_fifo_%d", j);
            sprintf(fifo_name2, "to_handler_fifo_%d", j);
            worker_fp = worker_paths(fifo_name1);
            worker_cli(worker_fp, fifo_name2);
            free_docfile_lines(docfile_lines);
            free(fifo_name1);
            free(fifo_name2);
            exit(1);
        }
    }

    /***********Stop here until all workers open FiFos for read***********/
    for (j = 0; j < get_arg_w_val(); j++)
    {
        waitpid(workers[j].worker_pid, NULL, WUNTRACED);	//open all handler to worker fifos for writing
        sprintf(fifo_name1, "to_worker_fifo_%d", j);
        sprintf(fifo_name2, "to_handler_fifo_%d", j);
        if ((to_worker_fd[j] = open(fifo_name1, O_WRONLY | O_NONBLOCK)) == -1)  //O_NONBLOCK for debugging reasons
        {
            perror("ERROR: ");
            exit(EXIT_FAILURE);
        }
        if ((to_handler_fd[j] = open(fifo_name2, O_RDONLY | O_NONBLOCK)) == -1) //O_NONBLOCK for debugging reasons
        {
            perror("ERROR: ");
            exit(EXIT_FAILURE);
        }
        k = j;
        while (k < get_docfile_lines())         //Equally distribute paths to workers
        {
            write(to_worker_fd[j], &(docfile_lines[k].lchars_counter), sizeof(int));
            write(to_worker_fd[j], &(docfile_lines[k].docfile_line), docfile_lines[k].lchars_counter*sizeof(char));
            k = k + get_arg_w_val();
        }
        kill(workers[j].worker_pid, SIGCONT);   //Αfter handler wrote to specific workers FiFo,
    }                                           //send that worker the continue signal to begin reading
    command_line_user(to_worker_fd, to_handler_fd, workers);
    printf("Unlinking FiFos\n");
    for (j = 0; j < get_arg_w_val(); j++)
    {
        sprintf(fifo_name1, "to_worker_fifo_%d", j);
        sprintf(fifo_name2, "to_handler_fifo_%d", j);
        unlink(fifo_name1);
        unlink(fifo_name2);
    }
    free_docfile_lines(docfile_lines);
    free(fifo_name1);
    free(fifo_name2);
    return 0;

}
