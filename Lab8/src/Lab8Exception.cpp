/*
 * Lab8Exception.cpp
 *
 *  Created on: Apr 19, 2018
 *      Author: oobnvc
 */

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <limits.h>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>


using namespace std;

class Signal
{
private:
	double Min_Num;
	double Avg;
	vector<double> data;

public:
	double length;
	double Max_Num;
	vector<double> updateddata;
	void offset(double x);
	void scale(double x);
	void center();
	void normalize()throw(string);
	void statistics();
	void menu();
	void Sig_info();
	void Save_file(int n);
	void getAverage(void);
	void getMax(void);
	void setMax( double jim ) { Max_Num = jim; }
	/*int GETMax()
	{
		return Max_Num;
	}*/
	//Operators (Member)
	void operator+(double x);
	void operator*(double rhs_factor);

	//Constructors
	Signal():Signal(1){}; // default file
	Signal(int n); // when given just a number it opens the file
	Signal(string filename);

	// Destructor
	~Signal(){};

};

Signal *operator+(const Signal &lhs, const Signal &rhs);

void Signal::menu()
{
	int opt;
	cout << "Welcome to a complicated life"<< endl;
	do
	{
		cout << "Here is a list of things you can do, Please pick your choices appropriately"<< endl;
		cout << "\n1) Offset " << endl;
		cout << "2) Scale" << endl;
		cout << "3) Center" << endl;
		cout << "4) Normalize" << endl;
		cout << "5) Statistics" << endl;
		cout << "6) Print Signal" << endl;
		cout << "7) Save Signal" << endl;
		cout << "8) New Stuff with Operator" << endl;
		cout << "9) Exit" << endl;

		cout << "Select an option: " <<endl;
		cin >> opt;

		switch(opt)
		{
		case 1:
		{
			cout << "\nEnter the offset value: ";
			double val;
			cin >> val;
			offset(val);
			break;
		}
		case 2:
		{
			cout << "\nEnter the scale value: ";
			try
			{
				double val;
				cin >> val;
				scale(val);
			}
			catch(...)
			{
				cerr<<" You can't scale by using a 0 " << endl;
			}
			break;
		}
		case 3:
		{
			center();
			break;
		}
		case 4:
		{
			normalize();
			break;
		}
		case 5:
		{
			statistics();
			break;
		}
		case 6:
		{
			Sig_info();
			break;
		}
		case 7:
		{
			cout << "Enter a filenumber: ";
			double num;
			cin >> num;
			Save_file(num);
			//delete num;
			break;
		}
		case 8:
		{
			// Demonstrate the non-member overloaded additio
			try
			{
				cout << "\nEnter a file number value: ";
				double val, val2;
				cin >> val;
				cout << "\nEnter a file number value: ";
				cin >> val2;
				Signal obj1 = Signal(val);
				Signal obj2 = Signal(val2);
				Signal *obj3;
				obj3 = obj1 + obj2;
			}
			catch(...)
			{
				cerr <<"Objects are not the same Lengths\n";
			}
			break;
		}
		case 9:
		{
			exit(EXIT_SUCCESS);
		}
		default:
		{
			cout << "Invalid option" << endl;
			break;
		}
		}
	}
	while(opt <= 8);
}

void Signal::offset(double x)
{
	/*for(int i = 0; i<length; i++)
	{
		cout << "Offset["<< i << "] -> "<< updateddata[i] << " by " << x << endl;
		updateddata[i] = updateddata[i] + x;
	}*/
	this->operator +(x);
	getAverage();
	getMax();
}

void Signal::scale(double x)
{

	if(x == 0)
	{
		throw "length of Objects are not Equal";
	}
	else
	{
		this->operator*(x);
	}
	getAverage();
	getMax();
}

void Signal::getAverage()
{
	Avg = 0;
	for(int i = 0; i<length; i++)
	{
		Avg = Avg + updateddata[i];
	}
	Avg = (Avg/(length));
}

void Signal::getMax()
{
	Max_Num = 0;
	for(int i = 0; i<length; i++)
	{
		if(updateddata[i] > Max_Num)//*(data+i) is an actual value in the vector/ or array
		{
			Max_Num = updateddata[i];
		}
	}
	//cout<<"Maxvalue is: "<< max << endl;
}

void Signal::center()
{
	getAverage();
	operator+(-Avg);
	getAverage();
	getMax();
}

void Signal::statistics()
{
	cout<<"Maxvalue is: "<< Max_Num<< endl;
	cout <<"Average is: " << Avg << endl;
}

void Signal::normalize() throw(string)
								{
	if(length == 0)
	{
		throw "Cannot Normalize because your vector is empty";
	}
	getMax();
	operator*(1/Max_Num);
	getAverage();
	getMax();
								}

void Signal::Sig_info()
{
	Min_Num = Max_Num;
	for(int i = 0; i<length; i++)
	{
		if( updateddata[i] < Min_Num )//*(data+i) is an actual value in the vector/ or array
		{
			Min_Num = updateddata[i];
		}
	}
	int i = 0;
	while ( i < length )
	{
		cout << "DATA[" << i << "] -> " << data[i] << " --> " << updateddata[i] << endl;
		i++;
	}

	cout << "\nSignal length: " << length << endl;
	cout << "Maximum val:" << Max_Num << endl;
	cout << "Minimum val:" << Min_Num << endl;
	cout << "Average val:" << Avg << endl;

}

