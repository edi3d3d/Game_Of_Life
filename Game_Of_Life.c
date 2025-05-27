#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#define Capacity 4
#define initialCapacity 1
/*********************************************************************************
 *                                                                               *
 *                                                                               *
 *                                READ BEFORE                                    *
 *                             TASK 5 = BONUS TASK                               *
 *                              TASK5 INPUT FILE:                                *
 *                                TASK NUMBER                                    *
 *                              DIMENSIONS (L,C)                                 *
 *                           TOTAL GENERATION COUNT                              *
 *                     LISTS IDENTICAL WITH THE LISTS FROM TASK 2                *
 *         FINAL MATRIX (NO SPACE IN BETWEEN THE LISTS AND THE MATRIX)           *
 *                                                                               *
 *                              TASK 2 OUTPUT...                                 *
 *         FINAL MATRIX (NO SPACE IN BETWEEN THE OUTPUT AND THE MATRIX)          *
 *                  I HAVE CUSTOM DATA21-25.IN FOR THIS TASK                     *
 *                                                                               *
 *                                                                               *
 *********************************************************************************/




/**
 * struct Stack - represents a Stack node for storing changed cells on each generation
 * @cell: pointer to an dynamic array of cell coordonates
 * @nr_cell: number of changed cells present in the @cell array
 * @next: pointer to the next generation's Stack node
 */
typedef struct Stack{
    Coord *cell;
    int nr_cell;
    struct Stack *next;
    int size;
} Stack;

/**
 * add_in_list - adds @l and @c at the end value of the node, it's unsorted
 * @l: line coordonate of the cell
 * @c: column coordonate of the cell
 * @node: pointer to the current Stack node
 */
void add_in_list(int l, int c, Stack *node)
{
    node->cell[node->nr_cell].l = l;
    node->cell[node->nr_cell].c = c;

    (node->nr_cell)++;
    if(node->nr_cell == node->size){
        node->size *= Capacity;
        node->cell = (Coord*) realloc(node->cell, (node->size) * sizeof(Coord));
    }
}

/**
 * in_list - checks if a cell is in a certain generation's list of cell coordonates using binary search
 * @l: line coordonate of the cell
 * @c: column coordonate of the cell
 * @node: pointer to the current Stack node
 *
 * returns: 1 if the list contains that cell, 0 otherwise
 */
int in_list(int l, int c, const Stack *node)
{
    int left=0, right=node->nr_cell;
    while (left < right) {
        int middle = (left + right) / 2;

        if(node->cell[middle].l < l) {
            left = middle + 1;
        } else if(node->cell[middle].l > l) {
            right = middle;
        } else if(node->cell[middle].c < c) {
            left = middle + 1;
        } else if(node->cell[middle].c > c){
            right = middle;
        } else {
            return 1;
        }
    }
    return 0;
}

/**
 * is_alive - checks if a certain coordonate's cell is alive or not by counting the number of changes
 * @l: line coordonate of the cell
 * @c: column coordonate of the cell
 * @node: pointer to the starting Stack node
 * @generation: generation number towards to check
 *
 * returns: 1 if the sum is odd (cell alive), 0 otherwise;
 */
int is_alive(int l, int c, const Stack *node , int generation)
{
    int value = 0;
    for(int i = 0; i <= generation && node != NULL ; i++, node = node->next)
        value += in_list(l, c, node);

    return value % 2;
}

/**
 * neighbour_count - counts the number of alive nrighbours of a certain cell in a certain generation
 * @l: line coordonate of the cell
 * @c: column coordonate of the cell
 * @size_l: number of lines in the grid
 * @size_c: number of columns in the grid
 * @node_start: pointer to the starting Stack node
 * @generation: generation number towards to check
 *
 * returns: number (0-8), the number of alive neighbours
 */
int neighbour_count(int l, int c, int size_l, int size_c, const Stack *node_start, int generation)
{
    const char neighbours[8][2] = {
        {-1, -1}, {-1, 0}, {-1, +1},
        { 0, -1},          { 0, +1},
        {+1, -1}, {+1, 0}, {+1, +1}
    };
    int count = 0;

    for(int i = 0; i < 8; i++)
    {
        if(l + neighbours[i][0] < 0 || l + neighbours[i][0] == size_l ||
           c + neighbours[i][1] < 0 || c + neighbours[i][1] == size_c)
            continue;
        count += is_alive(l + neighbours[i][0], c + neighbours[i][1], node_start, generation);
    }

    return count;
}

