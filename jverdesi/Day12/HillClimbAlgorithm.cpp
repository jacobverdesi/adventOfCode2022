//
// Created by jacob on 12/13/21222.
//
#include <windows.h>

#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include "../Utils/InitDay.h"
#include "HillClimbAlgorithm.h"
#include "../Utils/ColorMod.h"

using namespace std;

class Point {
public:
    int x{}, y{}, z{};
    int g = 0;
    int h = 0;
    int f = 0;
    Point *prev = nullptr;
    bool visited = false;
    bool inHeap = false;
    bool finalPath = false;

    explicit Point(int x1, int y1, int z1) {
        x = x1;
        y = y1;
        z = z1;
    }
};

struct pointComparator {
    bool operator()(const Point *a, const Point *b) const {
        return a->f > b->f;
    }
};

tuple<vector<vector<Point>>, pair<int, int>, pair<int, int>> inputMap(const list<string> &inputStringList) {
    vector<vector<Point>> map;
    int y = 0;
    pair<int, int> start;
    pair<int, int> end;
    for (const string &line: inputStringList) {
        vector<Point> row;
        int x = 0;
        for (auto col: line) {
            int z = (int) col - 97;
            if (col == 'S') {
                z = 0;
                start = pair(x, y);
            }
            if (col == 'E') {
                z = 25;
                end = pair(x, y);
            }

            row.emplace_back(x, y, z);
            x++;
        }
        map.push_back(row);
        y++;
    }
    tuple<vector<vector<Point>>, pair<int, int>, pair<int, int>> startEnd = tuple(map, start, end);
    return startEnd;
}

vector<Point *> getNeighbors(vector<vector<Point>> &map, Point *curr) {
    int width = (int) map[0].size();
    int height = (int) map.size();

    int x = curr->x;
    int y = curr->y;
    int z = curr->z;

    vector<pair<int, int>> neighbors{make_pair(0, -1), make_pair(-1, 0), make_pair(1, 0), make_pair(0, 1)};
    vector<Point *> validNeighbors;
    for (auto [i, j]: neighbors) {
        if ((0 <= x + i) and (x + i < width) and (0 <= y + j) and (y + j < height - 1)) {
            Point &neighbor = map[y + j][x + i];
            if (neighbor.z <= z + 1)
                validNeighbors.push_back(&neighbor);
        }
    }
    return validNeighbors;
}

int heuristic(Point *curr, Point *goal) {

    int dx = abs(curr->x - goal->x);
    int dy = abs(curr->y - goal->y);
    int dz = abs(curr->z - goal->z);
    int euclidian2D = (int) sqrt((dx * dx) + (dy * dy));
    int euclidian3D = (int) sqrt(euclidian2D * euclidian2D + dz * dz);
    int city_block = dx + dy;
    return euclidian3D;
}

int getPathLength(vector<vector<Point>> &map) {
    int pathLength = 0;
    int numVisited = 0;
    Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);
    for (const auto &row: map) {
        for (auto point: row) {
            if (point.visited) {
                numVisited++;
                if (point.finalPath) {
                    pathLength++;
                    //cout << red << '*' << def;
                } //else
                   // cout << '#';
                //cout << char(point.z + 97);

            } else {
               // cout << char(point.z + 97);
            }
        }
    //    cout << '\n';
    }
    return pathLength;


}

void astar(vector<vector<Point>> &map, pair<int, int> startPoint, pair<int, int> endPoint) {
    Point *start = &map[startPoint.second][startPoint.first];
    Point *end = &map[endPoint.second][endPoint.first];
    start->h = heuristic(start, end);
    start->f = heuristic(start, end);

    vector<Point *> heap;
    make_heap(heap.begin(), heap.end(), pointComparator());
    heap.push_back(start);
    push_heap(heap.begin(), heap.end(), pointComparator());
    while (!heap.empty()) {
        Point *curr = heap.front();
        pop_heap(heap.begin(), heap.end(), pointComparator());
        heap.pop_back();


        curr->inHeap = false;
        curr->visited = true;
        if (curr->x == end->x and curr->y == end->y) {
            while (curr->prev != nullptr) {
                curr->finalPath = true;
                curr = curr->prev;
            }
            break;

        }
        vector<Point *> neighborPointers(getNeighbors(map, curr));
        vector<Point *>::iterator neighbor;
        for (neighbor = neighborPointers.begin(); neighbor != neighborPointers.end(); neighbor++) {
            //cout << "\tChecking Neighbor (" << (*neighbor)->x << ',' << (*neighbor)->y << ")\n";
            if (!(*neighbor)->visited and !(*neighbor)->inHeap) {
                (*neighbor)->prev = curr;
                (*neighbor)->g = curr->g + 1;
                (*neighbor)->h = heuristic(curr, end);
                (*neighbor)->f = (*neighbor)->g + (*neighbor)->h;
                (*neighbor)->inHeap = true;
                heap.push_back((*neighbor));
                push_heap(heap.begin(), heap.end(), pointComparator());

            }
        }

    }
}
vector<pair<int,int>> getNewStartingPositions(vector<vector<Point>> &map){
    vector<pair<int,int>> startingPositionList;
    for(const auto& row:map){
        for(auto col:row){
            if(col.z==0)
                startingPositionList.emplace_back(col.x,col.y);
        }
    }
    return startingPositionList;
}


void day12Part1(const list<string> &inputStringList) {
    auto [map, start, end] = inputMap(inputStringList);

    astar(map, start, end);
    int pathLength = getPathLength(map);
    cout << "Path length: " << pathLength << '\n';

}

void day12Part2(const list<string> &inputStringList) {
    auto [map, start, end] = inputMap(inputStringList);
    int minShortestPathLength=1000;
    vector<pair<int,int>> newStartingPositions=getNewStartingPositions(map);
    cout<<"Num starting Positions: "<<newStartingPositions.size()<<'\n';
    for(auto startingPos: newStartingPositions) {
        astar(map, startingPos, end);
        int newLength = getPathLength(map);
        if(newLength<minShortestPathLength and newLength!=0)
            minShortestPathLength=newLength;
        map.clear();
        auto [newMap, start, end] = inputMap(inputStringList);
        map=newMap;

    }
    int pathLength = getPathLength(map);
    cout << "Path length: " << minShortestPathLength << '\n';

}

int mainDay12() {
    system(("chcp "s + std::to_string(CP_UTF8)).c_str());

    initDay(12, &day12Part1, &day12Part2);
    return 0;
}