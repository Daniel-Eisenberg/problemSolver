# Problem Solver

Our program contains server to handle multiple clients, our ```ClientHandler``` is the class that handles each clients requests. each client can send a problem that the server will solve and send the answer back to the client.
In order to solve the problem the ```ClientHandler``` have a member of type ```Solver```.

```Solver``` has our ```searcher``` which is the algorithm part of our implemention of the bridge design pattern.

the second part of our bridge is the ```searcheable``` which is the data stract that we use to represent the problem.

The problem itself is a matrix we get from the client line by line. Using the A* algorithm we send back the "cheapest" way to move through the matrix from index [0][0] to [row size - 1][column size - 1].




###Run the project:

1. Compile and run the project with the code file as an argument.
2. connect to the server using localhost and port 5600. 
3. send request in a form of numbers.
4. send to the server the word "end" when you are done inserting values and you want your problem to be solved.

Enjoy!
