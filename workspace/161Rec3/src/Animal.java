import java.io.File;
import java.io.IOException;
import java.util.*;

public class Animal {

	//begin class variables//
	private String name;		
	private int topSpeed;
	//end class variable//	

	//begin getters and setters//	
	//create the getters and setters, there is a shortcut by hovering over the variable names
	//for the setter associated with topSpeed make sure the values are between 0 and 70
	// Raise an exception if topSpeed is not within these values.
	public String getName(){
		return this.name;
	}
	public int getSpeed(){
		return this.topSpeed;
	}
	public void setName(String names){
		this.name=names;
	}
	public void setSpeed(int speed){
		this.topSpeed=speed;
	}
	//end getters and setters//

	//begin constructors//
	//create a constructor that takes in a String for the name and an int for the topSpeed
	//use your setters to initialize the instance variables
	public Animal(String names, int speed){
		name=names;
		if (speed<0||speed>70){
			System.out.println("Speed not within range 0-70.");
			System.exit(1);
		}
		topSpeed=speed;
	}
	//end constructors//

	//begin class methods//
	//create an equals(Object other) method that returns True if two Animal's top speeds are 
	//within 2 mph of each other
	public boolean equals(Object other){
		if(other instanceof Animal){
			Animal p = (Animal)other;
			if(this.topSpeed-p.topSpeed<=2&&p.topSpeed-this.topSpeed<=2){
				return true;
			}
			else return false;
		}
		else return false;
	}
	// Create a toString method
	// Sample String to return for this toString method
	// Name: elephant     Top Speed: 25
	public String toString(){	
		return "Name: "+name+"; Top Speed: "+topSpeed;
	}
	//end class methods//

}
