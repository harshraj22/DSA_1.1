import sys
import heapq

class Graph():
    """
        returns graph in the form of adjacency list
    """
    @classmethod
    def convert(cls, inputGraph):
        graph = dict()
        for index, row in enumerate(inputGraph):
            vertex1, vertex2, weight = row
            graph[vertex1] = (weight, vertex2)
            graph[vertex2] = (weight, vertex1)
        return graph

class DSU():
    def __init__(self, vertices):
        self.vertices = vertices
        self.weight = [1 for _ in range(vertices+1)]
        self.parent = [i for i in range(vertices+1)] 

    def find_par(self, index):
        """
            Path compression
        """
        if index == self.parent[index]:
            return index
        self.parent[index] = self.find_par(self.parent[index])
        return self.parent[index]

    def merge(self, x, y):
        """
            Union by rank (or weighted union)
        """
        xp, yp = self.find_par(x), self.find_par(y)
        if self.weight[xp] > self.weight[yp]:
            self.parent[yp] = xp
            self.weight[xp] += self.weight[yp]
        else:
            self.parent[xp] = yp
            self.weight[yp] += self.weight[xp]

    def forms_loop(self, x, y):
        return True if self.find_par(x) == self.find_par(y) else False

class MST(DSU):
    # inherits from DSU, thus has all its public methods available
    def __init__(self, graph, vertices):
        super(MST, self).__init__(vertices)
        """
            graph is list of tuple(weight, vertex1, vertex2)
        """
        self.graph = graph
        self.mst = []

    def compute(self):
        """
            computes the mst
        """
        # create a min heap
        heapq.heapify(self.graph)

        while len(self.graph) != 0:
            # extract min : the min weighted edge
            weight, v1, v2 = heapq.heappop(self.graph)

            # if the edge doesn't forms loop, add it to current MST
            if not self.forms_loop(v1, v2):
                self.mst.append((weight, v1, v2))
                self.merge(v1, v2)

    def print(self, outputFile):
        # sort self.mst based on weight
        self.mst = sorted(self.mst, key=lambda x: x[0])
        with open(outputFile, 'w') as f:
            for tup in self.mst:
                f.write(' '.join(str(i) for i in tup[::-1]))
                f.write('\n')

if __name__=='__main__':
    inputFile = sys.argv[1]
    with open(inputFile) as f:
        data = f.read().split('\n')
        # takes a string having 3 space separated integers and returns tuple of these integers
        convert = lambda x: tuple(map(int, x.split()))
        inputGraph = list(map(convert, data))
    
    # newGraph is list of tuple(weight, vertex1, vertex2)
    newGraph = [x[::-1] for x in inputGraph if len(x) != 0 ]

    # graph is adjacency list representation of given input graph
    graph = Graph().convert(newGraph)


    vertices = max(graph.keys())
    tree = MST(newGraph, vertices)
    tree.compute()
    tree.print("mst.txt")