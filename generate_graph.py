#!/usr/bin/env python

from itertools import combinations, groupby
import json
import random
import networkx as nx

def gnp_random_connected_graph(n, p):
    """
    Generates a random undirected graph, similarly to an Erdős-Rényi
    graph, but enforcing that the resulting graph is conneted
    """
    edges = combinations(range(n), 2)
    G = nx.Graph()
    G.add_nodes_from(range(n))
    if p <= 0:
        return G
    if p >= 1:
        return nx.complete_graph(n, create_using=G)
    for _, node_edges in groupby(edges, key=lambda x: x[0]):
        node_edges = list(node_edges)
        random_edge = random.choice(node_edges)
        G.add_edge(*random_edge)
        for e in node_edges:
            if random.random() < p:
                G.add_edge(*e)
    return G

NUM_NODES = 50

VEHICLES = ["Light", "Colorful"]
VERTICES = ["Basic", "Recolor"]

G = gnp_random_connected_graph(NUM_NODES, 0.002)

data = {
    "vertices" : {},
    "vehicles" : {}
}

vertices = data["vertices"]
vehicles = data["vehicles"]

for node in G.nodes:
    nodeName = "v" + str(node);
    vertices[nodeName] = {
        "type" : random.choice(VERTICES),
        "incident" : {}
    }
    incident = vertices[nodeName]["incident"]
    for edge in G.edges(node):
        incident["v" + str(edge[1])] = {
            "length" : random.uniform(0.3, 1.5)
        }

for i in range(1, random.randint(NUM_NODES // 10, NUM_NODES // 2)):
    vehicles[str(i)] = {
        "type" : random.choice(VEHICLES),
        "initial" : "v" + str(random.randint(0, NUM_NODES - 1))
    }

with open('graph.json', 'w') as outfile:
    json.dump(data, outfile)

