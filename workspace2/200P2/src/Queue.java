import java.util.ArrayList;


public class Queue implements QueueIF {

	// maintains expression, initialize in constructor
	private ArrayList<String> expQueue;
        // debug flag, set in constructor
	private boolean debug;
	
	// implement constructor
	public Queue(boolean debug){
		this.debug = debug;
		expQueue = new ArrayList<String>();
	}
	
	/* implement:
         * enqueue token at the end of expQueue
	 * In debug mode print "enqueue: " + enqueued value
	 */
	public void enqueue(String token){
		if(debug){
		System.out.println("enqueue: " + token);
	}
	expQueue.add(token);
	}
	
	/* implement
         * dequeue token from the front of the expQueue
	 * If expQueue empty, throw QueueException("dequeueing empty queue!")
	 * In debug mode print "dequeue: " + dequeued value
	 */ 
	public String dequeue() throws QueueException {
	// TODO Auto-generated method stub
	if(expQueue.isEmpty()){
		throw new QueueException("dequeueing empty queue!!");
	}
	String token = expQueue.get(0);
	if(debug){
		System.out.println("dequeue: " + token);// dequeue token from the front of the expQueue
	}
	expQueue.remove(0);
	return token;
}

	// implement, return size (#elements) of the queue
	public int size() {
	// TODO Auto-generated method stub
	return expQueue.size();
}

        // provided, do not change
	public String toString(){
		return expQueue.toString();
	}
	
        public static void main(String[] args) throws QueueException{
    	Queue q = new Queue(false);
    	q.enqueue("not");
    	q.enqueue("true");
    	System.out.println(q);
    	System.out.println(q.dequeue());
    	System.out.println(q.dequeue());
	}
}