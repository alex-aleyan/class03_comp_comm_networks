/* 
 *
 * Citing Sources: 
 *
 * https://www.linuxtopia.org/online_books/programming_books/gnu_c_programming_tutorial/argp-example.html 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "../source/func.h"

int getLinesPerFile(FILE *fp){
				int line_count = 0;
				char current_char;

				rewind(fp);

				for (current_char = getc(fp); current_char != EOF; current_char = getc(fp))	
								if (current_char == '\n') line_count++;

				printf("\ngetLinesPerFile: %d\n\n", line_count);

				rewind(fp);

				return line_count;
}

char ** getData(FILE *fd, int * number_of_lines, int debug, char * line_ptr2[])
{

    // Get number of lines:
    char current_char;
    int line_count=0;
    for (current_char = getc(fd), line_count=0; current_char != EOF; current_char = getc(fd))  if (current_char == '\n') line_count++;
				if (debug != 0) 	printf("\nNumber of lines (line_count): %d\n\n", line_count);
				if (line_count == 0){ perror("Error: file-in is empty!\n\n"); return -1; };
    char * line_ptr[line_count];
				(*number_of_lines)=line_count;
  
  		rewind(fd);

    // get number of chars per line:
    int char_count=0;
    int current_line=0;
    for (current_char = getc(fd), current_line=0; current_char != EOF; current_char = getc(fd))
    {
        char_count++;
        if (current_char == '\n')
        {
  								    // allocate just enough memory to hold the characters of current line:
												if (debug != 0) {
																printf("Number of char per line %d: %d\n", current_line, char_count);
																printf("Allocating: line=%d; bytes=%d: %d\n", current_line, char_count*sizeof(char)+1);
												}
  
            line_ptr[current_line] = malloc(char_count*sizeof(char)+1);
												line_ptr2[current_line] = line_ptr[current_line];
												if (debug != 0) printf("Line=%d stored at 0x%x\n\n", current_line, line_ptr[current_line]);
            if (line_ptr[current_line] == NULL) {printf("Caught NULL at malloc!!!"); return -1;};
  
            char_count = 0;
            current_line++;
        }
    }
  
  		rewind(fd);
  
    printf("\n");


  
    //copy file content to allocated memory line by line one charachter at the time:
    for (current_char = getc(fd), current_line=0, char_count; current_char != EOF; current_char = getc(fd))
    {
								if (debug != 0) {
												if (char_count == 0) printf("Line(%d):", current_line);
								}
  
        *(line_ptr[current_line]+char_count)=current_char;
        char_count++;
        if (current_char == '\n')
        {
            //terminate with NULL:
            *(line_ptr[current_line]+char_count)='\0';
												if (debug != 0) printf("%s", line_ptr[current_line]);
            char_count=0;
            current_line++;
        }
    }
  
    printf("\n");

  		rewind(fd);



				return line_ptr;
}