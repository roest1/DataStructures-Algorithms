/**
 * A test bed for a weighted digraph abstract data type implementation
 * and implementations of elementary classical graph algorithms that use the
 * ADT
 * @see GraphAPI.java, Graph.java, City.java
 * @author Duncan, Riley Oest
 * <pre>
 * usage: GraphDemo <graphFileName>
 * <graphFileName> - a text file containing the description of the graph
 * in DIMACS file format
 * Date: 11/6/22
 * course: csc 3102
 * programming project 3
 * Instructor: Dr. Duncan
 * </pre>
 */

import java.io.*;
import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.function.Function;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.concurrent.atomic.AtomicBoolean;

////////////////////////////////////////////////////////////////////////
////////////////////////Instructions///////////////////////////////
////////////////////////////////////////////////////////////////////////
/**
 * Mankind invented a system to cope with the fact that we are so intrinsically
 * lousy at manipulating numbers
 * - Charlie Munger
 * 
 * Augmenting an adjacency list implementation of a weighted digraph ADT
 * 
 * Need to write both ADT and non-member functions :
 * 
 * -> Minimum spanning tree of a simple undirected connected weighted graph
 * using Prim's algorihtm
 * ie: minimum spanning forest if the graph is not connected by applying Prim's
 * algorithm to each component of the graph
 * 
 * -> All-pairs shortest path Floyd-Warshall algorithm.
 * Shortest path problem is to find the graph geodesic, by connecting two
 * specific vertices (u, v) of a directed/undirected graph
 * ⟹ the length of the graph geodesic between these points δ(u, v) is called the
 * graph distance between u and v.
 * 
 * ///////Simplifying assumption/////////
 * ⟹ Weights on the edges are non-negative real numbers.
 * 
 * The program will have the following interface :
 * BASIC WEIGHTED GRAPH APPLICATION
 * =========================================
 * [1] BFS/DFS Traversal of G
 * [2] Connected Components of G
 * [3] Floyd's Shortest Round Trip in G
 * [4] Check whether G is Bipartite
 * [5] Prim's Minimum Spanning Tree/Forest in G
 * [0] Quit
 * ===========================================
 * 
 * 
 * //////////Definitions////////////
 * Bipartite graph := A set of graph vertices decomposed into two disjoint sets
 * such that no two graph vertices within the same set are adjacent
 * Connected := An undirected graph G is connected if there is a path between
 * any pair of vertices in G
 * Connected Components := The set of largest subgraphs of G that are each
 * connected
 * 
 * 
 * //////////// For [1] BFS/DFS Traversal of G /////////////
 * The application will generate and display a breadth-first-search and
 * depth-first-traversal of the input graph.
 * (Both traversals have been implemented)
 * Invoke these traversal methods using an appropriate lambda function.
 * 
 * To test menu option [1], you may use a directed or undirected graph.
 * 
 * ///////// For [2] Connected Components of G /////////
 * ⟹ Need to complete non-member getComponents() function
 * The getComponents() function uses the isEdge() ADT member function in its
 * implementation
 * ⟹ Need to complete isEdge() ADT member function
 * 
 * To test menu option [2], you may use an undirected graph
 * 
 * ////////// For [3] Floyd's Shorted Round Trip in G //////////
 * ⟹ Need to implement isPath() member function and floyd non-member function
 * This option displays details about the shortest round-trip (directed-cycle)
 * between any two vertices in teh input digraph
 * i.) if one exists
 * ii.) displays a message indicating that no round-trip between the two
 * vertices exists
 * 
 * To test menu option [3], you may use a weighted digraph only
 * 
 * ////////// For [4] Check whether G is Bipartite //////////
 * The application will generate and display a connected components of the input
 * undirected graph.
 * 
 * To test menu option [4], you may use an undirected graph
 * 
 * ////////// For [5] Prim's Minimum Spanning Tree/Forest in G///////////
 * Genrates a minimum spanning tree or forest of an undirected weighted graph.
 * Do this by calling a function that uses a priority-queue-based implementation
 * of Prim's MST algorithm
 * 
 * To test menu option [5], you may use an undirected graph
 * 
 * Executiable file : GraphDemo
 * 
 * Input : weighted digraph file will be a varitaion on the DIMACS network flow
 * format described below.
 * 
 * ///////////DIMACS : Center for Discrete Mathematics and Theoretical Computer
 * Science///////////
 * - Rutgers University
 * 
 * Comments : Each comment begins with 'c'
 * 
 * Problem Line : p NODES EDGES
 * - 1 problem line per input file
 * - Appears before any node or edge descriptor lines
 * - 'p' indicates the start of the problem line
 * - NODES = |V| (number of vertices in graph)
 * - EDGES = |E| (number of edges in graph)
 * 
 * Node descriptors : n ID LABEL
 * - Appear before edge descriptor lines
 * - 'n' indicates the start of a node descriptor line
 * - ID gives a node identification number ∈ [1, |V|]
 * - LABEL gives a string which serves as an alternate label for the vertex
 * 
 * EDGE Descriptors : e SRC DST WEIGHT
 * - One edge descriptor line for each edge in the graph
 * - 'e' indicates the start of Edge descriptor line
 * - For a directed edge (v, w), SRC gives the identification number for the
 * source vertex v
 * - For a directed edge (v, w), DST gives the destination vertex w
 * - For an undirected edge, (v, w) and (w, v) refer to the same edge so only
 * one edge descriptor line appears and the end points of the edge are written
 * in lexicographical order
 * - Identification numbers are integers ∈ [1, |V|]
 * - WEIGHT field contains cost(v, w)
 * 
 * //////////
 * 
 * The input file name is entered as a command line argument.
 * The assumption is that the file is in DIMACS format so no validation is done
 * on the input file
 * The readGraph function has already been implemented and reads the input file
 * and creates a Graph instance
 * Several sample weighted digraph files in DIMACS are available
 * Additional digraph files in DIMACS format may be used to test the application
 * There are three weighted digraph files in DIMACS format named cities[1-2,
 * 7].wdg
 * Also provided : cities[1-2, 7].pdf = visual depictions of the digraphs
 * 
 * There are four undirected weighted graphs cities[4-5, 10-11, 14].wug and
 * pdf's with their visual depictions : cities[4-5, 10-11, 14].pdf
 * 
 */

