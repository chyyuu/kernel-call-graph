# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import networkx as nx
import matplotlib.pyplot as plt
#G=nx.path_graph(4)
#nx.write_adjlist(G, "/chycode/kernel-call-graph/g2.txt")
#G=nx.read_adjlist("/chycode/kernel-call-graph/g2.txt", create_using=nx.DiGraph())
#nx.write_adjlist(G, "/chycode/kernel-call-graph/g.txt")
G=nx.read_adjlist("/chycode/kernel-call-graph/g.txt", nodetype=str, create_using=nx.DiGraph())
#nx.draw(G)
#plt.savefig("path.png")
print "Nodes: ", G.nodes()
print "Edges: ", G.edges()