#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 
struct Production { 
char **symbols; 
int length; 
}; 
struct NonTerminal { 
char *name; 
struct Production *productions; 
int num_productions; 
}; 
 
struct State { 
    char **symbols; 
    int symbols_len; 
    int input_pos; 
}; 
 
struct QueueNode { 
    struct State state; 
    struct QueueNode *next; 
}; 
 
char **split_into_tokens(const char *line, int *num_tokens) { 
    int len = strlen(line); 
    char **tokens = malloc(len * sizeof(char *)); 
    int count = 0; 
    for (int i = 0; i < len; i++) { 
        char c = line[i]; 
        if (c == '\0' || c == '\n') break; 
        if (isspace(c)) continue; 
        tokens[count] = malloc(2 * sizeof(char)); 
        tokens[count][0] = c; 
        tokens[count][1] = '\0'; 
        count++; 
    } 
    *num_tokens = count; 
    return tokens; 
} 
 
void print_trace(struct State state, char *current_symbol, int input_pos, int num_input_tokens) { 
    printf("Tracing: "); 
    printf("[Symbols: "); 
    for (int i = 0; i < state.symbols_len; i++) { 
        printf("%s ", state.symbols[i]); 
    } 
    printf(" | Input position: %d/%d] Current symbol: %s\n", input_pos, num_input_tokens, current_symbol); 
} 
 
int main() { 
    int num_non_terminals; 
    printf("Enter number of non-terminals: "); 
    scanf("%d", &num_non_terminals); 
    getchar(); 
 
    struct NonTerminal *non_terminals = malloc(num_non_terminals * sizeof(struct NonTerminal)); 
 
    for (int i = 0; i < num_non_terminals; i++) { 
        char name[256]; 
        printf("Enter name of non-terminal %d: ", i + 1); 
        fgets(name, sizeof(name), stdin); 
        name[strcspn(name, "\n")] = '\0'; 
        non_terminals[i].name = strdup(name); 
 
        printf("Enter number of productions for %s: ", name); 
        int num_prods; 
        scanf("%d", &num_prods); 
        getchar(); 
        non_terminals[i].num_productions = num_prods; 
        non_terminals[i].productions = malloc(num_prods * sizeof(struct Production)); 
 
        for (int j = 0; j < num_prods; j++) { 
            char prod_str[256]; 
            printf("Enter production %d for %s as a string: ", j + 1, name); 
            fgets(prod_str, sizeof(prod_str), stdin); 
            prod_str[strcspn(prod_str, "\n")] = '\0'; 
 
            int prod_length; 
            non_terminals[i].productions[j].symbols = split_into_tokens(prod_str, &prod_length); 
            non_terminals[i].productions[j].length = prod_length; 
        } 
    } 
 
    char input_str[256]; 
    printf("Enter input string to parse: "); 
    fgets(input_str, sizeof(input_str), stdin); 
    input_str[strcspn(input_str, "\n")] = '\0'; 
 
    int num_input_tokens; 
    char **input_tokens = split_into_tokens(input_str, &num_input_tokens); 
 
    struct QueueNode *front = NULL, *rear = NULL; 
    char **initial_symbols = malloc(sizeof(char *)); 
    initial_symbols[0] = non_terminals[0].name; 
    struct State initial_state = { initial_symbols, 1, 0 }; 
    struct QueueNode *initial_node = malloc(sizeof(struct QueueNode)); 
    initial_node->state = initial_state; 
    initial_node->next = NULL; 
    front = rear = initial_node; 
 
    int accepted = 0; 
    
    printf("Tracing begins...\n");  // Start of tracing 
    while (front != NULL && !accepted) { 
        struct QueueNode *current = front; 
        front = front->next; 
        if (front == NULL) rear = NULL; 
        struct State state = current->state; 
        if (state.symbols_len == 0) { 
            if (state.input_pos == num_input_tokens) { 
                accepted = 1; 
            } 
        } else { 
            char *current_symbol = state.symbols[0]; 
            int is_nt = 0; 
            struct NonTerminal *nt = NULL; 
            for (int k = 0; k < num_non_terminals; k++) { 
                if (strcmp(non_terminals[k].name, current_symbol) == 0) { 
                    is_nt = 1; 
                    nt = &non_terminals[k]; 
                    break; 
                } 
            } 
            print_trace(state, current_symbol, state.input_pos, num_input_tokens);  // Tracing here 
 
            if (is_nt) { 
                for (int p = 0; p < nt->num_productions; p++) { 
                    struct Production *prod = &nt->productions[p]; 
                    int new_len = prod->length + state.symbols_len - 1; 
                    char **new_symbols = malloc(new_len * sizeof(char *)); 
                    for (int i = 0; i < prod->length; i++) { 
                        new_symbols[i] = prod->symbols[i]; 
                    } 
                    for (int i = 0; i < state.symbols_len - 1; i++) { 
                        new_symbols[prod->length + i] = state.symbols[i + 1]; 
                    } 
                    struct State new_state = { new_symbols, new_len, state.input_pos }; 
                    struct QueueNode *new_node = malloc(sizeof(struct QueueNode)); 
                    new_node->state = new_state; 
                    new_node->next = NULL; 
                    if (rear) { 
                        rear->next = new_node; 
                        rear = new_node; 
                    } else { 
                        front = rear = new_node; 
                    } 
                    printf("  Applying production: %s -> ", nt->name); 
                    for (int i = 0; i < prod->length; i++) { 
                        printf("%s ", prod->symbols[i]); 
                    } 
                    printf("\n"); 
                } 
            } else { 
                if (state.input_pos < num_input_tokens && strcmp(current_symbol, input_tokens[state.input_pos]) == 0) { 
                    int new_pos = state.input_pos + 1; 
                    int new_len = state.symbols_len - 1; 
                    char **new_symbols = NULL; 
                    if (new_len > 0) { 
                        new_symbols = malloc(new_len * sizeof(char *)); 
                        for (int i = 0; i < new_len; i++) { 
                            new_symbols[i] = state.symbols[i + 1]; 
                        } 
                    } 
                    struct State new_state = { new_symbols, new_len, new_pos }; 
                    struct QueueNode *new_node = malloc(sizeof(struct QueueNode)); 
                    new_node->state = new_state; 
                    new_node->next = NULL; 
                    if (rear) { 
                        rear->next = new_node; 
                        rear = new_node; 
                    } else { 
                        front = rear = new_node; 
                    } 
                    printf("  Matching terminal: %s\n", current_symbol); 
                } 
            } 
        } 
        free(state.symbols); 
        free(current); 
    } 
 
    for (int i = 0; i < num_non_terminals; i++) { 
        for (int j = 0; j < non_terminals[i].num_productions; j++) { 
            for (int k = 0; k < non_terminals[i].productions[j].length; k++) { 
                free(non_terminals[i].productions[j].symbols[k]); 
            } 
            free(non_terminals[i].productions[j].symbols); 
        } 
        free(non_terminals[i].productions); 
        free(non_terminals[i].name); 
    } 
    free(non_terminals); 
    for (int i = 0; i < num_input_tokens; i++) { 
        free(input_tokens[i]); 
    } 
    free(input_tokens); 
    printf(accepted ? "String is accepted.\n" : "String is rejected.\n"); 
    return 0; 
} 