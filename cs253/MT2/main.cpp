#include <Animal.h>

int IDstruct::id_ctr = 0;

int main() {

  vector<Animal*> myBitches; 

  Animal *asshole = new Mammal();
  cout << "asshole->Name() is : " << asshole->Name() << endl; 
  //cout << "asshole->Temperature() is : " << asshole->Temperature() << endl;
  cout << "asshole->WarmUp() is : " << asshole->WarmUp() << endl;

  Mammal *myHoe = new Quagga();
  Quagga *queef = new Quagga();

  myBitches.push_back(asshole);
  myBitches.push_back(myHoe);
  myBitches.push_back(queef);

  for (unsigned int i = 0; i < myBitches.size(); i++) {
    cout << "myBitches.Name() is : " << myBitches[i]->Name() << endl; 
  }

  cout << endl;

  //asshole->~Mammal();
  delete asshole;
  delete myHoe;
  delete queef;

  return 0;
}
