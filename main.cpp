#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Graph.h"

using namespace std;


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

    //reading the file
    //BUILDING THE GRAPH
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
    //graphFile.close();

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
    //chargeFile.close();

    /*need arrays for each car maker's model choices - print these out depending on the user's choice
      they will be arrays of car structs, with the model name and battery range*/

    int userInput;
    while(userInput != 4){
        cout<<"======Main Menu====="<<endl<<"1. Plan a trip"<<endl<<"2. Print city choices"<<endl<<"3. Print graph"
        <<endl<<"4. Quit"<<endl;
        cin>>userInput;

        if(userInput==1){
            //plan a trip
            cout<<"Who is the maker of your car? (enter just the number of your choice)"<<endl;
            /*ask for car maker --> get model choices --> ask for model --> get battery range
              ask for starting and ending cities
              call method*/
        }else if(userInput==2){
            //print city choices
            for(int i=0;i<cityNames.size();i++){
                cout<<cityNames[i]<<endl;
            }
        }else if(userInput==3){
            //print graph
            cg.displayEdges();
        }else if(userInput == 4){

        }else{
            //unless they do not type 1-6
            cout<<"Enter a number between 1 and 6 only."<<endl;
        }

    }
    cout<<"Goodbye!"<<endl;
    return 0;
}
