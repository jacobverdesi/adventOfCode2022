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
    int heuristic_distance = 0;
    Point *prev = nullptr;
    bool visited = false;
    bool inHeap = false;
    bool finalPath=false;

    explicit Point(int x1, int y1, int z1) {
        x = x1;
        y = y1;
        z = z1;
    }
};

struct pointComparator {
    bool operator()(const Point *a, const Point *b) const {
        return a->heuristic_distance > b->heuristic_distance;
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
        if ((0 <= x + i) and (x + i < width) and (0 <= y + j) and (y + j < height-1)) {
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
    int euclidian2D = (int)sqrt(dx * dx + dy * dy);
    int euclidian3D = (int) sqrt(euclidian2D * euclidian2D + dz * dz);
    return euclidian2D;
}
void printMap(vector<vector<Point>> &map){
    int pathLength=0;
    Color::Modifier red(Color::FG_RED);
    Color::Modifier def(Color::FG_DEFAULT);
    for(const auto& row:map){
        for(auto point:row){
            if (point.visited) {
                if(point.finalPath) {
                    pathLength++;
                    cout<<red<<'*'<<def;
                }

                else
                    cout<< char(point.z+97);
                    //cout << '#';
            }
            else{
                cout<< char(point.z+97);
            }
        }
        cout<<'\n';
    }
    cout<<"Path length: "<<pathLength<<'\n';
}

void astar(vector<vector<Point>> &map, pair<int, int> startPoint, pair<int, int> endPoint) {
    Point *start = &map[startPoint.second][startPoint.first];
    Point *end = &map[endPoint.second][endPoint.first];

    start->heuristic_distance = heuristic(start, end);
    vector<Point *> heap;
    make_heap(heap.begin(), heap.end(), pointComparator());
    heap.push_back(start);
    push_heap(heap.begin(), heap.end());
    while (!heap.empty()) {
        pop_heap(heap.begin(), heap.end(), pointComparator());
        Point *curr = heap.back();
        heap.pop_back();
        curr->inHeap = false;
        curr->visited = true;
        if(curr->x==end->x and curr->y==end->y){
            while (curr->prev!= nullptr){
                curr->finalPath=true;
                curr= curr->prev;
            }
            break;

        }
        vector<Point *> neighborPointers(getNeighbors(map, curr));
        vector<Point *>::iterator neighbor;
        for (neighbor = neighborPointers.begin(); neighbor != neighborPointers.end(); neighbor++) {
            //cout << "\tChecking Neighbor (" << (*neighbor)->x << ',' << (*neighbor)->y << ")\n";
            if (!(*neighbor)->visited and (!(*neighbor)->inHeap)) {
                (*neighbor)->prev = curr;
                (*neighbor)->heuristic_distance = heuristic(curr, (*neighbor));
                (*neighbor)->inHeap = true;
                heap.push_back((*neighbor));
                push_heap(heap.begin(), heap.end(),pointComparator());
            }
        }

    }
    printMap(map);
}



void day12Part1(const list<string> &inputStringList) {
    auto [map, start, end] = inputMap(inputStringList);
//    cout << start.first << start.second << " " << end.first << end.second << '\n';
    astar(map, start, end);

}

void day12Part2(const list<string> &inputStringList) {
    int score = 12;
    for (const string &line: inputStringList) {
        if (!line.empty()) {

        }
    }
    cout << "Score: " << score << "\n";
}

int mainDay12() {
    system(("chcp "s + std::to_string(CP_UTF8)).c_str());

    initDay(12, &day12Part1, &day12Part2);
    return 0;
}