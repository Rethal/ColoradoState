//Brenton Grundman
//L05
import java.util.Arrays;
import java.util.Scanner;
import java.io.File;
import java.io.IOException;


public class Lab1 {

	// BEGIN PART 1

	/**
	 * Test if x is divisible by 3
	 * @param x integer to test
	 * @return true if x is divisible by 3
	 */

	public boolean isDivisibleBy3(int x)
	{
		if (x%3==0){
			return true;
		}
		else return false;		
	}

	/**
	 * Test if x is divisible by 5
	 * @param x integer to test
	 * @return true if x is divisible by 5
	 */
	public boolean isDivisibleBy5(int x)
	{

		if (x%5==0){
			return true;
		}
		else return false;	
	}

	/**
	 * Use helper functions isDivisibleBy3() and isDivisibleBy5() to implement.
	 *
	 * @param x integer to see if it divisible by 3, 5, or both
	 * @return "is divisible by 3" if x is divisible by 3, "is divisible by 5" if divisible by 5,
	 *          or "is divisible by 3 and 5" if divisible by 3 and 5
	 */

	public String testDivisors(int x)
	{

		//Lab1 lab = new Lab1();
		if (isDivisibleBy3(x) == true){
			if (isDivisibleBy5(x) == true){
				return " is divisible by 3 and 5";
			}
			else return " is divisible by 3";
		}
		else if (isDivisibleBy5(x)==true){
			return " is divisible by 5";
		}
		else return "";
	}

	/**
	 * Print i and the result of testDivisors for all i such that first <= i <= last
	 *
	 * Example:
	 * 1
	 * 2
	 * 3 "is divisible by 3"
	 * 4
	 * 5 "is divisible by 5"
	 * ...
	 * 15 "is divisible by 3 and 5"
	 *
	 * @param first integer to start the test range, inclusive
	 * @param last integer to end the test range, inclusive
	 */

	public void testRange(int first, int last)
	{
		//Lab1 lab = new Lab1();
		int x=first;
		for (int i=first;i<=last;i++){
			testDivisors(x);			
			System.out.println(x+testDivisors(x));
			x++;
		}

	}

	// END PART 1


	// BEGIN PART 2

	/**
	 * Extract all positive integers from the intArray.
	 * Returned array is exactly as long as the number of positive integers in values.
	 * @param intArray containing all the numbers
	 * @return array containing all of the positive integers in values.
	 */

	public int[] extractPositives(int[] intArray)
	{
		//System.out.println("extractPositives NOT IMPLEMENTED");
		int length = intArray.length;
		int newlength = 0;
		for(int i=0;i < length;i++){
			if (intArray[i]>=0){
				newlength++;
			}
		}
		int[] endArray = new int[newlength];
		int j=0;
		for(int i=0; i<newlength; i++){
			if (intArray[i]>=0){
				int x = intArray[i];
				endArray[j]=x;
				j++;
			}
		}
		return endArray;
	}

	// END PART 2


	// BEGIN PART 3

	/**
	 * Read in data from a file, print out the data in the specified format -
	 *    "Name: *name*, Age:*age*" and then print out all of the names in a row.
	 *
	 * @param filename string
	 */
	public void readAndPrint(String filename)
	{
		//System.out.println("readFromFile NOT IMPLEMENTED");
		Lab1 lab = new Lab1();
		try {
			Scanner people = new Scanner(new File(filename));
			String[] names = new String[7];
			int i=0;
			while(people.hasNext()){
				names[i]=people.next();
				System.out.print("Name: "+names[i]);
				i++;
				if (people.hasNextInt()){
					System.out.println(", Age: "+people.next());
				}
			}
			for(i=0;i<names.length;i++){
			System.out.print(names[i]+", ");
			}
		}
		catch (IOException E) {
			System.out.println("readIn: IOException!!");
			System.exit(0);
		}

	}


	// END PART 3



	public static void main(String[] args)
	{
		Lab1 lab = new Lab1();
		System.out.print("Input lower boundary: ");
		Scanner scan = new Scanner(System.in);
		int first = 0;
		int last = 0;
		if (scan.hasNextInt()){
			first = scan.nextInt();
		}
		else {
			System.out.println("There is no integer here.");
			System.exit(0);

		}
		System.out.print("Input upper boundary: ");
		if (scan.hasNextInt()){
			last = scan.nextInt();
		}
		else {
			System.out.println("There is no integer here.");
			System.exit(0);
		}
		lab.testRange(first, last);
		//Prompt user for first and last

		//System.out.println("Part 2 NOT IMPLEMENTED");
		//Use command line arguments as a data source
		//read in the file, create the array
		String fName = args[0];
		try {
			Scanner readin = new Scanner(new File(fName));
			int x=0;
			while(readin.hasNext()){
				x++;
				readin.nextInt();
			}
			int[] values = {10,-12,13,45,5,6,-110};
			int i= 0;
			//String numbers = readin.toString();
			//System.out.println(numbers);
			while(readin.hasNextInt()){
				int y = Integer.parseInt(readin.next());
				values[i]=y;
				i++;
			}
			System.out.println(Arrays.toString(lab.extractPositives(values)));
		}
		catch (IOException E) {
			System.out.println("readIn: IOException!!");
			System.exit(0);
		}
		//System.out.println("Part 3 NOT IMPLEMENTED");
		//Use the same command line arguments as a data source
		lab.readAndPrint(args[1]);
	}

}
