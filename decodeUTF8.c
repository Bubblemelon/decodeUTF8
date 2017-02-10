/*
 * encodeUTF8.c
 *
 * This program reads a given file containing UTF-8 encodings and then decodes it
 * to determine the Unicode characters.
 *
 * The decoded characters are saved to an output file in UTF-32 format.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main( int argc, char *argv[]  )
{

    /*
     * This program takes 2 arguments otherwise it aborts
     *
     * e.g. ./prgram in-file out-file
     */

    if( argc != 3 )
    {
        printf( "Incorrect usage, please input: ./encodeUTF8 input-filename output-filename " );
        exit(-1);

    }

    // FILE object for input file
    FILE *fin;

    // r == read fin
    fin = fopen( argv[1], "r" );

    /*
     * Checks to see if input file i.e. "fin" as the program's first argumentsument was open
     * successfully.
     *
     * program == argv[0]
     *
     */

    if( fin == NULL )
    {
        printf("Could not open %s for reading.\n", argv[1] );   // %s == string i.e. name of the file
        exit(-1); // indicates program unsuccessful
    }

    //FILE object for output file & open for writing == "w"
    FILE *fout = fopen( argv[2], "w" );

    /*
     * Check to see if output file i.e. "fout" was opened successfully
     *
     */
    if (fout == NULL)
    {
        printf("Could not open %s for writing.\n", argv[2] );
        exit(-1);
    }
    else
    {
        printf( "Using output file: %s\n", argv[2] ); // displays on terminal to indicate to user
    }

    /*
     * If user defined or specifies the same file for both input and output.
     *
     *  In C++ :
     *  if ( std::string(argv[1]) == std::string(argv[2]) )
     *
     *  Must #include <string.h>
     */

     if( strcmp( argv[1] , argv[2] ) == 0  )
    {
        printf( "Error: Unable to use input file as output file.\n" );
        exit(-1);
    }

     //////////////////////////////////////////////////////////////////////
     //
     //
     //////////////////////////////////////////////////////////////////////

     //counter to count the number of bytes in the file e.g FF == 1 byte == 4 bits for one hex digit
    int counter = 0;


     //container for characters in the input file
     unsigned int read = getc( fin );

    // collect the characters and save into read variable
     while( read != EOF )
     {
         printf( "%02X ", read );

         read = getc(fin);
         counter++;



       //printf( " %d ", counter);
     }

      printf( "\n" );

     /*
      * Excessing one byte at a time using a dynamic array called byte
      *
      */
     unsigned char* byte;
     //memcpy( byte, (char*)&read, sizeof(char)  );  caused printf to be FFFF (deferenced byte) or 0000
     byte = ( unsigned char* )&read;

     for( int i = 0; i <= 5 ; i++ )
     {
        printf( "%02X ", *byte  );
     }



















     //////////////////////////////////////////////////////////////////////
     //
     //
     //////////////////////////////////////////////////////////////////////





     /*
      * Program prints eof message Only if the end of file is reached.
      *
      * getc() returns EOF even when it fails.
      */

    if( feof(fin) )
    {
      printf( "\nEnd of File Reached for input file.\n" ); // prints when EOF reached
    }
   else
    {
      printf( "\nOther Error for input file?" ); //otherwise some sort of error
     }

    /*
     * Close both input and output files.
     */

    fclose( fin );
    fclose( fout );


} // end main
