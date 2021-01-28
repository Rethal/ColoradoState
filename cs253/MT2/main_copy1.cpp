#include <Animal.h>
#include <stdio.h>

int main() {

  bool cold = true;
 
  Animal *test; 
  cout << "'Animal* test' created" << endl;
  cout << "test->Name() is called: " << test->Name() << endl;
  // these seg faults wtf mate
  //cout << "test->WarmUp() is called: " << test->WarmUp() << endl;
  //cout << "test->Behave(true) is called: " << test->Behave(true) << endl;
  //cout << "test->Behave(false) is called: " << test->Behave(false) << endl;

  cout << endl;
  
  Mammal m;
  cout << "'Mammal m' created" << endl;
  cout << m.WarmUp() << endl;
  cout << m.Name() << endl;
  cout << m.Temperature() << endl;
  cout << "helloooooooooooooooooo " << m.Behave(cold) << endl;
  m.~Mammal();
  cout << "wtf " << m.WarmUp() << endl;
  cout << "pls? " << m.Name() << endl;

  cout << endl;

  Mammal doge(69.0);
  cout << "'Mammal doge(69.0)' created" << endl;
  cout << "doge.WarmUp() is called : \t" << doge.WarmUp() << endl;
  cout << "doge.Temperature is : \t\t" << doge.Temperature() << endl;
  cout << "doge.Name() is : \t\t" << doge.Name() << endl;
  cout << "doge.Behave(true) is called : \t" << doge.Behave(true) << endl;
  cout << "doge.Behave(false) is called : \t" << doge.Behave(false) << endl;

  cout << endl;
  
  Mammal cat;
  cout << "'Mammal cat' created" << endl;
  cout << "cat.Temperature() is : " << cat.Temperature() << endl;
  cout << "cat.Name() is : " << cat.Name() << endl;

  cout << endl;

  ZooProperty* zoo;
  cout << "'ZooProperty zoo' created" << endl;

  cout << endl;

  Quagga* fuckboi;
  cout << "'Qaugga fuckboi' created" << endl;
  // wtf how to access name
  //cout << "fuckboi->Name() is called : " << fuckboi->Name() << endl;
   
  return 0;
}
