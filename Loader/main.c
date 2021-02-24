//
//  main.c
//  Loader
//
//  Created by Christos Papadopoulos on 24/02/2021.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#include "loader.h"
int main(int argc, char * argv[]) {
   
   char *optstring = ":i:o:";
   char *inputFileName = NULL;
   char *outputFileName = NULL;
   int getVal;
   
   while((getVal = getopt(argc, argv, optstring)) != EOF)
   {
      switch(getVal)
      {
         case 'i':
            
            inputFileName = (char*)malloc(strlen(optarg)*sizeof(char));
            if (inputFileName == NULL)
            {
               printf("[Error] allocating memory for the inputFileName\n");
               
            }
            strcpy(inputFileName, optarg);
            break;
            
            
         case 'o':
            
            outputFileName = (char*)malloc(strlen(optarg)*sizeof(char));
            if (outputFileName == NULL)
            {
               printf("[Error] allocating memory for the outputFileName\n");
               
            }
            strcpy(outputFileName, optarg);
            break;
            
         case '?':
            
            printf("[ERROR] Unknown option '-%c !\n", optopt);
            break;
            
         case ':':
            
            printf("[ERROR] Option '-%c' requires an argument !\n", optopt);
            break;
            
            
      }
      
   }
   
   if (inputFileName != NULL && outputFileName != NULL)
   {
      char *extension = get_filename_ext(inputFileName);
      
      FILECONTENT *file_content_struct = create_file_struct(extension);
      if (file_content_struct == NULL)
      {
         printf("[ERRO] Could not build file structure\n");
         
      }
      int error = load_content(file_content_struct, inputFileName);
      
      if (error == -1)
      {
         printf("[ERROR] Could not open input file %s !\n", inputFileName);
         
      }
      
      error = 0;
      
      error = write_content(file_content_struct, outputFileName);
      if (error == -1)
      {
         printf("Could not create the output file %s !\n", outputFileName);

      }
      
      destroy_file_struct(file_content_struct);
      
      free(inputFileName);
      free(outputFileName);
      
      
      
   }
   
   else{
      
      printf("Usage :\n");
      printf("\t -i (MANDATORY): Input file to read bytes from.\n");
      printf("\t -o (MANDATORY): Output file to write to.\n\n");
      
      
   }
   
   
}
