import java.util.ArrayList;


public class Queue implements QueueIF {

        // This class implements the Queue Interface  QueueIF

	// maintains expression
	private ArrayList<String> expQueue;
	
	// debug controls debug reporting
	private boolean debug;
	
	// initialze expQueue and debug
	public Queue(boolean debug){
		this.debug = debug;
		expQueue = new ArrayList<String>();
	}
	
        public static void main(String[] args) throws QueueException{
    	Queue q = new Queue(false);
    	q.dequeue();
    }

		@Override
		public void enqueue(String token) {
			// TODO Auto-generated method stub
			if(debug){
				System.out.println("enqueue: " + token);
			}
			expQueue.add(token);
		}

		@Override
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

		@Override
		public int size() {
			// TODO Auto-generated method stub
			return expQueue.size();
		}
}
