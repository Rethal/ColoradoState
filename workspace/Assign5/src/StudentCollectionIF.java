
public interface StudentCollectionIF {
	// the constructor is not in the interface
	// it initializes course
	
	// if the student is not in the collection yet
	//   insert the student ***in order*** and return true
	// else return false 
	//
	// order is defined by the compareTo method of StudentIF
	// 
	public boolean insort(StudentIF s);
	
	// remove StudentIF s *** using its equals method ***
	public boolean remove(StudentIF s);
	
	// size
	public int size();
	
	// Compute the average score of all students
	public double classAvg();
	
	// Compute the top score of the student collection
	public double classTopScore();
}
