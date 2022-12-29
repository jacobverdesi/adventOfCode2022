//
// Created by jverdesi on 12/25/22.
//

#include "ProboscideaVolcanium.h"

#include <string>
#include <list>
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <regex>
#include <set>
#include "../Utils/InitDay.h"

using namespace std;
#define INF 99999
class Valve {


public:
    int flowRate = -1;
    int valveNum;
    string valveChar;
    map<int, int> edgeList;
    bool isOpened = false;

    explicit Valve(string line) {
        const regex re(R"([A-Z]{2}|\d+)");

        smatch match;
        int i = 0;
        while (regex_search(line, match, re)) {
            string val = match.str();
            if (i == 0) {
                valveChar = val;
                valveNum = val[1] - 65;
                valveNum += (val[0] - 65) * 27;

            } else if (i == 1) {
                flowRate = stoi(val);
            } else {
                int tunnelNum = 0;
                tunnelNum = val[1] - 65;
                tunnelNum += (val[0] - 65) * 27;
                edgeList.emplace(tunnelNum, 1);
            }

            i++;
            line = match.suffix().str();
        }
    }

    void reduceEdge(const Valve &removeValve) {
        if (edgeList.contains(removeValve.valveNum)) {
            int distance = edgeList[removeValve.valveNum];
            for (auto &[targetValveNum, targetValveDistance]: removeValve.edgeList) {
                if (targetValveNum != valveNum) {
                    if (edgeList.contains(targetValveNum) and
                        edgeList[targetValveNum] > (distance + targetValveDistance)) {
                        edgeList[targetValveNum] = distance + targetValveDistance;
                    } else {
                        edgeList.emplace(targetValveNum, distance + targetValveDistance);
                    }
                }
            }
            edgeList.erase(removeValve.valveNum);
        }
    }

};

class ValveMap {

    map<int, Valve> valveMap;
    vector<int> valvePath;
    int currValveIdx = 0;
    int remainingTime = 30;
    vector<vector<int>> distanceMatrix;
public:

    explicit ValveMap() = default;

    void reduceValveMap() {
        for (auto it = valveMap.begin(), next_it = it; it != valveMap.end(); it = next_it) {
            ++next_it;
            if (it->second.flowRate == 0 and it->first != 0) {
                for (auto &[valveNum, valve]: valveMap) {
                    if (it->first != valveNum)
                        valve.reduceEdge(it->second);

                }
                valveMap.erase(it);
            }
        }
    }

    void makeDistanceMatrix() {
        for (auto row: valveMap) {
            vector<int> valveY;
            for (const auto &col: valveMap) {
                if (row.second.edgeList.contains(col.first)) {
                    valveY.push_back(row.second.edgeList.find(col.first)->second);
                } else {
                    valveY.push_back(INF);
                }

            }
            distanceMatrix.push_back(valveY);

        }
        int graphSize=(int)distanceMatrix.size();
        int i, j, k;
        for (k = 0; k < graphSize; k++) {
            for (i = 0; i < graphSize; i++) {
                for (j = 0; j < graphSize; j++) {
                    if (distanceMatrix[i][j] > (distanceMatrix[i][k] + distanceMatrix[k][j])
                        && (distanceMatrix[k][j] != INF
                            && distanceMatrix[i][k] != INF))
                        distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                }
            }
        }
        for (const auto &row: distanceMatrix) {
            for (auto col: row) {
                cout << col << " ";
            }
            cout << '\n';
        }
    }

    void openValve(int newValveIdx) {
        // find shortest path
        // if path is less than remaining time
        // add path/newValveIdx to valvePath
        // set currValveIdx to newValveIdx
        //
    }

    [[nodiscard]] map<int, Valve> getValveMap() const {
        return valveMap;
    }

    void emplace(const Valve &v) {
        valveMap.emplace(v.valveNum, v);
    }

    bool operator<(ValveMap &other) {
        return this->valvePath < other.valvePath;
    }

    void printPath() {
        cout << "Valve Path: ";
        for (auto valveIdx: valvePath) {
            cout << valveMap.find(valveIdx)->second.valveChar;
        }
        cout << "\n";
    }

    void printValveMap() {
        for (auto [valveNum, valve]: valveMap) {
            cout << "Valve: " << valve.valveChar << "/" << valveNum << " FlowRate: " << valve.flowRate << " EdgeList: ";
            for (auto [edge, dist]: valve.edgeList) {
                cout << "(" << edge << "/" << dist << ") ";
            }
            cout << "\n";
        }
    }

    void printEdgeList() {
        for (auto [valveNum, valve]: valveMap) {
            for (auto [edge, dist]: valve.edgeList) {
                cout << valveNum << "-(" << dist << ")>" << edge << "\n";

            }
        }
    }
};

class ProboscideaVolcanium {
    set<ValveMap> memoizedValveMap;
public:
    ValveMap initValveMap;

    explicit ProboscideaVolcanium(const list<string> &inputStringList, bool isPart2 = false) {

        for (const string &line: inputStringList) {
            Valve v = Valve(line);
            initValveMap.emplace(v);
        }
        initValveMap.reduceValveMap();
        initValveMap.printEdgeList();
        cout << "==========================\n";
        initValveMap.printValveMap();
        cout << "===============================\n";
        initValveMap.makeDistanceMatrix();
        // valveMap.valveMap.find(0)->second.visited=true;
    }


    int dfs(ValveMap valveMap) {
        int maxPressure = 0;
        vector<int> valveList;
        for (auto [valveNum, valve]: valveMap.getValveMap()) {
            if (!valve.isOpened) {
                ValveMap newValveMap = valveMap;
                newValveMap.openValve(valveNum);
//                if(!memoizedValveMap.count(newValveMap)) {
//                    dfs(newValveMap);
//                }
            }
        }

//        for(auto [unopenedValveNum,unopenedValveDistance]:currValve.edgeList){
//            Valve nextValve=valveMap.find(unopenedValveNum)->second;
//            if(!nextValve.isVisited()) {
//                minRemaining-=unopenedValveDistance+1;
//                int newPressure=minRemaining*nextValve.flowRate;
//                cout <<"Opening Valve: "<<nextValve.valveNum << " Pressure: "<<newPressure<<"\n";
//
//                map<int,Valve> subMap=valveMap;
//                subMap.find(unopenedValveNum)->second.visited= true;
//                newPressure+=dfs(subMap);
//                if(newPressure>maxPressure){
//                    maxPressure=newPressure;
//                    bestMaxValve=nextValve;
//                }
//            }
//        }
//        cout<<bestMaxValve.valveChar<<'\n';
        return maxPressure;
    }

};

void day16Part1(const list<string> &inputStringList) {
    ProboscideaVolcanium proboscideaVolcanium = ProboscideaVolcanium(inputStringList);
    proboscideaVolcanium.dfs(proboscideaVolcanium.initValveMap);
//    proboscideaVolcanium.printValveMap();
//    cout << "==========================\n";
//    proboscideaVolcanium.printEdgeList();
//    cout << "===============================\n";


    //    cout << "========================\n";
//
//    proboscideaVolcanium.printEdgeList();
//    proboscideaVolcanium.printValveMap();
//
//    int maxPressure=proboscideaVolcanium.dfs(proboscideaVolcanium.getValveMap());
//
//    cout<<"Max pressure"<< maxPressure<<"\n";
}

void day16Part2(const list<string> &inputStringList) {
    int score = -1;
    for (const string &line: inputStringList) {
        if (!line.empty()) {

        }
    }
    cout << "Score: " << score << "\n";
}

int mainDay16() {
    initDay(16, &day16Part1, &day16Part2);
    return 16;
}