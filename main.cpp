#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#include "defns.h"
#include "utilities.cpp"
#include "heap.cpp"

void findMax(string x, int y, int size, SOC* arr, int year);
void findRatio(int year1, int year2, int size, earnings* arr);
void readQueries(SOC* arr, int SOCsize, int year, earnings* arr2, int earningsSize);
void print_with_commas( int n );

int main(int argc, char* argv[]){
    int year = stoi(argv[1]);
    int SOCsize;
    int earningsSize;
    SOC *socObjects = makeSOCobjects(argc, argv, &SOCsize);
    //cout << "makeSOCobjects completed \n";
    earnings *earningsObj = makeEarningsObjs(&earningsSize);
    //cout << "makeEarningsObjs completed \n";
    readQueries(socObjects, SOCsize, year, earningsObj, earningsSize);
    //cout << SOCsize << "\n";
    //cout << earningsSize;
    return 0;
}


void readQueries(SOC* arr, int SOCsize, int year, earnings* arr2, int earningsSize)
{
	string linestring;
	//istream rtrn = getline(std::cin, linestring);
	//cout << "rtrn=" << rtrn << "\n";
    int queryCount = 0;
	while(getline(std::cin, linestring)){
		//cout << "linestring1=" + linestring << "=linestring.length" << linestring.length() << "\n";
		int ifind=0;
		if (ifind != -1 )
		{
			//cout << "std::string::npos=" << std::string::npos << "\n";
			ifind = linestring.find("find");
			//cout << "ifind1=" << ifind << "\n";
			if (ifind == -1 ) {
				//cout << "ifind2=" << ifind << "\n";
			    //exit(0);
			}
			int imax = linestring.find("max",ifind);
			int iratio = linestring.find("ratio",ifind);

			if ( imax != std::string::npos )
			{
				string worker;
				int itotal = linestring.find("total",imax);
				int imale = linestring.find("male",imax);
				int ifemale = linestring.find("female",imax);
				int iworker = itotal;
				if ( itotal != std::string::npos )
				{
					iworker = itotal;
					worker = linestring.substr(itotal, 5);
				}
				if ( imale != std::string::npos )
				{
					iworker = imale;
					worker = linestring.substr(imale, 4);
				}
				if ( ifemale != std::string::npos )
				{
					iworker = ifemale;
					worker = linestring.substr(ifemale, 6);
				}
				if ( iworker != std::string::npos )
				{
                    if(queryCount > 0){
                    cout << "\n";
                    }
					string nstring = linestring.substr(iworker+worker.length());
					//cout << "ifind=" << ifind << "imax=" << imax << "-itotal=" << itotal << "-imale="+imale << "nstring=" << nstring << "\n";
					int n = std::stoi(nstring);
                    cout << "Query: find max " << worker << " " << n << "\n\n";
                    findMax(worker, n, SOCsize, arr, year);
                    queryCount++;
				}
				//cout << "ifind=" << ifind << "imax=" << imax << "-itotal=" << itotal << "-imale="+imale << "\n";
			}
			if ( iratio != std::string::npos )
			{
				int istartendyear = linestring.find(" ",iratio+5+4);
				if ( istartendyear == -1 )
				{
					istartendyear = linestring.find("\t",iratio+5+4);
				}
				if ( istartendyear != -1 )
				{
					string strstartYear = linestring.substr(iratio+5,(istartendyear-(iratio+5)));
					string strendYear = linestring.substr(istartendyear);
					//cout << "ifind=" << ifind << "iratio=" << iratio << "-strstartYear=" << strstartYear << "-strendYear="+strendYear << "\n";
					if ( strstartYear.length() > 0 && strendYear.length() > 0 )
					{
                        if(queryCount > 0){
                        cout << "\n";
                        }
						int startyear = std::stoi(strstartYear);
						int endYear = std::stoi(strendYear);
                        cout << "Query: find ratio " << startyear << " " << endYear << "\n\n";
                        findRatio(startyear, endYear, earningsSize, arr2);
						//cout << "startyear=" << startyear << "-endYear=" << endYear << "\n";
                        queryCount++;
					}
				}
			}
		}
			//cout << "ifind=" << "\n";

	    }
		linestring = "";
	//cout << "linestring2=" + linestring + "\n";
}

void findMax(string x, int y, int size, SOC* arr, int year){

	int tempSize = size;
buildHeap(arr, size, x);



cout << "Top " <<  y << " occupations in " << year << " for " << x << " workers:\n";

for(int i=0; i< y; i++){

SOC maxOccupation = deleteMax(arr, &tempSize, x);

cout << "\t" << maxOccupation.occupation << ": ";
print_with_commas(getNumberOfWorkers(maxOccupation,x));
cout << "\n";

}

}


void print_with_commas( int n )
{
    const unsigned int THOUSAND = 1000 ;

    if( n < THOUSAND )
    {
        std::cout << n ;
    }
    else
    {
        int remainder = n % THOUSAND ;
        string strremainder = std::to_string(remainder);
        if ( strremainder.length() == 2 )
        {
        	strremainder = "0" + strremainder;
        }
        else if ( strremainder.length() == 1 )
        {
        	strremainder = "00" + strremainder;
        }
        else if ( strremainder.length() == 0 )
        {
        	strremainder = "000";
        }

        print_with_commas( n / THOUSAND ) ;
        std::cout << ',' << strremainder ;
    }
}



void findRatio(int year1, int year2, int size, earnings* arr){

cout << "The female-to-male earnings ratio for " << year1 << "-" << year2 << ":\n";

for(int p = year1; p < year2 + 1; p++){

for(int j = 0; j < size; j++){


if(arr[j].year == p){

cout << "\t" << arr[j].year << ": ";

//cout << "arr[j].female_earnings=" << arr[j].female_earnings << "-arr[j].male_earnings" << arr[j].male_earnings << "\n";
float ratio = ((int)(arr[j].female_earnings * 1000.0/ arr[j].male_earnings)) / 10.0;
printf("%0.1f%%\n", ratio);

//std::cout.precision(1);

//std::cout << ratio << "%\n";



}

}

}


}





//declare variables outside
//change max method by swap
//go thru implementations
//take input queries
//make methods