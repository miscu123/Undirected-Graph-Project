#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

class Graph {
private:
    int n = 0, m = 0;
    std::vector<std::vector<std::pair<int, int>>> adjList; // Lista de adiacenta
    std::vector<std::vector<int>> adjMatrix;  // Matrice de adiacenta
    std::vector<std::vector<int>> costMatrix; // Matrice de cost
    std::vector<std::vector<int>> incidenceMatrix; // Matrice de incidenta
    std::vector<std::tuple<int, int, int>> edgeList; // Lista muchiilor

public:
    explicit Graph(const std::string& filename) {
        std::ifstream fin(filename);
        if (!fin) {
            std::cerr << "Eroare la deschiderea fisierului\n";
            exit(1);
        }

        fin >> n >> m;
        adjList.resize(n + 1);
        adjMatrix.assign(n + 1, std::vector<int>(n + 1, 0));
        costMatrix.assign(n + 1, std::vector<int>(n + 1, 9999));
        incidenceMatrix.assign(n + 1, std::vector<int>(m, 0));

        for (int i = 0; i < m; i++) {
            int u, v, g;
            fin >> u >> v >> g;

            // Lista de adiacenta
            adjList[u].emplace_back(v, g);
            adjList[v].emplace_back(u, g);

            // Matrice de adiacenta
            adjMatrix[u][v] = adjMatrix[v][u] = 1;

            // Matrice de cost
            costMatrix[u][v] = costMatrix[v][u] = g;

            // Lista muchiilor
            edgeList.emplace_back(u, v, g);

            // Matrice de incidenta
            incidenceMatrix[u][i] = 1;
            incidenceMatrix[v][i] = 1;
        }

        fin.close();
    }

    void printAdjList() const {
        std::cout << "Lista de adiacenta:\n";
        for (int i = 1; i <= n; i++) {
            std::cout << "De la adresa " << i << ": ";
            for (const auto& [v, g] : adjList[i]) {
                std::cout << "(La adresa: " << v << ", Combustibil: " << g << ") ";
            }
            std::cout << "\n";
        }
    }

