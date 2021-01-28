import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;


public class GuinnessBook {

	private ArrayList<Animal> landAnimals;

	public GuinnessBook(String filename) throws FileNotFoundException{

		landAnimals = new ArrayList<Animal>();

		File animalFile = new File(filename);
		Scanner scan = new Scanner(animalFile);
		
		while(scan.hasNextLine()){
			String[] animalInfo = scan.nextLine().split(" ");
			String animalName = "";
			
			for(int i = 0; i < (animalInfo.length-1); i++){
				animalName += animalInfo[i] + " ";
			}
			animalName = animalName.trim();
			Integer topSpeed = Integer.parseInt(animalInfo[animalInfo.length-1]);

			//insert the animal into the arraylist here, don't change any of the above code
			Animal p = new Animal(animalName,topSpeed);
			//if (!landAnimals.contains(p)){
				landAnimals.add(p);
			//}
			
		}
		scan.close();
	}


	public String toString(){
		//implement a toString for a GuinnessBook object
		//System.out.println("toString() NOT YET IMPLEMENTED");
		String animal = "";
		for (int i=0; i<landAnimals.size();i++){
		animal = animal+"\n"+landAnimals.get(i).toString();
		}
		return animal;
	}

	private void testGuinnessBook() throws FileNotFoundException {

        // uncomment the println statements to test the method for finding animals with a given speed
        // Is there an animal whose speed is close to x (i.e. within 2mph)?

         System.out.println("Is there an animal whose speed is around 70mph? " + landAnimals.contains(new Animal("fast animal", 70)));
         System.out.println("Is there an animal whose speed is around 35mph? " + landAnimals.contains(new Animal("slow animal", 35)));

        //If we would like to know which animal it is:
         System.out.println(landAnimals.get(landAnimals.indexOf(new Animal("fast animal", 70))));
         System.out.println(landAnimals.get(landAnimals.indexOf(new Animal("slow animal", 35))));

        //Now implement code to print all the animals whose speed is around 50mph
         Animal speedy = new Animal("speedy", 50);
         for(Animal s:landAnimals){
         if(s.equals(speedy)){
        	 System.out.println(s);
         }
         }
    }

    public static void main(String args[]) throws FileNotFoundException {
        // Once Animal.java is completed and GuinnessBook has a working toString,
        // uncomment the next two lines to test the constructor and toString
         GuinnessBook records = new GuinnessBook(args[0]);
         System.out.println(records);

        // Next, uncomment the following line and lines from testGuinnessBook to test your 
	// Animal class equals method
         records.testGuinnessBook();
    }

}