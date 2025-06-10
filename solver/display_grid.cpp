#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

void print_board(string dots){
    int i = 0; // counter for the dots
    for(int y = 0; y < 13; y++){
        for(int x = 0; x < 13; x++){
            if(y == 0 || y == 4 || y == 8 || y == 12){
                if(x == 0 || x == 4 || x == 8 || x == 12){
                    cout << "+";
                } else {
                    cout << "-";
                }
            } else {
                if(x == 0 || x == 4 || x == 8 || x == 12){
                    cout << "|";
                } else {
                    if(dots[i] == '.'){
                        cout << " ";
                    } else {
                        cout << dots[i];
                    }
                    i++;
                }
            }
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    cout << "You have entered " << argc
         << " arguments:" << endl;
    if (argc != 4) {
        cout << "Needed 4 arguments, gave " << argc << "." << endl;
        cout << "Usage: " << argv[0] << " <category> <difficulty> <index>" << endl;
        return 0;
    }



    // Using a while loop to 
    // iterate through arguments
    int i = 0;
    while (i < argc) {
        cout << "Argument " << i + 1 
             << ": " << argv[i]
             << endl;
        i++;
    }

    // get the puzzle from the arguments
    // they are in a json format, example as follows
    /*
        {
        "puzzles": [
            {
            "puzzle": "..5..47.....37...21..2...6.3...9......64......2....1.9.14....3...284..5.7....1...",
            "solution": "285164793469378512173259468341795286896412375527683149914526837632847951758931624"
            },
    */

    string category = argv[1];
    string difficulty = argv[2];
    int index = stoi(argv[3]);
    string filename = "../library/puzzles/v1/" + category + "/" + difficulty + ".json";

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open file: " << filename << endl;
        return 1;
    }

    json puzzles;
    // attempt to open the file and read the puzzles
    try
    {
        file >> puzzles;
    }
    catch(json::parse_error& e)
    {
        cerr << "JSON parse error: " << e.what() << '\n';
        return 1;
    }
    
    if(index < 0 || index >= puzzles["puzzles"].size()) {
        cout << "Index out of bounds. There are only " << puzzles["puzzles"].size() << " puzzles in this category and difficulty." << endl;
        return 1;
    }

    string puzzle = puzzles["puzzles"][index]["puzzle"];
    string solution = puzzles["puzzles"][index]["solution"];
    cout << "Displaying puzzle at index " << index << " from category " << category << " and difficulty " << difficulty << ":" << endl;

    print_board(puzzle);

    return 0;
}