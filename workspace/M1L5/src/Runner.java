import java.util.Arrays;

//Brenton Grundman 829460164
public class Runner {

	// A Runner has a name, a division, a number of races run;
	// an array of race times, and an array of opponent Times
	private String name = "";
	private int division = 0;
	int racesRun = 0;
	int[] raceTimes = new int[0];
	int[] opponentTimes = new int[0];
	

	/*TODO: 
	 * create a constructor that takes a String name and int division,
     * and initializes the appropriate instance variables
	 */ 
	public Runner(String name, int division){
		//System.out.println("constructor not implemented yet");
		this.name=name;
		this.division=division;

	}

    /*TODO:
     * return a string with the name, followed by a comma and space, 
     * followed by the division, followed by a comma and space, 
     * followed by the racesRun, followed by a newline, 
     * followed by the Arrays.toString of raceTimes, 
     * followed by a comma and space, 
     * followed by the Arrays.toString opponentTimes.
     * e.g.  "Jane Doe, 10, 3\n[3, 13, 7], [2, 12, 7]"
     */

	public String toString(){
		//System.out.println("toString not implemented yet");
		String namer = this.name;
		int div = this.division;
		int races = this.racesRun;
		String time1 = Arrays.toString(this.raceTimes);
		String time2 = Arrays.toString(this.opponentTimes);
		return namer+", "+div+", "+races+"\n"+time1+", "+time2;
	}

	// TODO: getter for name
    public String getName(){
		//System.out.println("getName not implemented yet");
		return this.name;
    }
    
    // TODO: getter for division
    public int getDivision(){
		//System.out.println("getDivision not implemented yet");
		return this.division;
    }
    
	/* TODO:
	 * checks whether other has the same name and division as this runner
	 */ 
   	public boolean equals(Runner other){
		//System.out.println("equals not implemented yet");
			if(this.name.equals(other.name) && this.division==other.division){
				return true;
			}
			else return false;
	}       
   	

   	/* TODO
   	 * add a race result at the front of raceTimes and opponentTimes 
   	 * and increment holesPlayed
   	 */
   	public void addRace(int time, int opponentTime){
		//System.out.println("addRace not implemented yet");
   		int[] time1=new int[raceTimes.length+1];
   		time1[0]=time;
   		for(int i=0;i<raceTimes.length;i++){
   			time1[i+1]=raceTimes[i];
   		}
   		raceTimes=time1;
   		int[] time2=new int[opponentTimes.length+1];
   		time2[0]=opponentTime;
   		for(int i=0;i<opponentTimes.length;i++){
   			time2[i+1]=opponentTimes[i];
   		}
   		opponentTimes=time2;
   		this.racesRun=this.racesRun+1;
   	}
   	
   	
   	/* TODO
   	 * pre i >= 0 and i < racesRun 
   	 * i is the index in the raceTimes and opponentTimes arrays
   	 * compute the score for match i: 
   	 *   0 if raceTime greater than opponentTime, 1 if equal, 2 if less
   	 */
    public int raceResult(int i){
		//System.out.println("raceResult not implemented yet");
    	if(raceTimes[i]>opponentTimes[i]){
    		return 0;
    	}
    	else if(raceTimes[i]<opponentTimes[i]){
    	return 2;	
    	}
    	else return 1;
    }
    
    /* TODO
     * return the sum of all race results, as computed in raceResult
     * if racesRun is 0, return 0;
     */
    public int totalScore(){
		//System.out.println("totalScore not implemented yet");
    	int x = 0;
    	if(this.racesRun>0){
    		for(int i=0;i<racesRun;i++){
    			x=x+raceResult(i);
    		}
    		return x;
    	}
    	else return 0;
    }
    

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Runner RJ = new Runner("Rita Jeptoo", 1);
		System.out.println("RJ: " + RJ);
		Runner BG = new Runner("Brent Grundman", 2);
		BG.addRace(12, 15);
		RJ.addRace(13, 14);
		BG.addRace(11, 10);
		RJ.addRace(13, 13);
		BG.addRace(5, 7);
		RJ.addRace(1, 1);
		BG.addRace(1, 34);
		BG.addRace(34, 1);
		System.out.println("RJ: " +RJ);
		System.out.println("BG: " + BG);
		System.out.println(BG.totalScore());
		System.out.println(RJ.totalScore());
	}
}


