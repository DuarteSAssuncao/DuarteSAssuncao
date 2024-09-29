# DA2324\_PRJ2\_G17\_5
Repository for the first project of "Desenho de Algoritmos", group 5, class 2LEIC17.
In this project we make a Routing Algorithm for Ocean Shipping and Urban Deliveries.

This project was developed by:
- Duarte Assunção - up202208319@up.pt - 33.(3)% effort
- Lucas Bessa - up202208396@up.pt - 33.(3)% effort
- Pedro Gorobey - up202210292@up.pt - 33.(3)% effort

---

## How to use
We developed an interface to allow the user to easily interact with the Network.  
First, you need to load the desired graph to the program. Please, read the next section of how to load the csv files.  
You can, then, execute the provided TSP algorithms, as described below.

## Load csv files
Because we are working with very large data structures, we couldn't include the csv files in the delivery.  
Please, put in the "csv" directory the directories with the graphs and rename the "Real-world Graphs" directory to "Real-World".  
Then, you can easily load the graphs to the program and execute the provided algorithms.

## Available algorithms
    0 - load <edges_csv> [<nodes_csv>]  
        Loads the graph using the given filenames  

    1 - backtrack                       
        Solves the TSP using the Backtracking algorithm  

    2 - tineq                           
        Solves the TSP using the 2-approximation Triangle Inequality algorithm  

    3 - near                            
        Solves the TSP using the Nearest Neighbour algorithm  

    4 - bhk                             
        Solves the TSP using the Bellman-Held-Karp algorithm  

    5 - bhks                            
        Solves the TSP using the Bellman-Held-Karp String Version algorithm (slower but uses less memory)  

    6 - rwtsp [<src_id>]                
        Solves the TSP using the Real World adaptation of the 2-approximation Triangular Inequality algorithm  

    7 - exit | quit                     
        Quits the program  

    Notes:  
        - src_id is an optional argument to choose the node to start at  
        - You can either type the algorithm name (as shown above) or its correspondent number  
