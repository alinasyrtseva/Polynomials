#include <cstdlib>
#include <Windows.h>

#include <iostream> 
#include <clocale> 
#include <conio.h>

#include "List.h"
#include "Polynomials.h"
#include "Tables.h"

using namespace std;

int main (int argc, char *argv[])
{  
    system("color F0");

	char* exp1  = "-2.5*x^2y^2z^2+2.5*x^2y^2z^2-3*x^3y^3z^3";
	char* expr2  = "3*x^3y^3z^3";
	char* exp3  = "3*x^7y^7z^7";
	char* exp4  = "6*x^7y^7z^7";
	Polynomial poly1 = Polynomial (exp1);
	Polynomial poly2 = Polynomial (expr2);
	Polynomial poly3 = Polynomial (exp3);
	Polynomial poly4 = Polynomial (exp4);

	SortTable tab (5);
	tab.InsRecord ("pol1", poly1);
	tab.InsRecord ("pol4", poly4);
	tab.InsRecord ("pol3", poly2);
	tab.InsRecord ("pol2", poly3);
	
	//tab.DelRecord ("pol3");
	tab.Print ();

	cout << endl;

	cout << *(tab.FindRecord ("pol2")) << endl;

    //getch ();
	return 0;
}