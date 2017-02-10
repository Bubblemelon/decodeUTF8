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
     unsigned char *read;

    // allocate memory for read with the size of the variable read
    read = ( unsigned char *)malloc( sizeof(read) );

    // collect the characters and save into read variable
    fread( read, 1, sizeof( read ), fin );


    //print contents of input file
     printf( "\nContents of file %s :\n" , argv[1] );

    for( int i = 0 ; i < sizeof(read); i++)
    {
         printf( "%X " , read[i] );
         counter++;
         //printf( " %d ", counter);
    }

    /*
     *
     * Loop for Byte Order Mark in UTF-8 File
     *
     */

    //Look for BOM without 1 or 2 or 3 or 4 ... byte encodings
    int bom = 0;

    if( read[0] == 0xEF && read[1] == 0xBB && read[2] == 0xBF )
    {
      printf("\n%X ", read[0] );
      printf("%X ", read[1] );
      printf("%X ", read[2] );
      printf( "is a UTF-8 Byte Order Mark.\n");

      bom = 3;

    }
    else
    {
      printf( "\nInput file is missing a UTF-8 Byte Order Mark.\n" );
      exit(-1);
    }

    /*
     * Evaluate if UTF-8 contains start byte and continuation byte
     *
     */

     //check for 1 byte encoding with 0 as start byte
     if( (read[3] >> 7) == 0x00 )
     {
       printf( "\nInput file is a 1 byte UTF-8 sequence" );
       printf( " with data bits of %02X\n", read[3] );
     }
     // check for multi byte encoding with start and continuation byte
     else
     {

      //check for 2 byte encoding with 110 start byte and 10 cont. byte
      if( (read[3] >> 5) == 0x06 )
      {
        // WHEN counter or sizeof() of read is fixed = USE FOR LOOP !!!
        //check for continuation byte 10
        if( (read[4] >> 6) == 0x02 )
        {
          printf( "\nInput file is a 2 byte UTF-8 sequence with data bits of:" );
          //printf( "%02X\n", read[3] );
          //printf( "",  )
        }

      }
      //check for 3 byte encoding with 1110 start byte and (two) 10 cont. byte
      else if( (read[3] >> 4) == 0x0E  )
      {
        // WHEN counter or sizeof() of read is fixed = USE FOR LOOP !!!

        //check for continuation byte 10
        if( (read[4] >> 6) == 0x02  && (read[5] >> 6) == 0x02 )
        {
          printf( "\nInput file is a 3 byte UTF-8 sequence with data bits of:" );
          //printf( "%02X\n", read[3] );
          //printf( "",  )

        }

      }
      //check for 3 byte encoding with 1111 0 start byte and (three) 10 cont. byte
      else if ( (read[3] >> 3) == 0x1F  )
      {
        // WHEN counter or sizeof() of read is fixed = USE FOR LOOP !!!

        //check for continuation byte 10
        if( (read[4] >> 6) == 0x02  && (read[5] >> 6) == 0x02 && (read[6] >> 6) == 0x02 )
        {
          printf( "\nInput file is a 4 byte UTF-8 sequence with data bits of:" );
          //printf( "%02X\n", read[3] );
          //printf( "",  )

        }
      }
      else
      {
        printf( "\nThis input file has the wrong encoding format!\n" );
        exit(-1);
      }


    } //closes large else






    /*
     *
     * Writting to output file in UTF-32 ( Big Endian )
     *
     * 00 00 FE FF
     */

     //a container for writing output file
     unsigned char *write;

    // allocate memory for read with the size of the variable write
    write = ( unsigned char *)malloc( sizeof(write) );

    // assign the UTF-32 BOM in big endian
    write[0] = 0x00;
    write[1] = 0x00;
    write[2] = 0xFE;
    write[3] = 0xFF;

   // assign bytes from input file without UTF-8 BOM and encode UTf-32 BOM
    for( int i = 0; i <= counter - bom ;i++ )
    {
      write[ 4 + i ] = read[ bom + i ];
    }

    //write into output file
    fwrite(write , 1 , sizeof(write) , fout);

    //print contents of input file
    printf("\nThe contents of file %s :\n", argv[2]);

    for( int i = 0 ; i < sizeof(write); i++)
    {
         printf( "%X " , write[i] );
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
      printf( "\nOther Error for input file?\n" ); //otherwise some sort of error
     }

    /*
     * Close both input and output files.
     */

    fclose( fin );
    fclose( fout );


} // end main