public class GraphDemo {
    public static final Double INFINITY = Double.POSITIVE_INFINITY;
    public static final Integer NIL = -1;

   public static void main(String []args) throws GraphException
   {
      if (args.length != 1)
      {
         System.out.println("Usage: GraphDemo <filename>");
         System.exit(1);
      }
      City c1, c2;
      Scanner console;
      int menuReturnValue, i,j;
      Function<City,PrintStream> f = aCity -> System.out.printf("%-2d  %-30s%n",aCity.getKey(),aCity.getLabel().trim());      
      Graph<City> g = readGraph(args[0]);      
      long s = g.size();
      menuReturnValue = -1;
      while (menuReturnValue != 0)
      {
         menuReturnValue = menu();
         switch(menuReturnValue)
         {
            case 1: //post-order depth-first-search traversal of g'
               System.out.println();
               System.out.println("Breadth-First-Search Traversal of the Graph In "+args[0]);
               System.out.println("==========================================================================");
               //invoke the bfsTraverse function
               g.bfsTraverse(f);
               // Output should be aligned in two-column format as illustrated below:
               // 1     Charlottetown
               // 4     Halifax
               // 2     Edmonton     

               System.out.println("==========================================================================");
               System.out.println();
               System.out.println("Depth-First-Search Traversal of the Graph In "+args[0]);
               System.out.println("==========================================================================");
               //invoke the dfsTraverse function
               g.dfsTraverse(f);
               // Output should be aligned in two-column format as illustrated below:
               // 1     Charlottetown
               // 4     Halifax
               // 2     Edmonton     

               System.out.println("==========================================================================");
               System.out.println();
               System.out.println();
               break;
            case 2: //Connected Components of G                 
                 System.out.println();
                 System.out.println("Connected Components in "+args[0]);
                 System.out.println();      
                 if (g.size() > 0) 
                 {
                    int [] cities = new int [(int) g.size()];
                     int components = getComponents(g, cities);
                     for (int city = 1; city <= components; city++) {
                        System.out.println("*** Component # " + city + " ***");
                        for (i = 1; i <= g.size(); i++) {
                            if (cities[i - 1] == city) {
                                //try {
                                    System.out.println(g.retrieveVertex(new City(i)).getLabel());
                                //  } catch (GraphException ge) {
                                    
                                //  }
                            }
                        }
                     }
                     System.out.println("----------------------\nNumber of Components: " + components);
                    
                     //Add code here to print the list of cities in each component of the graph.
                     //For example:
                     //*** Component # 1 ***
                     //Baton Rouge
                     //Gonzales
                     //Metaire                   
                     //*** Component # 2 ***
                     //Lafayette
                     //Independence
                     //*** Component # 3 ***
                     //Baker
                     //Eunice
                     //Franklin
                     //--------------------------
                     //Number of Components: 3
					 
					 
					 
                     //End code                  
				 }
                 else
                     System.out.println("The graph has no connected component.");
                 System.out.println();
                 System.out.println();
                 System.out.println();
                 break;                            
            case 3://Shortest-path algorithm
               console = new Scanner(System.in);
               System.out.printf("Enter the source vertex: ");      
               i = console.nextInt();
               System.out.printf("Enter the destination vertex: ");      
               j = console.nextInt();
               if (g.isPath(new City(i), new City(j)) && g.isPath(new City(j), new City(i)))
               {
                  int dest;
                  double[][] cost = new double[(int)g.size()][(int)g.size()];
                  int[][] path = new int[(int)g.size()][(int)g.size()];
                  int initial = i;
                  floyd(g,cost,path);
                  System.out.printf("Shortest round trip from %s to %s:%n",g.retrieveVertex(new City(i)).getLabel().trim(),g.retrieveVertex(new City(j)).getLabel().trim());				   
                  System.out.println("=========================================================================================");
                  //Add code here to print each leg of the trip from the source to the destination
                  String fromCity = g.retrieveVertex(new City(i)).getLabel().trim();
                  String toCity = g.retrieveVertex(new City(j)).getLabel().trim();

                  int next = i;
                  System.out.printf("%s -> %s:%n", fromCity, toCity);
                  while (next != j) {
                      System.out.printf("%-2s -> %-2s %.2f mi%n", 
                        g.retrieveVertex(new City(next)).getLabel().trim(), 
                        g.retrieveVertex(new City(path[next - 1][j - 1])).getLabel().trim(), 
                        g.retrieveEdge(new City(next), new City(path[next - 1][j - 1])));
                      next = path[next - 1][j - 1];
                  }
                  System.out.printf("Distance: %.2f mi%n%n", cost[i - 1][j - 1]);
                  System.out.printf("%s -> %s:%n", toCity, fromCity);
                  next = j;
                  while (next != i) {
                      System.out.printf("%-2s -> %-2s %.2f mi%n",
                              g.retrieveVertex(new City(next)).getLabel().trim(),
                              g.retrieveVertex(new City(path[next - 1][i - 1])).getLabel().trim(),
                              g.retrieveEdge(new City(next), new City(path[next - 1][i - 1])));
                      next = path[next - 1][i - 1];
                  }
                  System.out.printf("Distance: %.2f mi%n", cost[j - 1][i - 1]);

                  //using the format below, where the columns are left-aligned and the distances
                  //are displayed to the nearest hundredths.
                  //For example:
                  //Baton Rouge -> New Orleans:
                  //Baton Rouge            ->   Gonzales                  10.20 mi
                  //Gonzales               ->   Metaire                   32.00 mi
                  //Metaire                ->   New Orleans                7.25 mi
                  //Distance: 49.75 mi
                  //
                  //New Orleans -> Baton Rouge
                  //New Orleans            ->   Metaire                    8.00 mi
                  //Metaire                ->   Gonzales                  33.00 mi
                  //Gonzalen               ->   Baton Rouge               10.00 mi
                  //Distance: 51.00 mi
                  //


                  //End code                                      
                  System.out.println("=========================================================================================");
                  System.out.printf("Round Trip Distance: %.2f miles.%n%n",cost[i-1][j-1]+cost[j-1][i-1]);                               
               }
               else
                  System.out.printf("There is no path.%n%n");
               break;
            case 4: //Check whether g is bipartite
                System.out.println();
                AtomicBoolean bip = new AtomicBoolean(true);
                int[] part = isBipartite(g,bip);
                if (bip.get())
                {
                    if (g.size() == 0)
                        System.out.println("An empty graph is vacuously bipartite.");
                    else
                    {
                        System.out.printf("The Graph is Bipartite.%n%n");
                        System.out.println("First Partition: ");
                        for (i = 1; i <= g.size(); i++)
                        {
                            if (part[i] == 1)
                                System.out.printf("%d. %s%n ",i,g.retrieveVertex(new City(i)).getLabel().trim());
                        }
                        System.out.println();
                        System.out.println("Second Partition: ");
                        int k = 0;
                        for (i = 1; i <= g.size(); i++)
                        {
                            if (part[i] == 0)
                            {
                                System.out.printf("%d. %s%n ",i,g.retrieveVertex(new City(i)).getLabel().trim());
                                k++;
                            }
                        }
                        if (k == 0)
                            System.out.println("EMPTY");
                    }
                }
                else
                    System.out.println("The graph is not bipartite.");                        
                System.out.println();
                break;                 
            case 5: //primMST;
			   int edgesInMST = 0;
               System.out.printf("Enter the root of the MST: ");
               console = new Scanner(System.in);
               j=console.nextInt();                
               int[] mst = new int[(int)g.size()];
               double totalWt = primMST(g,j,mst);
               String cityNameA,cityNameB;
               System.out.println();
               for (i=1; i<=g.size(); i++)
               {
                   if (mst[i-1] < 1)
                       cityNameA = "NONE";
                   else
				   {
					   edgesInMST++;
                       cityNameA = g.retrieveVertex(new City(mst[i-1])).getLabel().trim();
				   }
                   cityNameB = g.retrieveVertex(new City(i)).getLabel().trim();                       
                   System.out.printf("%d-%s parent[%d] <- %d (%s)%n",i,cityNameB,i,mst[i-1],cityNameA);
               }
               System.out.printf("The weight of the minimum spanning tree/forest is %.2f miles.%n",totalWt);    
               System.out.printf("Spanning Tree Edge Density is %.2f%%.%n%n",100.0*edgesInMST/g.countEdges());
			   break;
            default: ;
         } //end switch
      }//end while
   }// end main

