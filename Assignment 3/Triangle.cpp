#include "Triangle.h"
#include "Colour.h"

int Triangle::TrianglesExisting;
int Triangle::TrianglesCreated;
double TRIANGLE_SIDE_TO_HEIGHT = 0.86666666;

/*
    Problem 2: Writing Class Triangle

    This program builds triangle objects that can be displayed graphically.

    Author Evan Law August 4, 2023;
*/

void Triangle::TriangleDisplay(BMP& myImageValue, string theOutputFile)
 {
	int yHeight = 0;
	double offset = 0;
	int t1 = 0; 
	int t2 = 0;
    yHeight = static_cast<int> (sideLength * sqrt(3.0)/2.0 );
    if(yLocation < 0|| yLocation > pageLength ||
        yLocation + yHeight > pageLength)
    {
        cerr << "point may be located outside of plotting page\n"
            << endl;
        return;
    }
    
    if(xLocation < 0|| xLocation >= pageWidth || 
        xLocation + sideLength > pageWidth )
    {
        cerr << "point may be located outside of plotting page\n"
            << endl;
        return;
    }
    
    // each pixel within the Triangle must be Set to the correct colour
    // myImageValue(i,j) is pixel j in row i
    // each value in the Colour object is Set for each pixel in 
    // the Triangle
	yHeight = static_cast<int> (sideLength * sqrt(3.0)/2.0 );
    for(int j=yLocation; j<(yLocation+yHeight); j++)
    {
		offset = static_cast<double>(sideLength) / yHeight/ 2.0;
		t1 = static_cast<int>( ceil( (j-yLocation+1) * offset) );
		t2 = static_cast<int>( floor( (j-yLocation+1) * offset) );
        for (int i=0; i < sideLength; i++)
        {
			if( i < t1 || i > sideLength - t2) continue;
            myImageValue(i+xLocation,j)->Red = triangColour.GetRedNumber();
            myImageValue(i+xLocation,j)->Blue = triangColour.GetBlueNumber();
            myImageValue(i+xLocation,j)->Green = triangColour.GetGreenNumber();
            myImageValue(i+xLocation,j)->Alpha = triangColour.GetAlphaNumber();
        }
    }
    
    //write generated bitmap image to a file
    myImageValue.WriteToFile(theOutputFile.c_str());
}

void Triangle::TriangleDivide(Triangle* TriList)
{
	int halfSide;
	int yHalf;
	halfSide = sideLength / 2;
	// constant below is  = sqrt(3.0)/4 * sidelength
	yHalf = static_cast<int> (halfSide * TRIANGLE_SIDE_TO_HEIGHT);
	TriList[2] = Triangle(xLocation + halfSide / 2, yLocation + yHalf, halfSide, triangColour);
	TriList[1] = Triangle(xLocation + halfSide, yLocation, halfSide, triangColour);
	TriList[0] = Triangle(xLocation, yLocation, halfSide, triangColour);
}

Triangle::Triangle()
{
    sideLength = 10;
    xLocation = 0;
    yLocation = 0;
    TrianglesCreated++;
    TrianglesExisting++;
    triangColour = Colour(0, 0, 0, 255);
}

// Initialization using initialization lists for efficiency
Triangle::Triangle(int xLocationValue, int yLocationValue, int sideLengthValue, Colour blockColourValue)
    : sideLength(sideLengthValue), xLocation(xLocationValue), yLocation(yLocationValue), triangColour(blockColourValue)
{
    if (xLocationValue < 0 || xLocationValue > pageWidth || yLocationValue < 0 || yLocationValue > pageLength) // xLocation or yLocation out of bounds
    {
        cout << "x position = " << xLocationValue << " and / or y position = " << yLocationValue << " of Triangle object is off the page\n";
        cout << "x position and y position have been reset to 0" << endl;
        xLocation = 0;
        yLocation = 0;
    }
    if (xLocation + sideLength > pageWidth)
    {
        cout << "Triangle object partially off the page \n" << "xlocation is " << xLocation << "\n";
        cout << " sideLength was " << sideLength;
        sideLength = pageWidth - xLocation;
        cout << " sideLength is " << sideLength << endl;
    }
    if (yLocation + sideLength > pageLength && (pageLength - yLocation)/TRIANGLE_SIDE_TO_HEIGHT < sideLength) // Only change sideLength if new size is smaller
    {
        cout << "Triangle object partially off the page \n" << "ylocation is " << yLocation << "\n";
        cout << " sideLength was " << sideLength;
        sideLength = (pageLength - yLocation) / TRIANGLE_SIDE_TO_HEIGHT;
        cout << " sideLength is " << sideLength << endl;
    }
    TrianglesCreated++;
    TrianglesExisting++;
}

Triangle::Triangle(int xLocationValue, int yLocationValue, Colour blockColourValue)
    : sideLength(10), xLocation(xLocationValue), yLocation(yLocationValue), triangColour(blockColourValue)
{
    if (xLocationValue < 0 || xLocationValue > pageWidth || yLocationValue < 0 || yLocationValue > pageLength) // Check if xLocation or yLocation is out of bounds
    {
        cout << "x position = " << xLocationValue << " and / or y position = " << yLocationValue << " of Triangle object is off the page\n";
        cout << "x position and y position have been reset to 0" << endl;
        xLocation = 0;
        yLocation = 0;
    }
    if (xLocation + sideLength > pageWidth) // Check if sideLength is too big
    {
        cout << "Triangle object partially off the page \n" << "xlocation is " << xLocation << "\n";
        cout << " sideLength was " << sideLength;
        sideLength = pageWidth - xLocation;
        cout << " sideLength is " << sideLength << endl;
    }
    if (yLocation + sideLength > pageLength && (pageLength - yLocation)/TRIANGLE_SIDE_TO_HEIGHT < sideLength) // Only change sideLength if new size is smaller
    {
        cout << "Triangle object partially off the page \n" << "ylocation is " << yLocation << "\n";
        cout << " sideLength was " << sideLength;
        sideLength = (pageLength - yLocation) / TRIANGLE_SIDE_TO_HEIGHT;
        cout << " sideLength is " << sideLength << endl;
    }
    TrianglesCreated++;
    TrianglesExisting++;
}

