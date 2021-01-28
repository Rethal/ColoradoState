import java.util.Scanner;

public class CircleOfLife {

	public static void main(String args[]){
		//Create a new Species object here, passing in the appropriate arguments
		Scanner key = new Scanner(System.in);
		String spec1;
		int pop1;
		double grow1;
		System.out.print("Species: ");
		spec1 = key.next();
		System.out.print("Population (1<x<1500): ");
		pop1=key.nextInt();
		System.out.print("Growth Rate (.01<x<.2): ");
		grow1=key.nextDouble();
		Species species1 = new Species(spec1, pop1, grow1);

		//print out the species' growth rate
		System.out.println("Growth rate: "+species1.grow);

		//use the species' toString here
		System.out.print(species1);

		//call populationInXYears here
		species1.populationInXYears(1);

		//Create a new Species object here, passing in the appropriate arguments using a very large number for the population (e.g. 100000000)
		Species species2 = new Species("Wolf", 123456789, .01);
		//print out the species' population to make sure it is set to 1500
		System.out.println("Population: " + species2.pop);
		//call populationInXYears here, feel free to hardcode in the int to be passed to the method
		species2.populationInXYears(3);
		//call mergeSpecies here
		species1.mergeSpecies(species2);
		//test that mergeSpecies is doing what you expected it to
		System.out.print(species1);
	}
}