    /**
     * This method reads a text file formatted as described in the project
     * description.
     * 
     * @param filename the name of the DIMACS formatted graph file.
     * @return an instance of a graph.
     */
    private static Graph<City> readGraph(String filename) {
        try {
            Graph<City> newGraph = new Graph();
            try (FileReader reader = new FileReader(filename)) {
                char temp;
                City c1, c2, aCity;
                String tmp;
                int k, m, v1, v2, j, size = 0, nEdges = 0;
                Integer key, v1Key, v2Key;
                Double weight;
                Scanner in = new Scanner(reader);
                while (in.hasNext()) {
                    tmp = in.next();
                    temp = tmp.charAt(0);
                    if (temp == 'p') {
                        size = in.nextInt();
                        nEdges = in.nextInt();
                    } else if (temp == 'c') {
                        in.nextLine();
                        in.nextLine();
                    } else if (temp == 'n') {
                        key = in.nextInt();
                        tmp = in.nextLine();
                        aCity = new City(key, tmp);
                        newGraph.insertVertex(aCity);
                    } else if (temp == 'e') {
                        v1Key = in.nextInt();
                        v2Key = in.nextInt();
                        weight = in.nextDouble();
                        c1 = new City(v1Key);
                        c2 = new City(v2Key);
                        newGraph.insertEdge(c1, c2, weight);
                    }
                }
            }
            return newGraph;
        } catch (IOException exception) {
            System.out.println("Error processing file: " + exception);
        }
        return null;
    }