Triangle::Triangle(const Triangle& toBeCopied)
    : sideLength(toBeCopied.sideLength), xLocation(toBeCopied.xLocation), yLocation(toBeCopied.yLocation), triangColour(toBeCopied.triangColour)
{
    TrianglesCreated++;
    TrianglesExisting++;
}

Triangle::~Triangle()
{
    TrianglesExisting--;
}

int Triangle::GetSideLength() const
{
    return sideLength;
}

int Triangle::GetXLocation() const
{
    return xLocation;
}

int Triangle::GetYLocation() const
{
    return yLocation;
}

Colour Triangle::GetTriangColour() const
{
    return triangColour;
}

int Triangle::GetTrianglesCreated()
{
    return TrianglesCreated;
}

int Triangle::GetTrianglesExisting()
{
    return TrianglesExisting;
}

void Triangle::SetTriangColour(const Colour blockColorValue)
{
    triangColour = blockColorValue;
}

void Triangle::SetSideLength(const int setSideLengthValue)
{
    if (setSideLengthValue > 0 && xLocation + setSideLengthValue <= pageWidth && yLocation + setSideLengthValue <= pageLength)
    {
        sideLength = setSideLengthValue;
    }
    else
    {
        cout << "sideLength reset to assure the whole triangle is on the page\n";
        if (xLocation + setSideLengthValue > pageWidth)
        {
            cout << "xLocation is " << xLocation;
            cout << " sideLength was " << setSideLengthValue;
            sideLength = pageWidth - xLocation;
            cout << "\n sideLength is " << sideLength << endl;
        }
        if (yLocation + setSideLengthValue > pageLength && (pageLength - yLocation) / TRIANGLE_SIDE_TO_HEIGHT < sideLength) // Only change sideLength if new size is smaller
        {
            cout << "yLocation is " << yLocation;
            cout << " sideLength was " << setSideLengthValue;
            sideLength = (pageLength - yLocation) / TRIANGLE_SIDE_TO_HEIGHT;
            cout << "\n sideLength is " << sideLength << endl;
        }
    }
}

void Triangle::SetXLocation(const int xLocationValue)
{
    xLocation = xLocationValue;

    if (xLocation >= pageWidth || xLocation < 0) // Ensure new xLocation is within bounds      
    {
        xLocation = 0;
        yLocation = 0;
    }
    if (xLocation + sideLength > pageWidth) // Check if adjustment to sideLength is necessary
    {
        sideLength = pageWidth - xLocation;
    }
}

void Triangle::SetYLocation(const int yLocationValue)
{
    yLocation = yLocationValue;

    if (yLocation >= pageLength || yLocation < 0) // Ensure new xLocation is within bounds      
    {
        xLocation = 0;
        yLocation = 0;
    }
    if (yLocation + sideLength > pageLength && (pageLength - yLocation) / TRIANGLE_SIDE_TO_HEIGHT < sideLength) // Only change sideLength if new size is smaller
    {
        sideLength = (pageLength - yLocation) / TRIANGLE_SIDE_TO_HEIGHT;
    }
}

void Triangle::SetTrianglesCreated(int numberCreated)
{
    TrianglesCreated = numberCreated;
}

void Triangle::SetTrianglesExisting(int numberExisting)
{
    TrianglesExisting = numberExisting;
}

ostream& operator << (ostream& os, const Triangle& myTriangle)
{
    os << setw(19) << "sideLength" << setw(10) << myTriangle.GetSideLength() << endl;
    os << setw(19) << "xLocation" << setw(10) << myTriangle.GetXLocation() << endl;
    os << setw(19) << "yLocation" << setw(10) << myTriangle.GetYLocation() << endl;
    os << setw(19) << "TrianglesCreated" << setw(10) << myTriangle.GetTrianglesCreated() << endl;
    os << setw(19) << "TrianglesExisting" << setw(10) << myTriangle.GetTrianglesExisting() << endl;
    os << setw(19) << "triangColour" << setw(10) << myTriangle.GetTriangColour() << endl;
    return os;
}

void Triangle::TrianglePrint()
{
    cout << setw(19) << "sideLength" << setw(10) << sideLength << endl;
    cout << setw(19) << "xLocation" << setw(10) << xLocation << endl;
    cout << setw(19) << "yLocation" << setw(10) << yLocation << endl;
    cout << setw(19) << "TrianglesCreated" << setw(10) << TrianglesCreated << endl;
    cout << setw(19) << "TrianglesExisting" << setw(10) << TrianglesExisting << endl;
    cout << setw(19) << "triangColour" << setw(10) << triangColour << endl;
}

const Triangle& Triangle::operator = (const Triangle& Triangle2)
{
    if (this != &Triangle2) // First check if the two objects are not already the same
    {
        sideLength = Triangle2.sideLength;
        xLocation = Triangle2.xLocation;
        yLocation = Triangle2.yLocation;
        triangColour = Triangle2.triangColour;
    }
    return *this;
}

bool Triangle::operator==(const Triangle& Triangle2) const
{
    return (sideLength == Triangle2.sideLength &&
        xLocation == Triangle2.xLocation &&
        yLocation == Triangle2.yLocation &&
        triangColour == Triangle2.triangColour);
}
