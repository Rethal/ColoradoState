/** @mainpage CS270 Spring 2015
 *  \htmlinclude "P5.html"
 */

/** @file: main.c
 *  @brief Driver to test functions of logic.c (do not modify)
 *
 * @details This is a driver program ... fill this in
 * <p>
 * @author ... Brenton Grundman
 * @date   ... 10/3/15
 */

// Include files
#include "logic.h"

/** Entry point of the program
 * @param   argc count of arguments, will always be at least 1
 * @param   argv array of parameters to program argv[0] is the name of
 *          the program, so additional parameters will begin at index 1
 * @details If one of the test cases fail then the program will assert.
 * @return  0 the Linux convention for success.
 */
int main(int argc, char *argv[])
{
    // check NOT gate truth table
    // A   NOT(A)
    // 0     1
    // 1     0
    printf("===== Testing not_gate =====\n");
    assert(not_gate(FALSE) == TRUE); 
    assert(not_gate(TRUE) == FALSE); 


    // check OR gate truth table
    // A B (A OR B)
    // 0 0   0
    // 0 1   1
    // 1 0   1
    // 1 1   1
    printf("===== Testing or_gate =====\n");
    assert(or_gate(FALSE,FALSE) == FALSE); 
    assert(or_gate(FALSE,TRUE) == TRUE); 
    assert(or_gate(TRUE,FALSE) == TRUE); 
    assert(or_gate(TRUE,TRUE) == TRUE); 
    
    // check RS latch truth table
    // the order matters so that the saved_bit will be true when expected
    //  S	R	saved_bit   rs_latch(S,R)
    //  FALSE	FALSE	FALSE	    will assert in rs_latch
    //  FALSE	FALSE	TRUE	    will assert in rs_latch
    //  TRUE	FALSE	FALSE	    FALSE
    //	TRUE	TRUE	FALSE	    FALSE
    //  FALSE	TRUE	FALSE	    TRUE
    //  FALSE	TRUE	TRUE	    TRUE
    //	TRUE	TRUE	TRUE	    TRUE
    //  TRUE	FALSE	TRUE	    FALSE
    printf("===== Testing rs_latch =====\n");
    assert( rs_latch( TRUE, FALSE )==FALSE );
    assert( rs_latch( TRUE, TRUE )==FALSE );
    assert( rs_latch( FALSE, TRUE )==TRUE );
    assert( rs_latch( FALSE, TRUE )==TRUE );
    assert( rs_latch( TRUE, TRUE )==TRUE );
    assert( rs_latch( TRUE, FALSE )==FALSE );

	//check AND
	printf("===== Testing and_gate =====\n");
	assert(and_gate(FALSE, FALSE) == FALSE);
	assert(and_gate(FALSE, TRUE) == FALSE);
	assert(and_gate(TRUE, FALSE) == FALSE);
	assert(and_gate(TRUE, TRUE) == TRUE);

	//check XOR
	printf("===== Testing xor_gate =====\n");
	assert(xor_gate(FALSE, FALSE) == FALSE);
	assert(xor_gate(FALSE, TRUE) == TRUE);
	assert(xor_gate(TRUE, FALSE) == TRUE);
	assert(xor_gate(TRUE, TRUE) == FALSE);

	//check D Flip Flop
	printf("===== Testing d_latch =====\n");
	assert(d_latch(TRUE, FALSE) == FALSE);
	assert(d_latch(TRUE, TRUE) == TRUE);
	assert(d_latch(FALSE, FALSE) == TRUE);
	assert(d_latch(FALSE, TRUE) == FALSE);
	assert(d_latch(FALSE, FALSE) == FALSE);
	assert(d_latch(TRUE, FALSE) == FALSE);

	//check Adder
	printf("===== Testing adder =====\n");
	BIT over = 0;
	assert(adder(5, 5, 0, &over) == 10);
	assert(over == 0);
	assert(adder(5, 5, 1, &over) == 11);
	assert(over == 0);
	assert(adder(1, 7, 1, &over) == 9);
	assert(over == 0);
	assert(adder(7, 7, 0, &over) == 14);
	assert(over == 0);
	assert(adder(13, 13, 1, &over) == 11);
	assert(over == 1);

	//check Multiplexer
	printf("===== Testing multiplexer =====\n");
	assert(multiplexer(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE) == FALSE);
	assert(multiplexer(TRUE, TRUE, TRUE, TRUE, TRUE, TRUE) == TRUE);
	assert(multiplexer(TRUE, FALSE, TRUE, FALSE, TRUE, FALSE) == TRUE);
	assert(multiplexer(FALSE, TRUE, FALSE, TRUE, FALSE, TRUE) == TRUE);

	//check Decoder
	printf("===== Testing decoder =====\n");
	BIT a = 0;
	BIT b = 0;
	BIT c = 0;
	BIT d = 0;
	decoder(FALSE, FALSE, &a, &b, &c, &d);
	assert(a == TRUE&&b == FALSE&&c == FALSE&&d == FALSE);
	decoder(FALSE, TRUE, &a, &b, &c, &d);
	assert(a == FALSE&&b == TRUE&&c == FALSE&&d == FALSE);
	decoder(TRUE, FALSE, &a, &b, &c, &d);
	assert(a == FALSE&&b == FALSE&&c == TRUE&&d == FALSE);
	decoder(TRUE, TRUE, &a, &b, &c, &d);
	assert(a == FALSE&&b == FALSE&&c == FALSE&&d == TRUE);

	return 0;
}
