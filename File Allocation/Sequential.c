/* File Allocation Methods: Sequential Allocation */

#include <stdio.h>
#include <string.h>

struct file
{
    char name[20];
    int no_of_blocks;
    int start;
} files[20];

// Stores the total number of blocks
int total_blocks;
// Stores the number of remaining blocks as they are allocated to files
int remaining_blocks;
// Stores the file count
int file_count = 0;

void create()
{
    printf("Enter file name: ");
    scanf("%s", files[file_count].name);

    printf("Enter the number of blocks: ");
    scanf("%d", &files[file_count].no_of_blocks);

    printf("Enter starting block: ");
    scanf("%d", &files[file_count].start);

    // If the number of blocks is greater than the remaining blocks available
    if (files[file_count].no_of_blocks > remaining_blocks)
    {
        printf("Not enough blocks available.\n");
        files[file_count].start = -1;
        return;
    }

    for (int i = 0; i < file_count; i++)
    {
        if (files[i].start != -1)
        {
            // Check if other files have used a similar starting block
            if (files[file_count].start == files[i].start)
            {
                printf("Starting block already allocated.\n");
                files[file_count].start = -1;
                return;
            }

            // Check if the blocks required by the file are already allocated to any other file
            if ((files[file_count].start >= files[i].start && files[file_count].start <= files[i].start + files[i].no_of_blocks - 1) ||
                (files[file_count].start + files[file_count].no_of_blocks - 1 >= files[i].start &&
                 files[file_count].start + files[file_count].no_of_blocks - 1 <= files[i].start + files[i].no_of_blocks - 1))
            {
                printf("Blocks already allocated.\n");
                files[file_count].start = -1;
                return;
            }
        }
    }

    // Check if the blocks of the file are non-contiguous
    if (files[file_count].start + files[file_count].no_of_blocks > total_blocks)
    {
        printf("Contiguous blocks not available.\n");
        files[file_count].start = -1;
        return;
    }

    remaining_blocks -= files[file_count].no_of_blocks;
}

void display()
{
    printf("%-20s%-20s%-20s\n", "Name of file", "No. of blocks", "Blocks allocated");

    for (int i = 0; i < file_count; i++)
    {
        printf("%-20s%-20d", files[i].name, files[i].no_of_blocks);

        if (files[i].start == -1)
            printf("%-20s\n", "Not allocated");
        else
        {
            for (int j = files[i].start; j < files[i].start + files[i].no_of_blocks; j++)
                printf("%d ", j);
            printf("\n");
        }
    }
}

int main()
{
    int choice;
    printf("Enter the total number of blocks: ");
    scanf("%d", &total_blocks);

    remaining_blocks = total_blocks;

    for (int i = 0; i < 20; i++)
        files[i].start = -1;

    do
    {
        printf("\tMENU\n");
        printf("1. Create file\n2. Display files\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create();
            file_count++;
            display();
            break;
        case 2:
            display();
            break;
        }
    } while (choice >= 1 && choice <= 2);

    return 0;
}