    /**
     * Display the menu interface for the application.
     * 
     * @return the menu option selected.
     */
    private static int menu() {
        Scanner console = new Scanner(System.in);
        // int option;
        String option;
        do {
            System.out.println("  BASIC WEIGHTED GRAPH APPLICATION   ");
            System.out.println("=======================================================");
            System.out.println("[1] BFS/DFS Traversal of G");
            System.out.println("[2] Connected Components of G");
            System.out.println("[3] Floyd's Shortest Round Trip in G");
            System.out.println("[4] Check whether G is Bipartite");
            System.out.println("[5] Prim's Minimum Spanning Tree/Forest in G");
            System.out.println("[0] Quit");
            System.out.println("=====================================");
            System.out.printf("Select an option: ");
            option = console.nextLine().trim();
            try {
                int choice = Integer.parseInt(option);
                if (choice < 0 || choice > 7) {
                    System.out.println("Invalid option...Try again");
                    System.out.println();
                } else
                    return choice;
            } catch (NumberFormatException e) {
                System.out.println("Invalid option...Try again");
            }
        } while (true);
    }

    /**
     * Determines whether an undirected graph is bipartite
     * 
     * @param g         an undirected graph
     * @param bipartite is true if g is bipartite, otherwise false
     * @return an array of size |G|+1. The first entry is |G| and the remaining
     *         entries are in {0,1} when g is bipartite where [i] = 0 if vertex i
     *         is in the first partition and 1 if it is in the second partition;
     *         if g is not bipartite NULL returned.
     */
    private static int[] isBipartite(Graph<City> g, AtomicBoolean bipartite) throws GraphException {
        if (g.isEmpty()) throw new GraphException("Empty graph");
        int [] part = new int [(int)g.size()];
        int i, j = 0;
        for (i = 0; i < part.length; i++) {
            part[i] = NIL;
        }
        bipartite.set(true);
        for (i = 1; i < part.length; i++) {
	        if (part[i] == -1) {
		        part[i] = 0;
            }
            for (j = i + 1; j <= part.length; j++) {
		        if (g.isEdge(new City(i), new City(j))) {
                    if (part[i] == part[j]) {
                        bipartite.set(false);
				            return null;
                    }
			        if (part[j] == -1) {
                        part[j] = (part[i] + 1)%2;
                    }
                }
            }
        }
        return part;
        // implementation attempted
    }

