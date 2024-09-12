#include "main.h"
#include <iostream>
#include <fstream>
#include <sstream>

void displayMenu() {
    std::cout << "Homework 5 - CSE 310\n";
    std::cout << "1. Read the graph from the file (enter the file name, D or UD and the flag)\n";
    std::cout << "   for example network01.txt D 1 or 2 for the directed graph\n";
    std::cout << "2. Print ADJ\n";
    std::cout << "3. Single Source, enter the starting node number\n";
    std::cout << "4. Single Pair, enter the starting node and ending node numbers\n";
    std::cout << "5. Print Path, enter the starting node and ending node numbers\n";
    std::cout << "6. Print Length, enter the starting node and ending node numbers\n";
    std::cout << "7. Print Path, enter the starting node and ending node numbers\n";
    std::cout << "8. Stop\n";
    std::cout << "Enter options 1 - 8\n";
}

using namespace std;

void processCommands(Graph& graph) {
    int choice, s, t, flag;
    string fn, tp;


    while (true) {
        displayMenu();
        cin >>  choice;

        switch (choice) {
        case 1:
            cin >> fn >> tp >> flag;
            {
                std::ifstream inputFile(fn);
                if (!inputFile) {
                    cerr << "Error opening input file." << endl;
                    break;
                }
                int n, m;
                inputFile >> n >> m;
                Graph newGraph(n, m);
                int edgeIndex, u, v;
                float w;
                bool insertAtRear = (flag == 2);
                while (inputFile >> edgeIndex >> u >> v >> w) {
                    newGraph.addEdge(u, v, w, insertAtRear);
                }
                graph = newGraph;
            }
            break;

        case 2:
            graph.printAdj();
            break;

        case 3:
            cin >> s;
            graph.dijkstra(s);
            break;

        case 4:
            cin >> s >> t;
            graph.dijkstra(s);
            graph.printPath(s, t);
            break;

        case 5:
            cin >> s >> t;
            graph.printPath(s, t);
            break;

        case 6:
            cin >> s >> t;
            graph.printLength(s, t);
            break;

        case 7:
            cin >> s >> t;
            graph.printPath(s, t);
            break;

        case 8:
            cout << "Exiting program." << endl;
            return;

        default:
            cerr << "Invalid option." << endl;
            break;
        }
    }
}

int main() {

    Graph graph(0, 0);  
    processCommands(graph);
    return 0;
}
