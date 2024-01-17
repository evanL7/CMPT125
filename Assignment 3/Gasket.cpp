#include "Gasket.h"
#include "Colour.h"

double GASKET_SIDE_TO_HEIGHT = 0.86666666;

/*
	Bonus Problem: Writing Class Gasket

	This program builds Gasket objects that can be displayed graphically.

	Author Evan Law August 4, 2023;
*/

void Gasket::GasketDivide(Triangle* listOfSubTriangles, int trianglesIn)
{
	if(trianglesIn <= 0  || trianglesIn >= static_cast<int>(pow(3,iterations) ) )
	{
		cerr << " illegal number of triangle in Gasket Divide";
		exit(1);
	}
	else
	{
		for (int k = trianglesIn-1; k >= 0; k--)
		{
			listOfSubTriangles[k].TriangleDivide(&listOfSubTriangles[k*3] );
		}
	}
}

Gasket::Gasket()
{
	sideLength = 100;
	xLocation = 0;
	yLocation = 0;
	iterations = 0;
	lenSubTriList = 1;
	listOfSubTriangles = new Triangle[lenSubTriList];
	listOfSubTriangles[0] = Triangle(xLocation, yLocation, sideLength, gasketColour);
	gasketColour = Colour(0, 0, 0, 255);
}

Gasket::Gasket(int iterationsValue, int xLocationValue, int yLocationValue, int sideLengthValue, Colour gasketColourValue)
{
	iterations = iterationsValue;
	xLocation = xLocationValue;
	yLocation = yLocationValue;
	sideLength = sideLengthValue;
	gasketColour = gasketColourValue;
	lenSubTriList = static_cast<int> (pow(3, iterations));
	listOfSubTriangles = new Triangle[lenSubTriList];

	if (xLocationValue < 0 || xLocationValue > pageWidth || yLocationValue < 0 || yLocationValue > pageLength) // Check if xLocation or yLocation is out of bounds
	{
		if (xLocationValue < 0 || xLocationValue > pageWidth)
		{
			cout << "x position of Gasket object is off the page\n";
		}
		if (yLocationValue < 0 || yLocationValue > pageLength)
		{
			cout << "y position of Gasket object is off the page\n";
		}
		cout << "x position and y position have been reset to 0" << endl;
		xLocation = 0;
		yLocation = 0;
	}

	Gasket::SetIterations(iterationsValue);
	Gasket::SetSideLength(sideLengthValue);
}

// Initialization using initialization lists for efficiency
Gasket::Gasket(const Gasket& toBeCopied)
	: iterations(toBeCopied.iterations), xLocation(toBeCopied.xLocation), yLocation(toBeCopied.yLocation), sideLength(toBeCopied.sideLength), 
	  gasketColour(toBeCopied.gasketColour), listOfSubTriangles(toBeCopied.listOfSubTriangles), lenSubTriList(toBeCopied.lenSubTriList)
{}

Gasket::~Gasket()
{
	delete[] listOfSubTriangles;
}

// Requested Get of accessors (Get functions)
// to Get the values of each of the
// variable members of the class Gasket
int Gasket::GetIterations() const
{
	return iterations;
}

int Gasket::GetXLocation() const
{
	return xLocation;
}

int Gasket::GetYLocation() const
{
	return yLocation;
}

int Gasket::GetSideLength() const
{
	return sideLength;
}

Colour Gasket::GetGasketColour() const
{
	return gasketColour;
}

// Requested Set functions to Set each of the variable members
// of class Gasket from outside of class Gasket.
// There is interaction between the members length width and area
// so Setting the variable member itself is not always adequate
// other calculations may be needded to maintain the consistancy
// of the instance of the class (the object)

void Gasket::SetIterations( const int iterationsValue)
{
    iterations = iterationsValue;

	if (iterationsValue < 0) // Check if iterations negative
	{
		cerr << "Invalid iteration value for GasketDisplay." << endl;
		return;
	}

	lenSubTriList = static_cast<int> ( pow( 3.0, iterations ) );
	delete [] listOfSubTriangles;
	listOfSubTriangles = NULL;
	listOfSubTriangles = new Triangle[lenSubTriList];
	listOfSubTriangles[0]= Triangle(xLocation, yLocation, sideLength, gasketColour);

	for (int k=1; k <= iterations; k++)
	{
		GasketDivide(listOfSubTriangles, lenSubTriList / 3 );
	}
}

void Gasket::SetSideLength(const int sideLengthValue)
{
	int height = 0;
    sideLength = sideLengthValue;
	//Check if the change in sideLength makes the
	//Triangle extend beyond any edge of the page
	if(sideLength < 1)  sideLength = 1;
	if( xLocation + sideLength > pageWidth )
	{
		cout << "scaling in x\n";
		cout << "sideLength was " << sideLength;
		sideLength = pageWidth - xLocation;
		cout << " sideLength now is " << sideLength << endl;
	}
	height = static_cast<int> (sideLength * GASKET_SIDE_TO_HEIGHT);
	if( yLocation + height > pageLength )
	{
		cout << "scaling in y\n";
		cout << "sideLength was " << sideLength;
		sideLength = static_cast<int>((pageLength - yLocation) / GASKET_SIDE_TO_HEIGHT);
		cout << " sideLength now is " << sideLength << endl;
	}
	listOfSubTriangles[0]= Triangle(xLocation, yLocation, sideLength, gasketColour);
	for (int k=1; k <= iterations; k++)
	{
		GasketDivide(listOfSubTriangles, lenSubTriList / 3 );
	}
}

void Gasket::SetXLocation(const int xLocationValue)
{
	xLocation = xLocationValue;

	if (xLocation >= pageWidth || xLocation < 0) // Ensure new xLocation is within bounds      
	{
		cout << "x position of Gasket object is off the page\n";
		cout << "x position and y position have been reset to 0" << endl;
		xLocation = 0;
		yLocation = 0;
	}
}

void Gasket::SetYLocation(const int yLocationValue)
{
	yLocation = yLocationValue;

	if (yLocation >= pageLength || yLocation < 0) // Ensure new yLocation is within bounds      
	{
		cout << "y position of Gasket object is off the page\n";
		cout << "x position and y position have been reset to 0" << endl;
		xLocation = 0;
		yLocation = 0;
	}
}

void Gasket::SetGasketColour(const Colour gasketColorValue)
{
	gasketColour = gasketColorValue;
}

void Gasket::GasketDisplay(BMP& myImageValue, int thisIter, string theOutputFile)
{
	if (thisIter < 0)
	{
		cerr << "Invalid iteration value for GasketDisplay." << endl;
		return;
	}
	for (int i = 0; i < lenSubTriList; i++) // Prints each triangle in the Gasket
	{
		listOfSubTriangles[i].TriangleDisplay(myImageValue, theOutputFile);
	}
}

void Gasket::GasketPrint()
{
	cout << setw(19) << "iterations" << setw(10) << iterations << endl;
	cout << setw(19) << "xLocation" << setw(10) << xLocation << endl;
	cout << setw(19) << "yLocation" << setw(10) << yLocation << endl;
	cout << setw(19) << "sideLength" << setw(10) << sideLength << endl;
	cout << setw(19) << "gasketColour" << setw(10) << gasketColour << endl;
	cout << setw(19) << "lenSubTriList" << setw(10) << lenSubTriList << endl;
	cout << endl;

	for (int i = 0; i < lenSubTriList; i++) // Prints each triangle in the Gasket to the console
	{
		listOfSubTriangles[i].TrianglePrint();
		cout << "\n";
	}
}