    /**
     * This method computes the cost and path matrices using the
     * Floyd all-pairs shortest path algorithm.
     * 
     * @param g    an instance of a weighted directed graph.
     * @param dist a matrix containing distances between pairs of vertices.
     * @param path a matrix of intermediate vertices along the path between a pair
     *             of vertices. 0 indicates that the two vertices are adjacent.
     * @return none.
        */
    private static void floyd(Graph<City> g, double dist[][], int path[][]) throws GraphException {
        // implement this method.
        if (g.isEmpty()) {
            throw new GraphException("Empty graph");
        }
        int i, j, k;
        for (i = 1; i <= g.size(); i++) {
            for (j = 1; j <= g.size(); j++) {
                if (i == j) {
                    path[i-1][j-1] = j;
                    dist[i-1][j-1] = 0;
                } else if (g.isEdge(new City(i), new City(j))) {
                    path[i-1][j-1] = j;
                    dist[i-1][j-1] = (int)g.retrieveEdge(new City(i), new City(j));
                } else {
                    dist[i-1][j-1] = INFINITY;
                    path[i-1][j-1] = NIL;
                }
            }
        }
        for (i = 1; i <= g.size(); i++) {
            dist[i-1][i-1] = 0;
            path[i-1][i-1] = i;
        }
        for (k = 1; k <= g.size(); k++) {
            for (i = 1; i <= g.size(); i++) {
                for (j = 1; j <= g.size(); j++) {
                    if (dist[i-1][k-1] != INFINITY && dist[k-1][j-1] != INFINITY && dist[i-1][j-1] > dist[i-1][k-1] + dist[k-1][j-1]) {
                        path[i-1][j-1] = path[i-1][k-1];
                        dist[i-1][j-1] = dist[i-1][k-1] + dist[k-1][j-1];
                    }
                }
            }
        }
    }
    
