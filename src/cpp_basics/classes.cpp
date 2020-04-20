#include <iostream>
#include <string>
using namespace std;

class Student
{
	public:
		string name;
		string major;
		double gpa;
		
		// constructor
		Student()
		{
			name = "No name";
			major = "No major";
			gpa = 0.0;
		}
	
		Student(string aName, string aMajor, double aGpa)
		{
			name = aName;
			major = aMajor;
			gpa = aGpa;
		}
	
		// object function
		bool hasHonors()
		{
			if (gpa > 3.5)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	
		// setter and getter
		// void setGpa(double aGpa)
		// double getGpa()
};

int main()
{
	Student student1("Jim", "Business", 2.4);
	Student student2("Pam", "Art", 3.6);
	
	cout << student2.hasHonors() << endl;
	
	return 0;
}