    void printAdjMatrix() const {
        std::cout << "\nMatricea de adiacenta:\n";
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                std::cout << adjMatrix[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    void printCostMatrix() const {
        std::cout << "\nMatricea de cost:\n";
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (costMatrix[i][j] == 9999)
                    std::cout << "Inf ";
                else
                    std::cout << costMatrix[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    void printEdgeList() const {
        std::cout << "\nLista muchiilor:\n";
        for (const auto& [u, v, g] : edgeList) {
            std::cout << u << " - " << v << " (" "Combustibil: " << g << ")\n";
        }
    }

    void printIncidenceMatrix() const {
        std::cout << "\nMatricea de incidenta:\n";
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < m; j++) {
                std::cout << incidenceMatrix[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    void dijkstra(int const source) const {
        std::vector<int> dist(n + 1, INT_MAX);
        std::vector<bool> visited(n + 1, false);
        std::vector<int> parent(n + 1, -1);

        dist[source] = 0;

        for (int count = 0; count < n; count++) {
            int u = -1;
            for (int i = 1; i <= n; i++) {
                if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                    u = i;
                }
            }

            visited[u] = true;

            for (const auto& [v, weight] : adjList[u]) {
                if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }

        std::cout << "\nDrumuri minime de la depozit (" << source << "):\n";
        for (int i = 1; i <= n; i++) {
            if (i == source) continue;

            if (dist[i] == INT_MAX) {
                std::cout << "Nu exista drum catre clientul " << i << "\n";
            } else {
                std::cout << "Pana la adresa " << i << ": ";
                std::vector<int> path;
                int current = i;
                while (current != -1) {
                    path.push_back(current);
                    current = parent[current];
                }

                for (int j = path.size() - 1; j >= 0; j--) {
                    std::cout << path[j];
                    if (j > 0) std::cout << " -> ";
                }
                std::cout << " (Cost total combustibil: " << dist[i] << ")\n";
            }
        }
        cout<<endl;
    }

    bool isHamiltonianCycleUtil(std::vector<int>& path, int pos, std::vector<bool>& visited) const {
        if (pos == n) {
            return adjMatrix[path[pos-1]][path[0]] == 1;
        }
        for (int v = 1; v <= n; v++) {
            if (adjMatrix[path[pos-1]][v] == 1 && !visited[v]) {
                path[pos] = v;
                visited[v] = true;

                if (isHamiltonianCycleUtil(path, pos + 1, visited)) {
                    return true;
                }

                visited[v] = false;
            }
        }

        return false;
    }

    void findHamiltonianCycle() const {
        std::vector<int> path(n + 1);
        std::vector<bool> visited(n + 1, false);

        path[0] = 1;
        visited[1] = true;
        if (!isHamiltonianCycleUtil(path, 1, visited)) {
            std::cout << "Graful nu are ciclu hamiltonian.\n";
            return;
        }

        std::cout << "Ciclu hamiltonian: ";
        for (int i = 0; i < n; i++) {
            std::cout << path[i] << " -> ";
        }
        std::cout << path[0] << "\n";
    }

    // Fixed DFSUtil function
    void DFSUtil(int v, std::vector<bool>& visited) {
        visited[v] = true;

        for (const auto& [neighbor, weight] : adjList[v]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

    bool isConnected() {
        std::vector<bool> visited(n + 1, false);
        int startVertex = 1;

        for (int i = 1; i <= n; i++) {
            if (!adjList[i].empty()) {
                startVertex = i;
                break;
            }
        }

        if (startVertex == n + 1) return true;

        DFSUtil(startVertex, visited);

        for (int i = 1; i <= n; i++) {
            if (!visited[i] && !adjList[i].empty()) {
                return false;
            }
        }

        return true;
    }

    int isEulerian() {
        if (!isConnected()) {
            return 0;
        }

        int oddDegreeCount = 0;
        for (int i = 1; i <= n; i++) {
            if (adjList[i].size() % 2 != 0) {
                oddDegreeCount++;
            }
        }

        if (oddDegreeCount > 2) {
            return 0;
        }

        return (oddDegreeCount == 0) ? 2 : 1; // 2 for Eulerian, 1 for Semi-Eulerian
    }

    void eulerianCycle() {
        int eulerianStatus = isEulerian();

        if (eulerianStatus == 0) {
            std::cout << "\nGraful nu are circuit sau drum eulerian.\n";
            return;
        }

        std::vector<std::vector<std::pair<int, int>>> adjListCopy = adjList;
        std::vector<int> circuit;

        int startVertex = 1;
        if (eulerianStatus == 1) {
            for (int i = 1; i <= n; i++) {
                if (adjList[i].size() % 2 != 0) {
                    startVertex = i;
                    break;
                }
            }
        }

        std::stack<int> currentPath;
        currentPath.push(startVertex);

        while (!currentPath.empty()) {
            int currentVertex = currentPath.top();

            if (adjListCopy[currentVertex].empty()) {
                circuit.push_back(currentVertex);
                currentPath.pop();
            } else {
                auto [neighbor, weight] = adjListCopy[currentVertex].back();
                adjListCopy[currentVertex].pop_back();

                for (auto it = adjListCopy[neighbor].begin(); it != adjListCopy[neighbor].end(); ++it) {
                    if (it->first == currentVertex) {
                        adjListCopy[neighbor].erase(it);
                        break;
                    }
                }

                currentPath.push(neighbor);
            }
        }

        if (eulerianStatus == 2) {
            std::cout << "\nCircuit eulerian: ";
        } else {
            std::cout << "\nDrum eulerian: ";
        }

        std::reverse(circuit.begin(), circuit.end());

        for (size_t i = 0; i < circuit.size(); i++) {
            std::cout << circuit[i];
            if (i < circuit.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }

    void minimumSpanningTree() {
        std::cout << "\nArborele minim de acoperire (MST):\n";

        std::vector<int> parent(n + 1, -1);
        std::vector<int> key(n + 1, INT_MAX);
        std::vector<bool> inMST(n + 1, false);

        key[1] = 0;

        for (int count = 0; count < n; count++) {
            int u = -1;
            for (int v = 1; v <= n; v++) {
                if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                    u = v;
                }
            }

            inMST[u] = true;

            for (const auto& [v, weight] : adjList[u]) {
                if (!inMST[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                }
            }
        }

        int totalWeight = 0;
        std::cout << "Muchii in MST:\n";
        for (int i = 2; i <= n; i++) {
            std::cout << parent[i] << " - " << i << " (Combustibil: " << costMatrix[i][parent[i]] << ")\n";
            totalWeight += costMatrix[i][parent[i]];
        }
        std::cout << "Combustibil total MST: " << totalWeight << std::endl;
    }

    bool BFS_for_flow(vector<vector<int>>& rGraph, int s, int t, vector<int>& parent) {
        vector<bool> visited(n + 1, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;
        parent[s] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v = 1; v <= n; v++) {
                if (!visited[v] && rGraph[u][v] > 0) {
                    if (v == t) {
                        parent[v] = u;
                        return true;
                    }
                    q.push(v);
                    visited[v] = true;
                    parent[v] = u;
                }
            }
        }
        return false;
    }

    int fordFulkerson(int source, int sink) {
        vector<vector<int>> rGraph(n + 1, vector<int>(n + 1, 0));
        vector<vector<int>> flowGraph(n + 1, vector<int>(n + 1, 0));

        for (int u = 1; u <= n; u++) {
            for (const auto& [v, capacity] : adjList[u]) {
                rGraph[u][v] = capacity;
            }
        }

        vector<int> parent(n + 1);
        int max_flow = 0;

        while (BFS_for_flow(rGraph, source, sink, parent)) {
            int path_flow = INT_MAX;

            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                path_flow = min(path_flow, rGraph[u][v]);
            }

            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                rGraph[u][v] -= path_flow;
                rGraph[v][u] += path_flow;
                flowGraph[u][v] += path_flow;
            }

            max_flow += path_flow;
        }

        cout << "\nMatricea de flux:\n";
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                cout << flowGraph[i][j] << " ";
            }
            cout << endl;
        }

        cout <<"Fluxul maxim este: ";
        return max_flow;
    }

};

int main() {
    Graph g(R"(C:\Users\Lenovo\CLionProjects\Optimizarea livrarii comenzilor in oras\Graf.txt)");
    g.printAdjList();
    g.printAdjMatrix();
    g.printCostMatrix();
    g.printEdgeList();
    g.printIncidenceMatrix();
    g.dijkstra(1);
    g.findHamiltonianCycle();
    g.eulerianCycle();
    g.minimumSpanningTree();
    cout << "\nFluxul maxim: " << g.fordFulkerson(1, 5) << endl;

    return 0;
}