    /**
     * This method generates a minimum spanning tree rooted at a given
     * vertex, root. If no such MST exists, then it generates a minimum
     * spanning forest.
     * 
     * @param g      a weighted undirected graph
     * @param r      root of the minimum spanning tree, when one exists.
     * @param parent the parent implementation of the minimum spanning tree/forest
     * @return the weight of such a tree or forest.
     * @throws GraphException when this graph is empty
     * 
     *                        <pre>
     * {@code
     * If a minimum spanning tree rooted at r is in the graph,
     * the parent implementation of a minimum spanning tree or forest is
     * determined. If no such tree exist, the parent implementation 
     * of an MSF is generated. If the tree is empty, an exception 
     * is generated.
     * }
     * </pre>
     */
   private static double primMST(Graph<City> g, int root, int[] parent) throws GraphException {
        // implement this method
        if (g.isEmpty())
            throw new GraphException("Empty graph in call to primMST()");
        if (!g.isVertex(new City(root)))
            throw new GraphException("Non-existent root in call to primMST()");
        int numVertices = (int) g.size();
        double[] dist = new double[numVertices];
        boolean[] processed = new boolean[numVertices];
        for (int i = 0; i < numVertices; i++) {
            dist[i] = INFINITY;
            parent[i] = -1;
            processed[i] = false;
        } 
        dist[root - 1] = 0;
        double totalWeight = 0;
        class Node {
            public int parent, id;
            public double key;

            public Node() {

            }

            public Node(int p, int v, double k) {
                parent = p;
                id = v;
                key = k;
            }
        }

        Comparator<Node> cmp = (v1, v2) -> {
            double d = v1.key - v2.key;
            if (d < 0)
                return -1;
            if (d > 0)
                return 1;
            d = v1.id - v2.id;
            if (d < 0)
                return -1;
            if (d > 0)
                return 1;
            return 0;
        };

        // Define an instance of the PriorityQueue class that uses the comparator;
        // Then implement the priority-queue-based Prim's MST algorithm
        PriorityQueue<Node> pq = new PriorityQueue<>(cmp);
        boolean[] visited = new boolean[numVertices + 1];
        Arrays.fill(visited, false);
    
        for (int i = 0; i < visited.length; i++){
            pq.add(new Node(NIL, i, INFINITY));
        }
        pq.add(new Node(NIL, root, 0));
        int count = 0;
        while (count < numVertices) {
            Node u = pq.remove();
            while (visited[u.id] == true) {
                u = pq.remove();
            }
            count += 1;
            parent[u.id - 1] = u.parent;
            if (parent[u.id - 1] == NIL) {
                u.key = 0;
            }
            dist[u.id] = u.key;
            totalWeight += u.key;
            for (int j = 1; j <= numVertices; j++) {
                
                if (g.isEdge(new City(u.id), new City(j)) && visited[j] == false) {
                    double weight = g.retrieveEdge(new City(u.id), new City(j));
                    if (weight < dist[j]) {
                        dist[j] = weight;
                        parent[j - 1] = u.id;
                        pq.add(new Node(u.id, j, dist[j]));
                    }
                }
            }
        }
        return totalWeight;
    }

    /**
     * Generates the connected components of this graph
     * 
     * @param g          a graph of city objects
     * @param components an associative array of city
     *                   key to component number: if components[i] = k, then
     *                   city i+1 is in component k.
     * @return the number of components in this graph
     * @throws GraphException
     */
    private static int getComponents(Graph<City> g, int components[]) throws GraphException {
        // Implement this method
        if (g.isEmpty())  throw new GraphException("Empty Graph");
        int count = 0, numVertices = 0;
        Queue<Integer> q = new LinkedList<>();
        while (numVertices < g.size()) {
            count += 1;
            int v = 1;
            while (components[v - 1] != 0) {
                v += 1;
            }
            q.add(v);
            components[v - 1] = count;
            numVertices += 1;
            while (!q.isEmpty()) {
                int r = q.poll();
                for (int i = r + 1; i <= g.size(); i++) {
                    if (g.isEdge(new City(r), new City(i)) && components[i - 1] == 0) {
                        q.add(i);
                        components[i - 1] = count;
                        numVertices += 1;
                    }
                }
            }
        }
        return count;
    }
}
