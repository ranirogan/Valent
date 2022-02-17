#ifndef MAKEUP_H
#define MAKEUP_H

#include <string>
#include <vector>

using namespace std;

class MakeUp{
    public:
        double cr; //chromium
        double ni; //nickle
        double mo; //molybdenum
        double c; //carbon
        double mn; //manganese
        double p; //phosphorus
        double s; //sulfur
        double si; //silicon
        double n; //nitrogen
        double fe; //iron
        double w; //weight

        MakeUp(double chromium, double nickle, double molybdenum, double carbon, double manganese, 
            double phosphorus, double sulfur, double silicon, double nitrogen, double iron, double weight = 100) : 
            cr(chromium), ni(nickle), mo(molybdenum), c(carbon), mn(manganese), p(phosphorus), 
            s(sulfur), si(silicon), n(nitrogen), fe(iron), w(weight){} 

        vector<double> calculate(MakeUp* goal);
        vector<double> newWeight(vector<double> weights);
        vector<double> newPercent(vector<double> weights);
};

/**
 * @brief Calculates the weight needed to add to each element. this assumes no more iron will
 *  need to be added (ie, not increasing the purity of iron)
 *  percentage increase = (current iron weight / goal iron %)
 *  new total weight = percentage increase * (current weight / goal weight standard)
 *  new element weight = total weight * element % 
 *  element to add = new element weight - current element weight
 * 
 * @param goal is a pointer to a MakeUp object that has the goal specs
 * @return vector<double> is a vector of the weights to add for each element
 */
vector<double> MakeUp::calculate(MakeUp* goal){
    double goal_fe_per = goal->fe;
    double cur_fe_weight = this->fe * 100;
    double incr = cur_fe_weight / goal_fe_per;
    incr = incr * (w / goal->w);
    
    vector<double> weights (11);
    weights[0] = incr * goal->cr - (cr * w);
    weights[1] = incr * goal->ni - (ni * w);
    weights[2] = incr * goal->mo - (mo * w);
    weights[3] = incr * goal->c - (c * w);
    weights[4] = incr * goal->mn - (mn * w);
    weights[5] = incr * goal->p - (p * w);
    weights[6] = incr * goal->s - (s * w);
    weights[7] = incr * goal->si - (si * w);
    weights[8] = incr * goal->n - (n * w);
    weights[9] = incr * goal->fe - (fe * w);
    weights[10] = incr; // new total weight

    //round near zero numbers to 0
    for(int i = 0; i < 11; i++){
        if(weights[i] < 0.000001)
            weights[i] = 0;
    }
    return weights;
}

/**
 * @brief Creates a vector that calculates the total weight of each element by
 *  readding the current element weight to the weight to add
 *  total weight = weight to add + current weight * element %
 * 
 * @param weights are the weights of each element that need to be added to the steel
 * @return vector<double> is a vector of the total weights of each element
 */
vector<double> MakeUp::newWeight(vector<double> weights){
    double total = weights[10];

    vector<double> totWeight (11);
    totWeight[0] = (weights[0] + cr * w);
    totWeight[1] = (weights[1] + ni * w); 
    totWeight[2] = (weights[2] + mo * w); 
    totWeight[3] = (weights[3] + c * w); 
    totWeight[4] = (weights[4] + mn * w); 
    totWeight[5] = (weights[5] + p * w); 
    totWeight[6] = (weights[6] + s * w); 
    totWeight[7] = (weights[7] + si * w); 
    totWeight[8] = (weights[8] + n * w); 
    totWeight[9] = (weights[9] + fe * w); 
    totWeight[10] = total;

    //round near zero numbers to 0
    for(int i = 0; i < 11; i++){
        if(totWeight[i] < 0.000001)
            totWeight[i] = 0;
    }

    return totWeight; 
}

/**
 * @brief Recalculates the percentage of each element based on the new weight of each
 *  element and the new total weight
 *  element % = new element weight / new total weight
 * 
 * @param weights are the new total weights for each element
 * @return vector<double> is a vector of the new % of each element
 */
vector<double> MakeUp::newPercent(vector<double> weights){
    double total = weights[10];

    vector<double> percent (10);
    percent[0] = (weights[0]) / total;
    percent[1] = (weights[1]) / total; 
    percent[2] = (weights[2]) / total; 
    percent[3] = (weights[3]) / total; 
    percent[4] = (weights[4]) / total; 
    percent[5] = (weights[5]) / total; 
    percent[6] = (weights[6]) / total; 
    percent[7] = (weights[7]) / total; 
    percent[8] = (weights[8]) / total; 
    percent[9] = (weights[9]) / total;

    return percent; 
}
#endif