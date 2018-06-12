//
// Created by ericpqmor on 29/05/18.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstring>
#include <queue>
#include <string>
#include <list>

using namespace std;
#define MAXN 1000
#define INF 10000000

typedef pair<float, float> ff;
typedef pair<int, int> ii;
typedef vector<int> vi;

class TravelingSalesman {

public:

    TravelingSalesman(ff Nodes[], int citiesNumber) {
        //Calculating distances and filling graph
        for(int i=1; i<=citiesNumber; i++) {
            for(int j=i; j<=citiesNumber; j++) {
                int distNodes = vertexDist(Nodes[i].first, Nodes[i].second, Nodes[j].first, Nodes[j].second);
                dist[i][j] = distNodes;
                dist[j][i] = distNodes;
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
                cout << dist[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

   //  A utility function to print the constructed MST stored in parent[]
    void printMST() {
        for (int i = 1; i <= citiesNumber; i++) {
            cout << i << ": ";
            for(int j=0; j<mst[i].size(); j++) {
                cout << mst[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void printCycle() {
        for(int i=0; i<cycle.size(); i++)
            cout << cycle[i] << " " << endl;
        cout << endl;
    }

    /*
     * Find the Minimun Spamming Tree using Prim's Algorithm
     */
    void findMST() {
        if(citiesNumber == 0) return;
        priority_queue<pair<ii,int>, vector<pair<ii,int> >, greater<pair<ii,int> > > pq;
        vi key(citiesNumber+2, INF);
        vi parent(citiesNumber+2, 0);
        vector<bool> inMST(citiesNumber+2, false);
        int src = 1;

        pq.push(make_pair(make_pair(key[1],src),1));
//        key[src] = 0;
        inMST[src] = true;

        while(!pq.empty()) {
            int u = pq.top().second;
//            cout << "Visiting pair(" << pq.top().first.second << "," << u << ")" << endl;
            pq.pop();

            if(!inMST[u]) {
                int d = dist[u][parent[u]];
                core[u].push_back(make_pair(parent[u],d));
                core[parent[u]].push_back(make_pair(u,d));
            }
            inMST[u] = true;

            for(int v = 1; v <= citiesNumber; ++v) {
                int w = dist[u][v];
                if(inMST[v] or v == u) continue;
//                cout << "\tTesting (" << u << "," << v << ")" << endl;

                if(key[v] > w) {
                    key[v] = w;
                    parent[v] = u;
                    pq.push(make_pair(make_pair(key[v], u),v));
                }

                if(key[v] == w and u < parent[v]) {
                    key[v] = w;
                    parent[v] = u;
                    pq.push(make_pair(make_pair(key[v], u),v));
                }
            }
        }
        for(int i=2; i<=citiesNumber; i++) {
//          printf("%d - %d\n", parent[i], i);
            mst[i].push_back(parent[i]);
            mst[parent[i]].push_back(i);
        }
    }

    void calculateCycle(int mark[MAXN], int u) {
        mark[u] = 1;
        cycle.push_back(u);

        for(int i=0; i<core[u].size(); i++) {
            int ind = core[u][i].first;

            if(!mark[ind]) calculateCycle(mark,ind);
        }
    }

    int getCycleCost() {
        int cost = 0;
        for(int i=0; i<cycle.size()-1; i++)
            cost += dist[cycle[i]][cycle[i+1]];
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
    vector<ii> core[MAXN];
    int dist[MAXN][MAXN];
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
                nodes[index] = make_pair(xi, yi);
            }

            TravelingSalesman g(nodes, citiesNumber);

            return g;

        } else {
            cerr << "Input file could not be found!" << endl;
        }
    }

    void readInputsAndSolve() {
        int m;
        std::cin >> m;

        for(int i=1; i<=m; i++) {
            string s = "ent";
            string ms = to_string(i);
            s = i < 10 ? s + "0" + ms + ".txt" : s + ms + ".txt";
//            cout << "s: " << s << endl;
            TravelingSalesman tsp = readInput(s);
            tsp.solveTSP();
//            tsp.printCycle();
//            tsp.printMST();
//            tsp.print();
            writeOutput(tsp.getCycleCost());
        }
    }

    void writeOutput(int cost) {
        output << cost << endl;
    }

private:
    ofstream output;
};

int main() {
    clock_t begin = clock();
    TravelingReader tr;
    tr.readInputsAndSolve();
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Elapsed time: " << elapsed_secs << " s" << endl;
}
