//
// Created by jverdesi on 12/24/22.
//

#include "BeaconExclusionZone.h"

#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <regex>
#include <math.h>
#include "../Utils/InitDay.h"
#include "../Utils/tokenizer.h"

using namespace std;

template<
        class result_t   = std::chrono::milliseconds,
        class clock_t    = std::chrono::steady_clock,
        class duration_t = std::chrono::milliseconds
>
auto since(std::chrono::time_point<clock_t, duration_t> const &start) {
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}

class SignalBeaconPair {
    int signalX;
    int signalY;
    int beaconX;
    int beaconY;
    int distance;

public:
    explicit SignalBeaconPair(vector<int> line) {
        signalX = line[0];
        signalY = line[1];
        beaconX = line[2];
        beaconY = line[3];
        auto [xMin, xMax] = minmax(signalX, beaconX);
        auto [yMin, yMax] = minmax(signalY, beaconY);
        distance = (xMax - xMin) + (yMax - yMin);

    }

    [[nodiscard]] bool isWithinDistance(int x, int y) const {
        auto [xMin, xMax] = minmax(signalX, x);
        auto [yMin, yMax] = minmax(signalY, y);
        int new_distance = (xMax - xMin) + (yMax - yMin);
        return new_distance <= distance;
    }

    [[nodiscard]] bool isSignalOrBeacon(int x, int y) const {
        return (x == beaconX and y == beaconY) or (x == signalX and y == signalY);

    }

    [[nodiscard]] vector<pair<int, int>> getPerimeterCoords(int range) const {
        vector<pair<int, int>> perimeterCoords;
        for (int i = 0; i <= distance + 1; i++) {
            int inverse_distance = distance + 1 - i;

            perimeterCoords.emplace_back(signalX - inverse_distance, signalY + i);
            perimeterCoords.emplace_back(signalX - inverse_distance, signalY - i);
            perimeterCoords.emplace_back(signalX + inverse_distance, signalY + i);
            perimeterCoords.emplace_back(signalX + inverse_distance, signalY - i);

        }
        return perimeterCoords;
    }


    bool operator==(SignalBeaconPair const &other) const {
        return this->signalX == other.signalX and
               this->signalY == other.signalY and
               this->beaconX == other.beaconX and
               this->beaconY == other.beaconY;
    }

};

class BeaconExclusionZone {
private:
    vector<SignalBeaconPair> signalBeconPairList;
    int xMin;
    int xMax;

public:
    explicit BeaconExclusionZone(const list<string> &inputStringList, bool isPart2 = false) {
        vector<int> xList;
        vector<int> yList;
        for (string line: inputStringList) {
            if (!line.empty()) {
                const regex re(R"((-)*\d+)");
                vector<int> tokenized(4, 0);
                smatch match;
                int i = 0;
                while (regex_search(line, match, re)) {
                    tokenized[i] = stoi(match.str());
                    if (i == 0 or i == 2)
                        xList.push_back(tokenized[i]);
                    else
                        yList.push_back(tokenized[i]);
                    i++;
                    line = match.suffix().str();
                }
                signalBeconPairList.emplace_back(tokenized);

            }
        }
        xMin = *min_element(xList.begin(), xList.end()) * 2;
        xMax = *max_element(xList.begin(), xList.end()) * 2;

    }

    int countBeaconCoverage(int y) {
        int count = 0;
        for (int x = xMin; x <= xMax; x++) {
            bool foundSignal = false;
            for (auto signalBeacon: signalBeconPairList) {
                if (signalBeacon.isWithinDistance(x, y) and !signalBeacon.isSignalOrBeacon(x, y)) {
                    foundSignal = true;
                    break;
                }
            }
            count += foundSignal;
        }
        return count;
    }

    ::uint64_t tuningFrequency(int range) {

        for (auto signalBeacon: signalBeconPairList) {
            vector<pair<int, int>> perimeterCoordS = signalBeacon.getPerimeterCoords(range);
            for (auto [x, y]: perimeterCoordS) {
                if (0 <= x and x <= range and 0 <= y and y <= range) {
                    bool foundSignal = false;

                    for (auto signalBeacon2: signalBeconPairList) {
                        if (signalBeacon2.isWithinDistance(x, y)) {
                            foundSignal = true;
                            break;
                        }
                    }
                    if (!foundSignal)
                        return (x * (std::uint64_t) 4000000) + y;
                }

            }
        }
        return 0;
    }


};


void day15Part1(const list<string> &inputStringList) {
    BeaconExclusionZone b = BeaconExclusionZone(inputStringList);
    cout << "Score: " << b.countBeaconCoverage(2000000) << "\n";

}

void day15Part2(const list<string> &inputStringList) {
    BeaconExclusionZone b = BeaconExclusionZone(inputStringList);
    ::uint64_t val = b.tuningFrequency(4000000);
    cout << "Score: " << val << "\n";
}

int mainDay15() {
    initDay(15, &day15Part1, &day15Part2);
    return 15;
}