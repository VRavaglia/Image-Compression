/* ARITHMETIC ENCODING ALGORITHM.	*/

#include "arithmetic_coding.h"
#include "bit_output.h"
#include <math.h>

static void bit_plus_follow();        /* Routine that follows	*/


//static int Code_value_bits;
//static  code_value Top_value, First_qtr, Half, Third_qtr;

/* CURRENT STATE OF THE ENCODING */

static code_value low, high;        /* ends of the current code-region */
static uint32_t bits_to_follow;        /* Number of opposite bits to output after	*/
static unsigned bits_written;
/* the next bit.				            */

/* START ENCODING A STREAM OF SYMBOLS */

void start_encoding(int max_bits) {
    low = 0;                        /* Full code range */
//    Code_value_bits = max_bits;
//    Top_value = (((long)1<<Code_value_bits)-1);
//    First_qtr = (Top_value/4+1);
//    Half = (2*First_qtr);
//    Third_qtr = (3*First_qtr);

//    printf("\nEncodding: %i, %i, %i, %i, %i\n", Code_value_bits, Top_value, First_qtr, Half, Third_qtr);

    high = Top_value;
    bits_to_follow = 0;            /* No bits to follow next */
}


/* ENCODE A SYMBOL */

void encode_symbol(symbol, cum_freq, file)
        int symbol;                        /* Symbol to encode 				*/
        const int cum_freq[];                    /* Cummulative symbol frequencies	*/
        FILE *file;
{
//    printf("%i",symbol);
    uint64_t range;                    /* size of the current_code region	*/
    range = (uint64_t) (high - low) + 1;                            /* Narrow the code  */
    high = low + (range * cum_freq[symbol - 1]) / cum_freq[0] - 1; /* region to that   */
    low = low + (range * cum_freq[symbol]) / cum_freq[0];     /* allotted to this */

    if(low > high){
        printf("\n Range: %i", range);
        printf("\n Symbol: %i", symbol);
        printf("\nCumFreqs: %i, %i, %i", cum_freq[0], cum_freq[symbol - 1], cum_freq[symbol]);
        printf("\nLow: %i, High: %i", low, high);
    }



//    if(symbol == 9){
//        printf("\nEncodding: %i, %i, %i, %i, %i\n", Code_value_bits, Top_value, First_qtr, Half, Third_qtr);
//    }
/* symbol           */

    for (;;)
    {                                            /* Loop to output bits	*/
        if (high<Half)
        {
            bit_plus_follow(0, file);                    /* Output 0 if in low half */
        }
        else if (low>=Half)
        {                                    /* Output 1 if in high half	*/
            bit_plus_follow(1, file);
            low -= Half;
            high -= Half;                        /* Subtract offset to top */
        }
        else if (low>=First_qtr && high<Third_qtr)
        {                                /* Output an opposite bit   */
/* later if in middle half.	*/
            bits_to_follow += 1;
            low -= First_qtr;                /* Subtract offset to middle */
            high -= First_qtr;
        }
        else break;                        /* Otherwise exit loop */
        low = 2 * low;
        high = 2 * high + 1;                        /* Scale up code range */
    }
}

/* FINISH ENCODING THE STREAM */

void done_encoding(FILE *file) {
    bits_to_follow += 1;                        /* Output two bits that 		*/
    if (low < First_qtr) bit_plus_follow(0, file);    /* select the quarter that 		*/
    else bit_plus_follow(1, file);                    /* the current code range		*/
}                                            /* contains						*/


/* OUTPUT BITS PLUS THE FOLLOWING OPPOSITE BITS */

static void bit_plus_follow(int bit, FILE *file)
{
    output_bit(bit, file);                            /* Output the bit				*/
    while (bits_to_follow > 0) {
        output_bit(!bit, file);                        /* Ouput bits_to_follow			*/
        bits_to_follow -= 1;                    /* opposite bits. Set			*/
    }                                        /* bits_to_follow to zero		*/
}

void escreve_indice(int indice, int bits_indice, FILE* pointf_file) {
    int k;
    int mask;
    int bit_to_write;

    mask = pow(2, bits_indice - 1);
    //printf("\nIndice: %d\t", indice);
    for (k = 0; k < bits_indice; k++) {
        bit_to_write = (mask & indice) / mask;
        //printf(" %d", bit);
        indice = indice << 1;
        output_bit(bit_to_write, pointf_file);
    }

}




