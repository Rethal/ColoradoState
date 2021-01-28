

public class LinkedBookList {

	private BookNode head;
	private int size;

	public LinkedBookList(){
		head = null;
		size = 0;
	}

	public int size(){
		return size;
	}

	//IMPLEMENT -- adds a book to the end of the linked list
	public void add(Book b){
		BookNode loca = new BookNode(b);
		if(size==0){
			head = loca;
		}
		else{
			head.setNext(loca);
		}
		size++;
		return;
	}

	//IMPLEMENT -- adds a book at the specific index, or at the end if index is greater than size
	public void add(Book b, int index){
		if(index>size){
			add(b);
		}
		else{
			BookNode that = new BookNode(b);
			BookNode current = head;
			int i = 0;
			//			while(current.getNext()!=null){
			//				if(s.compareTo(current.getNext().getStd())<0){
			//					break;
			//				}
			//				current = current.getNext();
			//			}
			while(current.getNext()!=null){
				current = current.getNext();
				i++;
				if(i==(index-1)){
					that.setNext(current.getNext());
					current.setNext(that);
					head = current;
//					that.setNext(current);
//					head.setNext(that);
					size++;
					return;
				}
			}
		}
		return;
	}

	//IMPLEMENT -- removes a book and returns it, or returns null if it is not present
	public Book remove(Book b){
		BookNode current = head;
		for(int i=0;i<size-1;i++){
			current=current.getNext();
			if(current.getNext().getBook()==b){
				current.setNext(current.getNext().getNext());
				head = current;
				return b;
			}
		}
		return null;
	}

	//IMPLEMENT -- removes a book at a specific indexand returns it, 
	//or returns null if it is not present
	public Book remove(int index){

		return null;
	}

	//IMPLEMENT -- returns the total number of pages in the linked list
	public int totalPages(){
		BookNode current = head;
		int pages = 0;
		while(current.getNext()!=null){
			System.out.println(current.getNumPages());
			System.out.println(pages);
			pages = pages+current.getNumPages();
			current = current.getNext();
			
			
		}
		return pages;
	}

	public String toString()
	{
		String res = "";

		return res;
	}

}




