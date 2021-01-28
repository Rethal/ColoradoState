#include <Animal.h>

int IDstruct::id_ctr = 0;

int main() {

  cout << "Main program has started" << endl;
  cout << endl;

  IDstruct id;
  cout << "id.id is currently : " << id.id << endl;
  id.id = 10;
  cout << "id.id was set to 10.. we received : " << id.id << endl;
  cout << "id.IdCtr() is : " << id.IdCtr() << endl;

  cout << endl;

  ZooProperty zoo;
  cout << "zoo.value is currently : " << zoo.value << endl;
  cout << "zoo.ID() is : " << zoo.ID() << endl;
  zoo.value = 69.1;
  cout << "zoo.value is now : " << zoo.value << endl;
  cout << "zoo.ID() is uh : " << zoo.ID() << endl; 
  
  cout << endl;

  cout << "ZooProperty SDzoo(zoo) occured" << endl;
  ZooProperty SDzoo(zoo);
  cout << "now SDzoo.ID() is : " << SDzoo.ID() << endl;
  cout << "now SDzoo.value : " << SDzoo.value << endl;

  cout << endl;

  Quagga q;
  cout << "q.value is : " << q.value << endl;
  cout << "q.value is now set to : 123" << endl;
  q.value = 123;
  cout << "q.value is expected to be 123 : " << q.value << endl;
  cout << "q.Name() is : " << q.Name() << endl;
  cout << "q.ID() is : " << q.ID() << endl;
  //cout << "q.IdCtr() is " << q.IdCtr() << endl;

  return 0;
}
