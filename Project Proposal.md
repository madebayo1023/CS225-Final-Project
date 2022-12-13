## Leading Question 
Given a dataset of Netflix movies, what movies are most similar to a movie provided by the user in regards to characteristics provided by the user? For example, one query the user can make is what movie is most similar to Black Panther in regards to level of popularity (how many people watched / revenue generated)? The output is going to be a list of top x movies (either 5 or 10 or however many there is based on the size output generated) that are most similar to what the user’s query is. 

## Dataset Acquisition
We will obtain our dataset from Kaggle, an online crowd-sourced platform. Each row in the dataset contains information relating to a specific movie or show such as its genre, release date and rating among other characteristics. The original dataset contains 7912 unique entries or rows. Each entry has 9 unique characteristics or columns. They include title, year, certificate, duration, genre, rating, description, stars, and votes. Since some characteristics are quantitative such as the ratings column and others are qualitative such as the description column, the nature of finding the most closely related movie or show will be subtly different. Due to concerns regarding runtime efficiency, we are planning to use a subset of the first 1000 entries of the original dataset. 

## Data Format 
We obtained our csv dataset from a website called Kaggle. The dataset contains 7912 unique entries and is in the format “title,year,certificate,duration,genre,rating,description,stars,votes.” Since we are concerned about runtime, we currently plan to use a subset of the entire dataset - the first 1000 entries in the dataset.

## Data Correction
To ensure the data is error-free, we are going to traverse the data to ensure there are no null values in a specific cell at a row, column position. We have already scanned through the dataset and observed no null values. In the case that we do come across a null entry (since this is a large dataset), we are going to ignore that entire row for the specific query that the user requests. For example, if the user wants the top 5 most closely related movies with the same genre, while processing the data and building our resultant output for the top 5 movies, we would simply skip over this row since it serves no purpose due to the null value in the genre column. So, if there is a null value in the column about which the user requests information, we will simply ignore it since we don’t want to tamper with the data. We have not encountered any data points that are statistical outliers.

## Data Storage
We will preprocess the data using google sheets in order to remove any rows with null values and to ensure that all entries have a similar format. This will facilitate the future processing of the data into our data structure. We are also going to make a map of Movie objects to indices, a map of indices to Movie objects, and a two dimensional adjacency matrix of ints that store the similarity scores with respect to each map. For example, if Black Panther maps to 0 and The Batman maps to 1, then the similarity score between the two movies will be stored in both [0][1] and [1][0] of the adjacency matrix. Both maps will have a space complexity of O(n), while the adjacency matrix will have a space complexity of O(n^2). We are going with this improved data structure because we will be able to access the elements in O(1) constant runtime.  

Map<Movie, int> movieToIdx 
Map<int, Movie> idxToMovie 
vector<vector<double>> adjacencyMatrix

Function Inputs What are the expected inputs for your algorithm? Do you have to do anything to convert your stored dataset into a usable input for the algorithm described? (Ex: A graph algorithm would require making the input into a graph.) For the more complex algorithms, be sure to include as part of the input any additional information you might need. For example, A* search requires a heuristic. If you choose to do A*, what are some possible heuristics you might use?

Function Outputs What is the expected output for your algorithm? How will you store, print, or otherwise visualize the outcome?

Function Efficiency Your algorithm likely has a theoretically optimal Big O that you can find online. But most algorithms also have multiple implementations and there is no guarantee that your implementation of this algorithm is optimal. As part of this proposal you must include an estimate or target goal on the Big O efficiency of your algorithm in both time and memory.

## Algorithm
Breadth First Search: To traverse our weighted graph, we will use BFS. The space complexity will be O(n), where n is a node in the graph, because we may need store the entire graph on  a stack while traversing, and the time complexity will be O(n) because we may need to search the entire graph to find a specific element.
In order to find how similar a Movie objects is to all the other movie objects, we will use Dijkstra's Algorithm. The space complexity will be O(V^2) using an adjacency matrix, and a time complexity of O(E+VlogV), where V is the number of vertices and E is the number of edges in the graph.
Betweenness centrality algorithm: We will use this algorithm to find a path between Movie two objects paths such that the similarity between them is maximized, in order to figure how many nodes are between each other. The time complexity O(nm + n2logn) and the space complexity is O(n + m) where n, m are the number of vertices and edges in a graph, respectively.

## Timeline
Week 1: Create movie object class
Getters
Week 2: Create movie recommendation class
Parse dataset, create Movie objects and populate map
Figuring out a recommendation algorithm
Create map (graph) data structure
Week 3: Implement Algorithms
Week 4: Create functions specific to user recommendation request (either top 5/top 10 and if there arent that many they return what we do have) (Everyone)