/**
 * printf_cells - prints the current state of the board.matrix based on the @task
 * @output_file: pointer towards the output file in which the writing will take pleace
 * @size_l: number of lines in the grid
 * @size_c: number of columns in the grid
 * @node_start: pointer to the starting Stack node
 * @node: pointer to the current Stack node
 * @task: value defining the current task
 * @generation: generation number towards to check
 *
 * if the task is 1 it prints the current board.matrix, except the generation 0 board.matrix
 * if the task is 2 it prints the generation and coordonates of each node in the Stack, except for the starting generation 0 board.matrix
 * if the task is 3 it prints the current board.matrix for each node, similar to task 1
 * if the task is 5 it prints the starting board.matrix calculated from task 2 style lists
 */
void printf_cells(FILE* output_file, int size_l, int size_c, const Stack *node_start, const Stack *node, int task, int generation)
{
    if(task == 1 || task == 3 || task == 5){
        for(int i = 0; i < size_l; i++){
            for(int j = 0; j < size_c; j++)
                if(is_alive(i, j, node_start, generation)) {
                    fprintf(output_file, "X");
                } else {
                    fprintf(output_file, "+");
                }
            fprintf(output_file, "\n");
        }
        fprintf(output_file, "\n");
    }else if (task == 2 && generation != 0){
        fprintf(output_file, "%d", generation);
        for(int i = 0; i < node->nr_cell; i++)
            fprintf(output_file, " %d %d", node->cell[i].l, node->cell[i].c);
        fprintf(output_file, "\n");
    }
}

/**
 * @input_file: pointer to the file for the input data
 * @node: pointer to a node in which the list will be added
 * it reads from the file a row and splits it to get the lines and columns,
 */
void list2list(FILE* input_file, Stack *node)
{
    char aux[256];
    int generation;

    if(fscanf(input_file, "%d", &generation) != 1)
        return ;
    if(fgets(aux, 255, input_file) == NULL)
        return ;

    const char *p = strtok(aux, " \n");

    while(p != NULL){
        int l = atoi(p);

        p = strtok(NULL, " \n");
        int c = atoi (p);


        add_in_list(l, c, node);


        p = strtok(NULL, " \n");
    }
}

/**
 * setup - gets the data from the DataInput file and creates the list for generation 0
 * @data_file: pointer to the file for the input data
 * @size_l: number of lines in the grid
 * @size_c: number of columns in the grid
 * @nr_iterations: total number of iterations
 * @node_start: pointer to the starting Stack node
 * @task: the task number (1-4)
 */
void setup(FILE* data_file, int *size_l, int *size_c, int *nr_iterations, Stack *node_start, int *task)
{
    if(fscanf(data_file,"%d%d%d%d", task, size_l, size_c, nr_iterations) != 4)
        exit(1);    //read data from file
    fgetc(data_file);

    node_start->cell = (Coord*) malloc(sizeof(Coord));
    node_start->size = initialCapacity;
    node_start->nr_cell = 0;
    node_start->next = NULL;

    Stack *node_position = node_start;

    if(*task == 5){
        for(int i = 1; i <= *nr_iterations; i++){
            list2list(data_file, node_position);    //all but last generation

            node_position->next = (Stack*) malloc(sizeof(Stack));
            node_position = node_position->next;

            node_position->cell = (Coord*) malloc(sizeof(Coord));
            node_position->size = 1;
            node_position->nr_cell = 0;
            node_position->next = NULL;
        }
        (*nr_iterations)++;
    }

    for(int i = 0; i < (*size_l); i++){
        for(int j = 0; j < (*size_c); j++){
            char board_value;


            if(fscanf(data_file, "%c", &board_value) != 1)
                exit(1);
            if(board_value == 'X')
                add_in_list(i, j, node_position);

        }
        fgetc(data_file);
    }

}

/**
 * update_cells - loops over every neighbour in the current @node's cells and calculates if it should be alive or dead the next generation
 * @size_l: number of lines in the grid
 * @size_c: number of columns in the grid
 * @node_start: pointer to the starting Stack node
 * @node: pointer to the current Stack node
 * @node_next: pointer to the next node after the current @node
 * @generation: generation number towards to check
 * @direction:  the direction of tree path, choosing what rules are applied
 */
