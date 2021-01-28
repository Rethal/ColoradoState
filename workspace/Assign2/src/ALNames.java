import java.util.ArrayList;

public class ALNames {
    private ArrayList<Name> names;
    
    public ALNames(){
//      System.out.println("ALNames constructor not implemented yet");
        names = new ArrayList<Name>();
     }


    //TODO ALNames.addName
    /**
     * 
     * @param n: Name
     * only if n not already in ALNames
     */
    public void addName(Name n){
//          System.out.println("addName not implemented yet");
            if(!names.contains(n))names.add(n);
    }
  
    
    //TODO Implement ALNames.toString
    public String toString(){
            return names.toString();
    }
    
    public static void main(String[] args){
    	ALNames alN = new ALNames();
    	Name n1 = new Name("Wim", "Bohm");
    	alN.addName(n1);
    	System.out.println("ALNames alN: " + alN);
    	
    	
    	Name n2 = new Name("Brent", "Grundman");
    	alN.addName(n2);
    	System.out.println("ALNames alN: " + alN);
    	
    	
    	
    }


}
