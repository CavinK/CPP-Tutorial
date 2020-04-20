#include <iostream>
#include <string>
using namespace std;

class Chef
{
	public:
		void makeChicken()
		{
			cout << "The chef makes chicken" << endl;
		}
		void makeSalad()
		{
			cout << "The chef makes salad" << endl;
		}
		void makeSpecialDish()
		{
			cout << "The chef makes bbq ribs" << endl;
		}
};

class ItalianChef : public Chef
{
	public:
		void makeChicken() // override?(https://www.programcreek.com/2009/02/overriding-and-overloading-in-java-with-examples/)
		{
			cout << "The chef makes yummy chicken" << endl;
		}
		void makePasta()
		{
			cout << "The chef makes pasta" << endl;
		}
};

int main()
{
	Chef chef;
	chef.makeChicken();
	
	cout << endl;
	
	ItalianChef italianChef;
	italianChef.makeSpecialDish();
	italianChef.makeChicken();
	italianChef.makePasta();
	
	return 0;
}