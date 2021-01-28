#include <Animal.h>
#include <stdio.h>

int IDstruct::id_ctr = 9;

int main() {

  //Quagga *q1 = new Quagga();
  //Mammal *m1 = new Mammal();

  IDstruct animalID;
  cout << "'IDstrucct animalID' has been created" << endl;
  cout << "animalID.IdCtr() is called : " << animalID.IdCtr() << endl;
  cout << "animalID.id is called : " << animalID.id << endl;

  cout << endl;

  Quagga *q = new Quagga(); 
  cout << "'Quagga q' has  = new Quagga()been created" << endl;
  cout << "q.Name() is called : " << q->Name() << endl;
  cout << "q.ID() is called : " << q->ID() << endl;
  cout << "q.Value() is called : " << q->Value() << endl;
  cout << "q.Temperature() is called : " << q->Temperature() << endl;
  cout << "q.WarmUp() is called : " << q->WarmUp() << endl;
  cout << "q.Behave(true) is called : " << q->Behave(true) << endl;
  cout << "q.Behave(false) is called : " << q->Behave(false) << endl;
 
  //q = m;

  cout << "q = m code occured" << endl;
  cout << "q.Temperature() is now : " << q->Temperature() << endl;
 
  delete q;
  //delete animalID;
 
  Mammal mikey(69);
  cout << "'Mammal mikey(69)' was created" << endl;
  cout << "mikey.~Mammal() is called" << endl;
  mikey.~Mammal();
  cout << "did it get deleted?" << endl;
  mikey.Temperature();

  
  //delete q1;
  //delete m1;
     
  return 0;
}
