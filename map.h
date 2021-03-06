#ifndef _MAP_H_
#define _MAP_H_

struct map_node
{
    struct map_node* next;
    int id;
    int text_length;
    int number_of_words;
    double score;
    char text[0];
};

struct map_short_node
{
        struct map_short_node* next;
        int id;
        double score;
};

struct word
{
    struct word* word_next;
    int number_of_line;
    int words_found;
    int word_length;
    char actual_word[0];
};

extern struct map_node *map_node_head;

void initialize_to_zero_score_of_map_nodes(void);

struct map_node * get_map_list_head(void);

void free_map_list(struct map_node *incoming_struct);

void free_replica(void);

void print_map_list_node(struct map_node *map_node_next);

void print_map_list(void);

void print_map_short_list(void);

struct map_node * search_map_node_to_list_with_id(int id, struct map_node *map_node_temp);

void free_replicate_map_list(void);

void sort_replicate_map_list(void);

void get_top_k(struct map_short_node *tmp);

void create_replicate_map_list(void);

int add_map_node_to_list(int number_of_chars_per_line, int numb_of_line, FILE* fp);

struct map_node *load_map_list(char *argv);

struct word *get_word(void);

void set_word(void);

int get_words_per_line(struct map_node *map_node_next);

void printer(struct map_short_node *tmp);

struct map_node *find_words(struct map_node *map_node_current, struct word *search_words_head);

struct map_node *remove_tabs(struct map_node *map_node_current);

#endif /* _MAP_H_ */
