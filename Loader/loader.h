//
//  loader.h
//  Loader
//
//  Created by Christos Papadopoulos on 24/02/2021.
//

#ifndef loader_h
#define loader_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#endif /* loader_h */


typedef struct FILECONTENT_t FILECONTENT;

FILECONTENT *create_file_struct(char *extension);
FILECONTENT *destroy_file_struct(FILECONTENT *file_content_struct);

int load_content(FILECONTENT *file_content_struct, char *inputFileName);
int write_content(FILECONTENT *file_content_struct, char *outputFileName);
char *get_filename_ext(char *filename);
