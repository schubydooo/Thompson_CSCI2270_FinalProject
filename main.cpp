#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Graph.h"

using namespace std;

//main method
int main(int argc, char* argv[])
{
    //get file stuff
    ifstream graphFile;
    graphFile.open("FinalProjectCities.txt");
    string fileline;
    Graph cg;
    bool firstLine = false;
    bool firstCol = true;
    vector<string> cityNames;
    vector<car*> cars;

    //reading the file and building the graph
    while(getline(graphFile,fileline)){
        if(fileline == ""){
            break;
        }

        string partline;
        istringstream s(fileline);
        //if the first line has not been read yet
        //ADDING THE VERTICES
        if(!firstLine){
            while(getline(s,partline,',')){
                if(!firstCol){
                    cg.addVertex(partline);
                    //also add the name to a vector
                    cityNames.push_back(partline);
                }else{
                    firstCol = false;
                }
            }
            firstLine = true;
        }

        //ADDING THE EDGES
        //going through the other lines
        int col = 0; //what "column" you are on - really what ending city you are on
        string name; //what "row" you are on - really what starting city you are on
        while(getline(s,partline,',')){
            if(col == 0){
                name = partline;
            }else{
                int dist = stoi(partline);
                if(dist != -1 && dist != 0){
                    cg.addEdge(name,cityNames[col-1],dist);
                }
            }
            col++;
        }

    }

    //SETTING THE CHARGE
    //importing a separate file that just has names and 1 or 0
    //1 if the city has a charging station, 0 if not
    ifstream chargeFile;
    chargeFile.open("SuperChargerCities.txt");
    while(getline(chargeFile,fileline)){
        string name1;
        string sCharge;
        int charge;
        stringstream inLine(fileline);
        getline(inLine,name1,',');
        getline(inLine,sCharge,',');
        charge = stoi(sCharge);

        if(charge == 1){
            cg.setCharge(name1,true);
        }else{
            cg.setCharge(name1,false);
        }
    }

    //TAKING IN CAR INFO
    //makes a vector of car pointers, with the cars' names and battery ranges
    ifstream carFile;
    carFile.open("ElectricVehicleRanges.txt");
    while(getline(carFile,fileline)){
        if(fileline == ""){
            break;
        }
        string name2; //name of car
        string sRange; //mile range of car in string
        int range; //mile range of car in int
        stringstream inLine(fileline);
        getline(inLine,name2,',');
        getline(inLine,sRange,',');
        range = stoi(sRange);
        car* temp = new car(name2,range);
        cars.push_back(temp);
    }

    int userInput;
    while(userInput != 5){
        cout<<"======Main Menu====="<<endl<<"1. Plan a trip"<<endl<<"2. Print city choices"<<endl<<"3. Visit cities on a time crunch"<<endl<<"4. Print graph"
        <<endl<<"5. Quit"<<endl;
        cin>>userInput;

        if(userInput==1){
            //plan a trip
            string sChoice;
            int choice;
            cout<<"Type the number of your car:"<<endl;
            for(int i=0;i<cars.size();i++){
                cout<<i+1<<". "<<cars[i]->model<<endl;
            }
            cin.ignore(1,'\n');
            getline(cin,sChoice);
            choice = stoi(sChoice);
            while(choice < 1 || choice > 10)
            {
                cout << "Please enter a number between 1 and 10" << endl;
                getline(cin,sChoice);
                choice = stoi(sChoice);
            }
            string startCity;
            string endCity;
            cout<<"Starting City: ";
            getline(cin,startCity);
            cout<<"Ending City: ";
            getline(cin,endCity);
            cg.setBatteryRange(cars[choice-1]->batRange);
            cg.planTrip(startCity,endCity);
            /*
            if((choice) > 0 && (choice) < 11)
			{

			}
			else
				cout<<"Sorry, the number you typed is invalid."<<endl;
            */
        }else if(userInput==2){
            //print city choices
            for(int i=0;i<cityNames.size();i++){
                cout<<cityNames[i]<<endl;
            }
        }
        else if(userInput == 3)
        {
            string startCity;
            string time;
            cout << "Okay, so you don't have too long to drive, got it!" << endl;
            cout << "Please enter how many hours you have to travel: " << endl;
            cin.ignore(1, '\n');
            getline(cin,time);
            int timeInt = stoi(time);
            cout << "Where would you like to start your trip: " << endl;
            getline(cin, startCity);
            cg.citiesWithinReach(startCity, timeInt);
        }
        else if(userInput == 4){
            //print graph
            cg.displayEdges();
        }else if(userInput == 5){
            cout << "Goodbye!" << endl;
        }
        else
        {
            //unless they do not type 1-6
            cout<<"Enter a number between 1 and 6 only."<<endl;
        }

    }
    return 0;
}
