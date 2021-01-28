#include "Tree.h"

int main()
{
	// This is a main file designed to allow some testing of a few things.
	// 

	// put some of these down, we'll use them later
	Quagga* a = new Quagga("a");
	Quagga* b = new Quagga("b");
	Quagga* c = new Quagga("c");
	Quagga* d = new Quagga("d");
	Quagga* e = new Quagga("e");

	Quagga *x, *y, *z;

	Quagga A("a");
	Quagga B("b");
	Quagga C("c");
	Quagga D("d");
	Quagga E("e");

	//Let's just throw up a Quagga Tree.
	QuaggaTree* tree1 = new QuaggaTree();
	if (!tree1->push(new Quagga("c"))) std::cout << "PUSH FAILED FOR C!";
	else std::cout << "c good" << endl;
	tree1->print(std::cout);
	if (!tree1->push(new Quagga("e"))) std::cout << "PUSH FAILED FOR E!";
	tree1->print(std::cout);
	if (!tree1->push(new Quagga("a"))) std::cout << "PUSH FAILED FOR A!";
	tree1->print(std::cout);
	if (!tree1->push(new Quagga("d"))) std::cout << "PUSH FAILED FOR D!";
	tree1->print(std::cout);
	if (!tree1->push(new Quagga("b"))) std::cout << "PUSH FAILED FOR B!";
	tree1->print(std::cout);

	//QuaggaTree* tree1 = new QuaggaTree();
	if (!tree1->push(c)) std::cout << "PUSH FAILED FOR C!";
	tree1->print(std::cout);
	if (!tree1->push(e)) std::cout << "PUSH FAILED FOR E!";
	tree1->print(std::cout);
	if (!tree1->push(a)) std::cout << "PUSH FAILED FOR A!";
	tree1->print(std::cout);
	if (!tree1->push(d)) std::cout << "PUSH FAILED FOR D!";
	tree1->print(std::cout);
	if (!tree1->push(b)) std::cout << "PUSH FAILED FOR B!";
	tree1->print(std::cout);

	if (!tree1->push(new Quagga("b"))) std::cout << "PUSH FAILED FOR B!";
	if (!tree1->push(new Quagga())) std::cout << "PUSH FAILED!";
	if (!tree1->push(new Quagga("c"))) std::cout << "PUSH FAILED FOR C!";
	if (!tree1->push(new Quagga())) std::cout << "PUSH FAILED!";

	tree1 = new QuaggaTree();
	if (!tree1->push(new Quagga())) std::cout << "PUSH FAILED!";
	if (!tree1->push(new Quagga("c"))) std::cout << "PUSH FAILED FOR C!";
	if (!tree1->push(new Quagga())) std::cout << "PUSH FAILED!";
	if (!tree1->push(x)) std::cout << "PUSH FAILED FOR X!";
	if (!tree1->push(z)) std::cout << "PUSH FAILED FOR Z!";

	QuaggaTree* tree2 = new QuaggaTree(*tree1);
}