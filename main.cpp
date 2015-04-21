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
    ifstream inFile;
    string filename = argv[1];
    inFile.open(filename);
    string fileline;
    Graph cg;
    bool firstLine = false;
    bool firstCol = true;
    vector<string> cityNames;

    //reading the file
    //BUILDING THE GRAPH
    while(getline(inFile,fileline)){
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

    int userInput;
    while(userInput != 6){
        cout<<"======Main Menu====="<<endl<<"1. Plan a trip"<<endl<<"2. Print city choices"<<endl<<"3. Quit"<<endl;
        cin>>userInput;

        if(userInput==1){
            //plan a trip
            /*ask for car maker --> get model choices --> ask for model --> get battery range
              ask for starting and ending cities
              call method*/
        }else if(userInput==2){
            //print city choices
        }else if(userInput==3){
            //quit
        }else{
            //unless they do not type 1-6
            cout<<"Enter a number between 1 and 6 only."<<endl;
        }

    }
    cout<<"Goodbye!"<<endl;
    return 0;
}
