//
// Created by ericpqmor on 29/05/18.
//

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <queue>

using namespace std;
#define MAXN 1000
#define INF 10000000

typedef pair<float, float> ff;
typedef pair<int, int> ii;
typedef vector<int> vi;

class TravelingSalesman {

public:
    TravelingSalesman(std::pair<float, float> Nodes[], int citiesNumber) {
        //Calculating distances and filling graph
        for(int i=1; i<=citiesNumber; i++) {
            for(int j=i; j<=citiesNumber; j++) {
                matrix[i][j] = vertexDist(Nodes[i].first, Nodes[i].second, Nodes[j].first, Nodes[j].second);
                matrix[j][i] = matrix[i][j];
            }
        }

        this->citiesNumber = citiesNumber;
        for(int i=1; i<=citiesNumber; i++)
            mst[i].clear();
    }

    ~TravelingSalesman() {
        //free(matrix);
    }

    void print() {
        for(int i=1; i<=citiesNumber; i++) {
            for(int j=1; j<=citiesNumber; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

   //  A utility function to print the constructed MST stored in parent[]
    int printMST() {
        for (int i = 1; i <= citiesNumber; i++) {
            cout << i << ": ";
            for(int j=0; j<mst[i].size(); j++) {
                cout << mst[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    int printCycle() {
        for(int i=0; i<cycle.size(); i++)
            cout << cycle[i] << " " << endl;
        cout << endl;
    }

    /*
     * Find the Minimun Spamming Tree using Prim's Algorithm
     */
    void findMST() {
        priority_queue<ii, vector<ii>, greater<ii> > pq;

        int src = 1;

        vi key(citiesNumber+2, INF);
        vi parent(citiesNumber+2, 0);
        vector<bool> inMST(citiesNumber+2, false);

        pq.push(make_pair(0, src));
        key[src] = 0;

        while(!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            inMST[u] = true;

            for(int i=1; i<=citiesNumber; i++) {
                if(u == i) continue;
                int w = matrix[u][i];

                if(!inMST[i] && key[i] > w) {
                    key[i] = w;
                    pq.push(make_pair(key[i], i));
                    parent[i] = u;
                }
            }
        }

        for(int i=2; i<=citiesNumber; i++) {
            mst[i].push_back(parent[i]);
            mst[parent[i]].push_back(i);
        }
    }

    void calculateCycle(int mark[MAXN], int u) {
        mark[u] = 1;
        cycle.push_back(u);

        for (int v=0; v<mst[u].size(); v++) {
            int e = mst[u][v];
            if(mark[e]) continue;

            calculateCycle(mark, e);
        }
    }

    int getCycleCost() {
        int cost = 0;
        for(int i=0; i<cycle.size()-1; i++)
            cost += matrix[cycle[i]][cycle[i+1]];
        return cost;
    }

    void solveTSP() {
        findMST();
        int mark[MAXN];
        memset(mark, 0, sizeof mark);
        calculateCycle(mark, 1);
        cycle.push_back(1); //Closing cycle
    }

private:
    int matrix[MAXN][MAXN];
    vi mst[MAXN];
    int citiesNumber;
    vi cycle;

    int vertexDist(float x1, float y1, float x2, float y2) {
        float xd = x1 - x2;
        float yd = y1 - y2;
        return static_cast<int>(sqrt(xd * xd + yd * yd) + 0.5);
    }
};

class TravelingReader {
public:

    TravelingReader() {
        output.open("saida.txt");
    }

    ~TravelingReader() {
        output.close();
    }

    TravelingSalesman readInput(std::string inputFile) {
        ifstream input;
        input.open(inputFile.c_str());

        if(input.is_open()) {
            int graph[MAXN][MAXN];
            ff nodes[MAXN];
            int citiesNumber;

            input >> citiesNumber;

            //Reading nodes
            for(int count=1; count<=citiesNumber; count++) {
                int index;
                float xi, yi;

                input >> index >> xi >> yi;
                nodes[index] = std::make_pair(xi, yi);
            }

            TravelingSalesman g(nodes, citiesNumber);

            return g;

        } else {
            cerr << "Input file could not be found!" << endl;
        }
    }

    void writeOutput(int cost) {
        output << cost << endl;
    }

private:
    ofstream output;
};

int main() {
    TravelingReader tr;
    TravelingSalesman tsp = tr.readInput("ent01.txt");
    tsp.solveTSP();
    tr.writeOutput(tsp.getCycleCost());
}
