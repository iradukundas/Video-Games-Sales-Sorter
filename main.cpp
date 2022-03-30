#include "AUList.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void calculateMeanSTDev(double& mean, double& stdev, vector<double> data) //compute mean and standard deviation for any vector of doubles
{
    double sum = 0;
	mean=0;
	stdev = 0;
	
    for(int i = 0; i <data.size(); i++) //first compute the mean of data vector
    {
        sum += data.at(i);
    }

    mean = sum/data.size();

    for(int i = 0; i < data.size(); i++) //now compute the standard deviation of the vector
        stdev += pow(data.at(i) - mean, 2);

    stdev= sqrt(stdev / data.size());
}


AUList csvtoAUList(string csvfile) 
{ //convert a csv file to a list structure
    AUList retCCList;
	ifstream ReadFile(csvfile); //open the csv file for reading
    string line, curvalue;
	getline(ReadFile, line); //throw away the first line (column names)

    while (getline(ReadFile,line)) 
    {        
        stringstream ss(line); //turn the line into a string-stream
        int fielditer=0;
        Sales_Data newrec;
        
		while(getline(ss, curvalue, ','))
		{ //Separate each variable per sample from the comma separator
            switch (fielditer) { //We need to explicitly convert values to the appropriate type (stoi=integer, stod=double)

				case 0: newrec.Platform_count = stoi(curvalue); break;
            	case 1: newrec.Platform = curvalue; break;
                case 2: newrec.Name = curvalue; break;
            	case 3: newrec.NA_Sales = stod(curvalue); break;
            	case 4: newrec.EU_Sales = stod(curvalue); break;
            	
			}
            fielditer++;
        }
        retCCList.PutItem(newrec);
    }
    return retCCList;
}

int main(int argc, char** argv) 
{
	AUList AverageSales=csvtoAUList("vgsales_data.csv");
	AverageSales.PrintList(); //printing data
	cout << "Average sales for platform from 1980 to 2016";
	cout << "/n";
	
	for (int Plat_it = 1; Plat_it <= 21; Plat_it ++) { //Iterate through values

        vector<double> plat_na (0);
        vector<double> plat_eu (0);
        
        AverageSales.ResetList();
        while (AverageSales.HasNextItem())
        {
            Sales_Data curitem = AverageSales.GetNextItem();

            if (curitem.Platform_count == Plat_it ) //only store variables in vector whose target variable aligns to current class
            { 
                plat_na.push_back(curitem.NA_Sales);
                plat_eu.push_back(curitem.EU_Sales);
            }
        }

        //mean and standard deviations for each variable
        double mean_na; double stdev_na;
        double mean_eu; double stdev_eu;

        calculateMeanSTDev(mean_na,stdev_na,plat_na);
        calculateMeanSTDev(mean_eu,stdev_eu,plat_eu);
		
		//outputing values
        cout<<"\nFor Platform_count: " << Plat_it << " [The NA_Sales Mean is: " << mean_na << " and NA_Sales STDev is: " << stdev_na << "]"<< endl;
        cout<<"For Platform_count: " << Plat_it << " [The EU_Sales Mean is: " << mean_eu << " and Eu_Sales STDevis : " << stdev_eu << "]"<< endl;

    }
    
    system("pause");
    return 0;

}
    
