
public class Species {	

	//Put the instance variable here.
	public String name;
	public int pop;
	public double grow;
	//Create a Species constructor that takes in a String for its name, an int for
	//its population, and a double for its growth rate (this will represent
	// percent).
public Species(String names, int pops, double grows){
	name=names;
	pop=pops;
	grow=grows;
	if (pop>1500){
		pop=1500;
	}
	if (pop<1){
		pop=1;
	}
	if (grow>.2){
		grow=.2;
	}
	if (grow<.01){
		grow=.01;
	}
}

	//mergeSpecies adds the populations of the two species, changes the name
	//of the species to the concatenation of the two names, and the growth
	//rate to the maximum of the two growth rates
	public void mergeSpecies(Species other){
		//System.out.println("mergeSpecies NOT IMPLEMENTED YET");
		name = this.name+other.name;
		pop = this.pop+other.pop;
		if (other.grow>this.grow){
			grow = other.grow;
		}
	}

	public String toString(){
		//System.out.println("toString NOT IMPLEMENTED YET");
		String namer = "Species: " + name + "\n";
		String pops = "Population: " +pop + "\n";
		String grows = "Growth Rate: " +grow + "\n";
		return namer + pops + grows;
	}


	//increases the population according to the growth rate of the species, i.e.
	// updates the population instance variable
	public void grow() {
		//System.out.println("grow NOT IMPLEMENTED YET");
		double years = pop + pop*grow;
		pop = (int)years;
	}

	//returns the population of the species in x years according to its growth rate
	public int populationInXYears(int x){
		//System.out.println("getPoplulationInXYears NOT IMPLEMENTED YET");
		int initial = pop;
		for (int i=0;i<x;i++){
			this.grow();
		}
		int total = pop;
		pop = initial;
		System.out.println("The number of " + name + " in " + x + " year(s) will be " + total);
		return total;
	}

}
