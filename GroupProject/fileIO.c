#include "fileIO.h"

const char delim[2] = "|";

void readFile(Node** table) {
    //  printf("test\n");

    FILE *filePointer;

    filePointer = fopen("books.txt", "r");

    while (!feof(filePointer)) {

        Manga new;
        char singleLine[200] = {0};
        fgets(singleLine, 200, filePointer);

        char *split;
        char *temp;
        // get id

        if (strlen(singleLine) > 0) {
            split = strtok(singleLine, delim);
            // printf("%s", split);
            new.id = atoi(split);
            //printf("another %d\n", new.id);
            split = strtok(NULL, delim);
            FLUSH;



            //  get title
            //split = strtok(NULL, delim);
            //     split = strtok(singleLine, delim);


            //  printf("title %s\n", split);
            new.title = (char*) malloc((strlen(split) + 1) * sizeof (char));
            strcpy(new.title, split);
            //printf("\ngo %s does not work\n", new.title);

            //  printf("\ngo %s does not work\n", new.title);
            // strcpy(new.title , temp);
            FLUSH;
            // get author
            split = strtok(NULL, delim);
            //split = strtok(singleLine, delim);
            new.author = (char*) malloc((strlen(split) + 1) * sizeof (char));
            strcpy(new.author, split);
            FLUSH;

            // get genre
            split = strtok(NULL, delim);

            new.genre = (char*) malloc((strlen(split) + 1) * sizeof (char));
            strcpy(new.genre, split);
            //printf("publisher %s", new.genre);        
            FLUSH;

            // get publisher
            split = strtok(NULL, delim);

            new.publisher = (char*) malloc((strlen(split) + 1) * sizeof (char));
            strcpy(new.publisher, split);

            FLUSH;

            // get used
            //0 is false
            //1 is true
            split = strtok(NULL, delim);
            new.used = (atoi(split));
            FLUSH;

            // get  Price
            split = strtok(NULL, delim);
            new.price = (atof(split));
            
            FLUSH;




            add(table, NULL, new);
        }
    }
}

void writeFileRecursive(FILE *filePointer, TreeNode *current) {
    if (current != NULL) {
        writeFileRecursive(filePointer, current->left);
        fprintf(filePointer, "%d|%s|%s|%s|%s|%d|%.2f\r\n", current->node->manga.id,
                current->node->manga.title,current->node->manga.author, current->node->manga.genre,
                current->node->manga.publisher, current->node->manga.used,
                current->node->manga.price);
        writeFileRecursive(filePointer, current->right);
    }
}

void writeFile(TreeNode* root) {
    FILE *filePointer;
    filePointer = fopen("books.txt", "w");
    fclose(filePointer);
    filePointer = fopen("books.txt", "a");
    writeFileRecursive(filePointer, root);
    fclose(filePointer);
}