void Signal::Save_file(int n)
{
	ostringstream fileNumStream;
	fileNumStream << setw(2) << setfill('0') << to_string(n); /// this is so that we could open files such as 10/11

	ofstream myfile ( "Raw_data_" + fileNumStream.str() + ".txt" );

	if( !myfile.is_open() )
	{
		throw "Could not open file ";
		return;
	}

	myfile << length << " " << Max_Num << endl;

	for( int i = 0; i < length; i++ )
	{
		myfile << updateddata[i] << endl;
	}

	myfile.close();

}

Signal::Signal(int n) /// It reads in my file.
{
	Avg = 0;
	Max_Num = 0;
	Min_Num = 0;

	ostringstream fileNumStream;
	fileNumStream << setw(2) << setfill('0') << to_string(n);

	ifstream myfile ( "Raw_data_" + fileNumStream.str() + ".txt" );

	int i = 0;
	length = 0;

	myfile.is_open();
	try
	{
		if(!myfile.is_open())
		{
			throw 1;
		}
	}
	catch(int c)
	{
		cout << "ERROR! File could not be opened." << endl;
		throw;
	}
	myfile >> length >> Max_Num;
	myfile.ignore( 1,'\n' );
	cout << "Length: " << length << " | Max: " << Max_Num << endl;

	string line;
	while ( i < length )
	{
		//myfile >> test[i];
		getline( myfile, line );
		data.push_back( atof( line.c_str() ) );
		updateddata.push_back( data[i] );
		//cout << "Read the data for " << i << " : " << data[i] << endl;
		i++;
	}
	myfile.close();
}

Signal::Signal(string filename)
{
	ifstream myfile(filename);
	int i = 0;
	length = 0;
	try
	{
		if(!myfile.is_open())
		{
			throw 1;
		}
	}
	catch(int c)
	{
		cout << "ERROR! File could not be opened." << endl;
		throw;
	}
	cout << "I opened a file using a filename! I so cool!" << endl;
	myfile >> length >> Max_Num;
	myfile.ignore( 1,'\n' );
	cout << "Length: " << length << " | Max: " << Max_Num << endl;

	string line;
	while ( i < length )
	{
		//myfile >> test[i];
		getline( myfile, line );
		data.push_back( atof( line.c_str() ) );
		updateddata.push_back( data[i] );
		//cout << "Read the data for " << i << " : " << data[i] << endl;
		i++;
	}
	myfile.close();

	Avg = 0;
	Max_Num = 0;
	Min_Num = 0;
}

//Operator
void Signal::operator+(double x)

{
	int i = 0;
	for(i = 0; i < length; i++)
	{
		updateddata[i] += x;
		cout << "Data[" << i << "] ->"<< updateddata[i] << endl;
	}

}
class Exception
{
private:

public:
	void message()
	{
		cout << "\nERROR! You messed up big time\n The length of the files are not the same." << endl;
	}
};

void Signal::operator*(double rhs_factor)
{
	for(int i = 0; i < length; i++)
	{
		updateddata[i] *= rhs_factor;
		cout << "Data[" << i << "] ->"<< updateddata[i] << endl;
	}
}

// -------- Operators can be Non-member functions -------------------
Signal *operator+(const Signal &lhs, const Signal &rhs)
{
	Signal *sum = new Signal;

	if(lhs.length == 0 || rhs.length == 0)
	{
		throw "Your Vectors are Empty";
	}
	if(lhs.length != rhs.length)
	{
		throw Exception();
	}
	else
	{
		sum->length = lhs.length;
		for(int i = 0; i < sum->length; i++)
		{
			// use push_back to grow vector
			sum->updateddata.push_back(lhs.updateddata[i]);
			sum->updateddata[i] += rhs.updateddata[i];
		}
		//cerr<<"Average of both object ="<< sum->getAverage()<<endl;
	}

	//sum->setMax( 3220 );

	//cout << "LEFT " << lhs.Max_Num << " | Right " << rhs.Max_Num << " | SUM: " << sum->Max_Num << endl;

	if( lhs.Max_Num > rhs.Max_Num )
	{
		try
		{
			sum->Max_Num = lhs.Max_Num;
		}
		catch(char n)
		{
			cerr <<"MAxIMUM number is supposed to be a number not a char\n";
		}
	}
	else
	{
		sum->Max_Num = rhs.Max_Num;
	}
	cout << sum->Max_Num << " is the MAX NUM" << endl;

	return sum;
}

int main(int argc, char*argv[])
{
	int filenum;
	string filename;
	if(argc == 1)
	{
		Signal input;
		input.menu();
		delete &input;
	}
	else if (argc >= 3)
	{
		for( int i = 1; i <= argc; i++ )
		{
			if((argv[i][0] == '-') && (argv[i][1] == 'n'))
			{
				filenum = atoi(argv[2]);
				cout << "File value: " << filenum << endl;
				try
				{
					Signal input( filenum );
					input.menu();
					delete &input;
				}
				catch(...)
				{
					cout << "\nERROR!! Whatever you are trying to do is Out_Of_Range" << endl;
				}
				break;
			}
			else if ((argv[i][0] == '-') && (argv[i][1] == 'f'))
			{
				try
				{
					filename = argv[2];
					cout << "Filename: " << filename << endl;
					Signal input(filename);
					input.menu();
					delete &input;
				}
				catch(char c)
				{
					cerr <<"ERROR!! Invalid Filenumber"<< endl;
					throw;
				}
				catch(...)
				{
					cout << "Exception occurred";
				}
			}
			break;
		}
	}
	else
	{
		cerr << "Error! Wrong number of argument "<< endl;
	}
	return 0;

}



