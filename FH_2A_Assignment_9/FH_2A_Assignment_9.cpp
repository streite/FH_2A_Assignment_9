#include <string>
#include <iostream>
#include <sstream>

using namespace std;

// class Student prototype -----------------------
class Student
{
private:
   string lastName;
   string firstName;
   int totalPoints;

public:
   static const string DEFAULT_NAME;
   static const int DEFAULT_POINTS = 0;
   static const int MAX_POINTS = 1000;

public:
   Student( string lst = DEFAULT_NAME, string fst = DEFAULT_NAME,
      int pts = DEFAULT_POINTS);

   // accessors and mutators
   string getLastName() { return lastName; }
   string getFirstName() { return firstName; }
   int getTotalPoints() { return totalPoints; }

   bool setLastName(string last);
   bool setFirstName(string first);
   bool setPoints(int pts);

   static int compareTwoStudents( Student firstStud, Student secondStud );
   string toString();

private:
   static bool validString( string testStr );
   static bool validPoints( int testPoints );

};  // end of class Student prototype --------------

// class StudentArrayUtilities prototype -----------------------
class StudentArrayUtilities
{
public:
   static void printArray(string title, Student data[], int arraySize);
   static void arraySort(Student array[], int arraySize);

private:
   static bool floatLargestToTop(Student data[], int top);
   static void mySwap(Student &a, Student &b);
};

// static initializations that can't be done in-line
const string Student::DEFAULT_NAME = "zz-error";

int main()
{
   Student  myClass[] =
   {
      Student("smith","fred", 95),
      Student("bauer","jack",123),
      Student("jacobs","carrie", 195),  Student("renquist","abe",148),
      Student("3ackson","trevor", 108),  Student("perry","fred",225),
      Student("loceff","fred", 44),  Student("stollings","pamela",452),
      Student("charters","rodney", 295),  Student("cassar","john",321)
   };

   int arraySize = sizeof(myClass) / sizeof(myClass[0]);

   StudentArrayUtilities::printArray("Before: ", myClass, arraySize);
   StudentArrayUtilities::arraySort(myClass, arraySize);
   StudentArrayUtilities::printArray("After: ", myClass, arraySize);
}

// beginning of Student method definitions -------------

// constructor requires parameters - no default supplied
Student::Student( string last, string first, int points)
{
   if ( !setLastName(last) )
      lastName = DEFAULT_NAME;
   if ( !setFirstName(first) )
      firstName = DEFAULT_NAME;
   if ( !setPoints(points) )
      totalPoints = DEFAULT_POINTS;
}

bool Student::setLastName(string last)
{
   if ( !validString(last) )
      return false;
   lastName = last;
   return true;
}

bool Student::setFirstName(string first)
{
   if ( !validString(first) )
      return false;
   firstName = first;
   return true;
}

bool Student::setPoints(int pts)
{
   if ( !validPoints(pts) )
      return false;
   totalPoints = pts;
   return true;
}

// could be an instance method and, if so, would take one parameter
int Student::compareTwoStudents( Student firstStud, Student secondStud )
{
   int result;

   // this particular version based on last name only (case insensitive)
   result = firstStud.lastName.compare(secondStud.lastName);

   return result;
}

string Student::toString()
{
   string resultString;
   ostringstream cnvrtFirst, cnvrtLast, cnvrtPoints;

   cnvrtFirst << firstName;
   cnvrtLast << lastName;
   cnvrtPoints << totalPoints;

   resultString = " " + cnvrtLast.str()
      + ", " + cnvrtFirst.str()
      + " points: " + cnvrtPoints.str()
      + "\n";
   return resultString;
}

bool Student::validString( string testStr )
{
   if (testStr.length() > 0 && isalpha(testStr[0]))
      return true;
   return false;
}

bool Student::validPoints( int testPoints )
{
   if (testPoints >= 0 && testPoints <= MAX_POINTS)
      return true;
   return false;
}
// end of Student method definitions  --------------

// beginning of StudentArrayUtilities method definitions -------------

// print the array with string as a title for the message box
// this is somewhat controversial - we may or may not want an I/O
// methods in this class.  we'll accept it today
void StudentArrayUtilities::printArray(string title, Student data[], int arraySize)
{
   string output = "";

   cout << title << endl;

   // build the output string from the individual Students:
   for (int k = 0; k < arraySize; k++)
      output += " " + data[k].toString();

   cout << output << endl;
}

void StudentArrayUtilities::arraySort(Student array[], int arraySize)
{
   for (int k = 0; k < arraySize; k++)
      // compare with method def to see where inner loop stops
         if (!floatLargestToTop(array, arraySize-1-k))
            return;
}

// returns true if a modification was made to the array
bool StudentArrayUtilities::floatLargestToTop(Student data[], int top)
{
   bool changed = false;

   // compare with client call to see where the loop stops
   for (int k =0; k < top; k++)
      if (  Student::compareTwoStudents(data[k], data[k + 1]) > 0 )
      {
         mySwap(data[k], data[k + 1]);
         changed = true;
      }
      return changed;
}

void StudentArrayUtilities::mySwap(Student &a, Student &b)
{
   Student temp("", "", 0);

   temp = a;
   a = b;
   b = temp;
}

// end of StudentArrayUtilities method definitions  --------------

/* ------------------------------ run ----------------------------

Before:
  smith, fred points: 95
  bauer, jack points: 123
  jacobs, carrie points: 195
  renquist, abe points: 148
  zz-error, trevor points: 108
  perry, fred points: 225
  loceff, fred points: 44
  stollings, pamela points: 452
  charters, rodney points: 295
  cassar, john points: 321

After:
  bauer, jack points: 123
  cassar, john points: 321
  charters, rodney points: 295
  jacobs, carrie points: 195
  loceff, fred points: 44
  perry, fred points: 225
  renquist, abe points: 148
  smith, fred points: 95
  stollings, pamela points: 452
  zz-error, trevor points: 108

Press any key to continue . . .

---------------------------------------------------------------- */
