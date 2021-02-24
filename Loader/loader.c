//
//  loader.c
//  Loader
//
//  Created by Christos Papadopoulos on 24/02/2021.
//

#include "loader.h"


struct FILECONTENT_t
{
    char **filecontent;
    char *extension;
    int length;
    
    
};

FILECONTENT *create_file_struct(char *extension)
{
    
    FILECONTENT *file_struct = (FILECONTENT*)malloc(sizeof(FILECONTENT));
    if (file_struct == NULL)
    {
        return NULL;
        
    }
    file_struct->extension = extension;
    
    return file_struct;

}

FILECONTENT *destroy_file_struct(FILECONTENT *file_content_struct)
{
    assert(file_content_struct != NULL);
    
    for (int x = 0; x < file_content_struct->length; x++)
    {
        free(file_content_struct->filecontent[x]);
    }
    free(file_content_struct->filecontent);
    free(file_content_struct);

    
    return 0;
}



int load_content(FILECONTENT *file_content_struct, char *inputFileName)
{
    assert(file_content_struct != NULL);
    assert(file_content_struct != NULL);
    
    const int STEPSIZE = 100;
    FILE *file = fopen(inputFileName, "r");
    
    if (file == NULL)
    {
        return -1;
        
    }
    
    int arrlen = 0;
    file_content_struct->filecontent = NULL;
    char buf[1000];
    int i = 0;
    
    while (fgets(buf, 1000, file) != (char*) NULL)
    {
        if (i == arrlen)
        {
            arrlen += STEPSIZE;
            
            char **newlines = (char **)realloc(file_content_struct->filecontent, arrlen*sizeof(char*));
            if( newlines == NULL)
            {
                printf("[ERROR] Could not allocate more memory !\n");
                fclose(file);
                return -2;
            }
            file_content_struct->filecontent = newlines;
            
        }
        
        
        buf[strlen(buf)-1] = '\0';
        
        char *str = (char*)malloc((strlen(buf)+1)*sizeof(char));
        if (str == NULL)
        {
            printf("[ERROR] Could not allocate more memory !\n");
            fclose(file);
            return -2;
            
        }
        strcpy(str, buf);
        
        file_content_struct->filecontent[i] = str;
        
        i++;
    }
    file_content_struct->length = i;
    fclose(file);
    return 0;
}


int write_content(FILECONTENT *file_content_struct, char *outputFileName)
{
    char *extension = malloc((strlen(file_content_struct->extension)+1)*sizeof(char));
    strcpy(extension, ".");
    strcat(extension, file_content_struct->extension);
    strcat(outputFileName, extension);
    FILE *outputFile = fopen(outputFileName, "w+");
    if (outputFile == NULL)
    {
        free(extension);
        return -1;
        
    }
    
    
    for(int x = 0; x < file_content_struct->length; x++)
    {
        
        fputs(file_content_struct->filecontent[x], outputFile);
        fputs("\n", outputFile);
        
    }
    free(extension);
    fclose(outputFile);
    return 0;
}


char *get_filename_ext(char *filename) {
    char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}