void update_cells(int size_l, int size_c,const Stack *node_start, Stack *node_next, int generation, int direction)
{
    node_next->cell = (Coord*) malloc(sizeof(Coord));
    node_next->size=initialCapacity;
    node_next->nr_cell=0;
    node_next->next = NULL;


    for(int i = 0; i < size_l; i++)
        for(int j = 0; j < size_c; j++){
            int n_count = neighbour_count(i, j, size_l, size_c, node_start, generation);
            int cell_alive = is_alive(i, j, node_start, generation);

            if(direction == 0 && n_count == 2 && !cell_alive){
                add_in_list(i, j, node_next);
            } else if(direction == 1 && ((cell_alive && (n_count < 2 || n_count > 3)) || (cell_alive == 0 && n_count == 3))) {
                add_in_list(i, j, node_next);
            }
        }
}

/**
 * task_cells - generates, updates and deletes 1/2 branches based on the task number
 * @output_file: pointer towards the output file in which the writing will take pleace
 * @size_l: number of lines in the grid
 * @size_c: number of columns in the grid
 * @nr_iterations: total number of iterations
 * @node_start: pointer to the starting Stack node
 * @node: pointer to the current Stack node
 * @generation: generation number towards to check
 * @task: the task number (1-4)
 */
void task_cells(FILE* output_file, int size_l, int size_c, int nr_iterations, Stack *node_start, Stack *node, int task, int generation)
{
    //printf("Generation: %d  ", generation); //remove before final version


    if(task == 5) {
        printf_cells(output_file, size_l, size_c, node_start, node, task, nr_iterations);
        return ;
    } if(task < 4) {
        printf_cells(output_file, size_l, size_c, node_start, node, task, generation);
    } else {

        Graph board = {
            .matrix = (int**) malloc(size_l * (sizeof(int*))),
            .size.l = size_l,
            .size.c = size_c
        };

        for(int i = 0; i < size_l; i++)
            board.matrix[i] = (int*) malloc(size_c * sizeof(int));



        for(int i = 0; i < size_l; i++)
            for(int j = 0; j < size_c; j++){
                if(is_alive(i, j, node_start, generation)){             //build board.matrix
                    board.matrix[i][j] = 1;
                } else{
                    board.matrix[i][j] = 0;
                }
            }

        LongestHamiltonian(output_file, board);

        for(int i = 0; i < size_l; i++)     //free board.matrix
            free(board.matrix[i]);

        free(board.matrix);
    }

    if(generation == nr_iterations)
        return ;

    int startingValue = (task == 1 || task == 2);
    for(int i = startingValue; i <= 1; i++){
        node->next = (Stack*) malloc(sizeof(Stack));
        update_cells(size_l, size_c, node_start, node->next, generation, i);
        task_cells(output_file, size_l, size_c, nr_iterations, node_start, node->next, task, generation+1);
        free(node->next->cell);
        free(node->next);
    }
}

int main(int argc, const char* argv[])
{
    for(int i = 1; i < argc; i++)
    {
        FILE *input_file = fopen(argv[i], "r");
        char OutputFile[30];
        strcpy(OutputFile + 1, argv[i]);
        int len = strlen(OutputFile);

        OutputFile[0] = 'O';
        OutputFile[1] = 'u';
        OutputFile[2] = 't';

        OutputFile[len - 2] = 'o';
        OutputFile[len - 1] = 'u';
        OutputFile[len + 0] = 't';
        OutputFile[len + 1] = '\0';


        FILE *output_file = fopen(OutputFile, "w");

        if(input_file == NULL || output_file == NULL) {

            printf("File could not open");

            if(input_file == NULL) {
                fclose(output_file);
            } else if (output_file == NULL) {
                fclose(input_file);
            }

            return 1;
        }

        int task, size_l, size_c, nr_iteratii;

        Stack *node_start = (Stack*) malloc(sizeof(Stack));
        setup(input_file, &size_l, &size_c, &nr_iteratii, node_start, &task);

        task_cells(output_file, size_l, size_c, nr_iteratii, node_start, node_start, task, 0);

        free(node_start->cell);
        free(node_start);
        fclose(input_file);
        fclose(output_file);

    }
    return 0;
}
