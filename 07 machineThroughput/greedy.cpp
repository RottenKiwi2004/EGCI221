#include <iostream>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <queue>
using namespace std;

struct selectionState {
    int currentPrice;
    int totalWork;
    int maxPrice;
    int machineCount;
    int itemIdx;
    vector <int> v;
};

void printState(struct selectionState &state) {
    cout << "---------------------------------------------" << endl;
    cout << "  currentPrice: " << setw(4) << state.currentPrice << endl;
    cout << "  totalWork: " << setw(4) << state.totalWork << endl;
    cout << "  maxPrice: " << setw(4) << state.maxPrice << endl;
    cout << "  machineCount: " << setw(4) << state.machineCount << endl;
    cout << "  itemIdx: " << setw(4) << state.itemIdx << endl;
    cout << "  machinePicked: ";
    for (int i=0; i<state.v.size(); i++) cout << state.v[i] << ", ";
    cout << endl;
    cout << "---------------------------------------------" << endl;
}

class CompareState {
public:
    bool operator()(const selectionState &a, const selectionState &b) {
        return a.currentPrice > b.currentPrice;
    }
};

pair <int, int> machines[] = {
    // Price, Work
    make_pair(10, 1), make_pair(21,  7), make_pair(32, 17),
    make_pair(15, 5), make_pair(30, 15), make_pair(25, 10),
};

int main(int argc, char ** argv) {

    int machineVariantCount = sizeof(machines) / sizeof(pair<int, int>);
    if (argc == 1) return -1;
    int W = atoi(argv[1]);

    priority_queue <selectionState, vector <selectionState>, CompareState> pq;
    struct selectionState initial;
    initial.currentPrice = initial.itemIdx = initial.machineCount = initial.maxPrice = initial.totalWork = 0;
    struct selectionState finalState = initial;
    finalState.currentPrice = INT_MAX;    
    
    pq.push(initial);

    while (!pq.empty()) {

        struct selectionState lowestPriceState = pq.top();
        pq.pop();

        int currentPrice    = lowestPriceState.currentPrice;
        int currentMaxPrice = lowestPriceState.maxPrice;
        int totalWork       = lowestPriceState.totalWork;
        int machineCount    = lowestPriceState.machineCount;
        int machineIdx      = lowestPriceState.itemIdx;

        if (totalWork >= W && finalState.currentPrice > currentPrice) {
            finalState = lowestPriceState;
            continue;
        }
        if (machineIdx == machineVariantCount) continue;

        struct selectionState ignoreThisMachine = lowestPriceState;
        ignoreThisMachine.itemIdx++;

        struct selectionState selectThisMachine = lowestPriceState;
        pair <int, int> currentMachine = machines[machineIdx];
        selectThisMachine.maxPrice = max(currentMaxPrice, currentMachine.first);
        selectThisMachine.totalWork += currentMachine.second;
        selectThisMachine.machineCount++;
        selectThisMachine.currentPrice = selectThisMachine.maxPrice * selectThisMachine.machineCount;
        selectThisMachine.v.push_back(machineIdx);
        selectThisMachine.itemIdx++;

        pq.push(selectThisMachine);
        pq.push(ignoreThisMachine);

    }

    printState(finalState);
}