#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include <ctime>
#include "makeup.h"

using namespace std;

MakeUp* readFile(string fileName);
void printResults(vector<double> weights, vector<double> totWeights, vector<double> percents, 
    MakeUp* current, MakeUp* goal, string fileName);

int main(int argc, char** argv){ 
    if(argc != 4){
        cout << "Missing/incorrect args" << endl;
        return 0;
    }
    cout << "Reading current specs from: " << argv[1] << endl;
    cout << "Reading goal specs from: " << argv[2] << endl;

    // read specs from file
    MakeUp* current = readFile(argv[1]);
    MakeUp* goal = readFile(argv[2]);
    if(current == nullptr || goal == nullptr)
        return 0;

    // calculate needed weight increase, total weight, new % of each elem
    vector<double> weights = current->calculate(goal);
    vector<double> totWeights = current->newWeight(weights);
    vector<double> percents = current->newPercent(totWeights);

    // print to out file
    printResults(weights, totWeights, percents, current, goal, argv[3]);
    cout << "Report printed to: " << argv[3] << endl;

    return 0;
} 

/**
 * @brief Reads elemental makeup & weight from text file and returns a pointer to a
 *  MakeUp object containing that information
 * 
 * @param fileName is the name of the file to read from
 * @return MakeUp* is a pointer to an object containing the elemental makeup and weight of the steel
 */
MakeUp* readFile(string fileName){
    ifstream inputFile(fileName);
    // if can't open, return nullptr
    if(!inputFile.is_open()){
        cout << "Error in input file" << endl;
        return nullptr;
    }

    // read file and add elements into an array
    string line;
    double data [11];
    int index = 0;
    while(!inputFile.eof()){
        getline(inputFile, line);
        // element % is after space
        string per = line.substr(line.find(' ') + 1);
        data[index] = stod(per);
        index++;
    }

    // return new MakeUp pointer
    MakeUp* curr = new MakeUp(data[0], data[1], data[2], data[3], 
       data[4], data[5], data[6], data[7], data[8], data[9], data[10]);
    return curr;
}

/**
 * @brief Prints the element, start %, goal %, current weight, weight to add, new weight, new %
 * 
 * @param weights are the weights of each element needed to add
 * @param totWeights are the total weights of each element per the calculation
 * @param percents are the new % of each element based on the new weight
 * @param current is a pointer to a MakeUp object for the current specs
 * @param goal is a pointer to a MakeUp object for the goal specs
 * @param fileName is the file to write the report to
 * @param maxLoad is the maximum weight limit
 */
void printResults(vector<double> weights, vector<double> totWeights, vector<double> percents, 
MakeUp* current, MakeUp* goal, string fileName){
    ofstream out;
    out.open(fileName);
    if(!out.is_open())
        cout << "Error opening report file." << endl;

    //round near zero weight to add to 0 
    double weightToAdd = weights[10] - current->w;
    if(weightToAdd < 0.000001)
        weightToAdd = 0;

    time_t now = time(0);
    char* dt = ctime(&now);
    out << fixed << setprecision(4);
    out << "Steel Composition Report " << dt << endl;
    out << "|" << setw(11) << "Element|" << setw(14) << "Start percent|" << setw(13) << "Goal percent|" 
        << setw(15) <<  "Current Weight|" << setw(15) << "Weight to add|" << setw(14) << "Total Weight|" << setw(16) 
        << "New Percentage|" << endl;
    out << "---------------------------------------------------------------------------------------------------" << endl;
    out << "|" << setw(11) << "Chromium|"  << setw(13) << current->cr << "|" << setw(12) << goal->cr << "|" 
        << setw(14) <<  current->w * current->cr << "|" << setw(14) << weights[0] << "|" << setw(13) << totWeights[0] 
        << "|" << setw(15) << percents[0] << "|" << endl;
    out << "|" << setw(11) << "Nickle|" << setw(13) << current->ni << "|" << setw(12) << goal->ni << "|" 
        << setw(14) <<  current->w * current->ni << "|" << setw(14) << weights[1] << "|" << setw(13) << totWeights[1] 
        << "|" << setw(15) << percents[1] << "|" << endl;
    out << "|" << setw(11) << "Molybdenum|" << setw(13) << current->mo << "|" << setw(12) << goal->mo << "|" 
        << setw(14) <<  current->w * current->mo << "|" << setw(14) << weights[2] << "|" << setw(13) << totWeights[2] 
        << "|" << setw(15) << percents[2] << "|" << endl;
    out << "|" << setw(11) << "Carbon|" << setw(13) << current->c << "|" << setw(12) << goal->c << "|" 
        << setw(14) <<  current->w * current->c << "|" << setw(14) << weights[3] << "|" << setw(13) << totWeights[3] 
        << "|" << setw(15) << percents[3] << "|" << endl;
    out << "|" << setw(11) << "Manganese|" << setw(13) << current->mn << "|" << setw(12) << goal->mn << "|" 
        << setw(14) <<  current->w * current->mn << "|" << setw(14) << weights[4] << "|" << setw(13) << totWeights[4] 
        << "|" << setw(15) << percents[4] << "|" << endl;
    out << "|" << setw(11) << "Phosphorus|" << setw(13) << current->p << "|" << setw(12) << goal->p << "|" 
        << setw(14) <<  current->w * current->p << "|" << setw(14) << weights[5] << "|" << setw(13) << totWeights[5] 
        << "|" << setw(15) << percents[5] << "|" << endl;
    out << "|" << setw(11) << "Sulfur|" << setw(13) << current->s << "|" << setw(12) << goal->s << "|" 
        << setw(14) <<  current->w * current->s << "|" << setw(14) << weights[6] << "|" << setw(13) << totWeights[6] 
        << "|" << setw(15) << percents[6] << "|" << endl;
    out << "|" << setw(11) << "Silicon|" << setw(13) << current->si << "|" << setw(12) << goal->si << "|" 
        << setw(14) <<  current->w * current->si << "|" << setw(14) << weights[7] << "|" << setw(13) << totWeights[7] 
        << "|" << setw(15) << percents[7] << "|" << endl;
    out << "|" << setw(11) << "Nitrogen|" << setw(13) << current->n << "|" << setw(12) << goal->n << "|" 
        << setw(14) <<  current->w * current->n << "|" << setw(14) << weights[8] << "|" << setw(13) << totWeights[8] 
        << "|" << setw(15) << percents[8] << "|" << endl;
    out << "|" << setw(11) << "Iron|" << setw(13) << current->fe << "|" << setw(12) << goal->fe << "|" 
        << setw(14) <<  current->w * current->fe << "|" << setw(14) << weights[9] << "|" << setw(13) << totWeights[9] 
        << "|" << setw(15) << percents[9] << "|" << endl;
    out << "---------------------------------------------------------------------------------------------------" << endl;
    out << "|" << setw(11) << "Total|" << setw(13) << "100%" << "|" << setw(12) << "100%" << "|" 
        << setw(14) <<  current->w << "|" << setw(14) << weightToAdd << "|" << setw(13) << weights[10] 
        << "|" << setw(15) << "100%" << "|" << endl;
    out<< endl;
}