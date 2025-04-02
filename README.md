# Undirected-Graph-Project
This project features code for an undirected graph, read from a .txt file. It generates the adjacency list and matrices and implements algorithms such as Dijkstra's, Minimum Spanning Tree (MST), Eulerian and Hamiltonian cycles, and Maximum Flow.

**Project Documentation  
Optimization of Order Delivery in the City**

1. **Introduction:** This project models a parcel delivery system in the city using graph theory. The objective is to optimize the courier's delivery routes, minimizing the total distance traveled and the associated delivery costs.

2. **Graph Representation:** To model the problem, an undirected weighted graph was used, where:
   - Nodes represent relevant locations (e.g., the depot and customer addresses).
   - Edges represent the roads between locations, each associated with a weight (the transportation cost between two locations).

   The graph is represented in multiple forms:
   - Adjacency list
   - Adjacency matrix
   - Cost matrix
   - Edge list
   - Incidence matrix

3. **Implemented Algorithms:**
   
   3.1 **Dijkstra's Algorithm - Shortest Path**
   This algorithm is used to determine the shortest route from the depot (node 1) to all delivery locations, minimizing the total fuel cost.
   
   3.2 **Eulerian and Hamiltonian Cycles**
   - **Hamiltonian Cycle:** Checks if there is a route that allows visiting each address exactly once and returning to the depot.
   - **Eulerian Cycle:** Checks if the courier can traverse each road exactly once without interrupting the delivery.
   
   3.3 **Minimum Spanning Tree (MST)**
   The MST algorithm helps identify the optimal road structure so that all locations are connected at a minimal cost. Prim's algorithm is used for this purpose.
   
   3.4 **Maximum Flow - Ford-Fulkerson Algorithm**
   To determine the maximum parcel transport capacity between the depot and an endpoint (e.g., the final customer's address), the Ford-Fulkerson algorithm is implemented.

4. **Code Structure:**
   The `Graph` class implements all necessary methods for graph manipulation and processing, including methods for reading data from a file, displaying graph structures, and applying the mentioned algorithms.

   In the file, the graph is defined as follows:
   ```
   5 6
   1 2 3
   1 3 2
   2 4 5
   2 5 1
   3 5 4
   4 5 6
   ```
   The first line, ‘5’, represents the number of nodes in the graph, while ‘6’ represents the number of edges. A visualization of this graph would be as follows:
   ![image](https://github.com/user-attachments/assets/62a69b35-5af7-4895-9aef-c7d5d3a15197)

5. **Conclusions:** This project demonstrates the usefulness of graph algorithms in real-world problems, optimizing delivery routes and reducing transportation costs. The applied algorithms allow for the analysis and improvement of delivery logistics in a crowded city, making it a viable solution for various logistical scenarios.

6. **Documentation:** This project was developed with the help of materials from the Geeks for Geeks website, as well as course materials on Graph Algorithms:
   - **Dijkstra – shortest path:** Course/Laboratory on Graph Algorithms
   - **MST:** Course/Laboratory on Graph Algorithms
   - **Eulerian path and circuit for undirected graph** | GeeksforGeeks
   - **Hamiltonian Cycle** | GeeksforGeeks

