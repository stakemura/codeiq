# -*- coding:utf-8 -*-

"""
@brief CodeIQ 'Shortest common superstring' ( https://codeiq.jp/ace/stakemura/q450 )
@author Shintaro TAKEMURA (stakemura@gmail.com)

This code is public domain, no warranty expressed or implied,
Functionality is thought to be correct, but it's up to you to make
sure it does what you want.
"""

import os
import networkx as nx


def calc_distance(s1, s2):
    """
    @type s1: str or unicode 
    @type s2: str or unicode
    @rtype: int
    """
    length = len(s1)
    for i in range(length):
        if s2.startswith(s1[i:]):
            return length - i
    return 0


def generate_network(parts):
    """
    @type parts: list
    @rtype: nx.DiGraph
    """
    G = nx.DiGraph()

    for s1 in parts:
        G.add_node(s1, weight=len(s1))

    for s1 in parts:
        for s2 in parts:
            if s1 != s2:
                d = calc_distance(s1, s2)
                if d>0:
                    G.add_edge(s1, s2, weight=d, label=s2[:d])
    return G

if __name__ == '__main__':
    from optparse import OptionParser

    parser = OptionParser()

    parser.add_option("-o", "--output", dest="output", #default="superstring.graphml",
                      help="output path", metavar="FILE")

    options, args = parser.parse_args()

    parts = ['onoult',
             'oniosis',
             'oultra',
             'ilicov',
             'canoco',
             'tramic',
             'oconio',
             'pneumo',
             'copics',
             'icrosco',
             'csilic',
             'ovolcano']

    G = generate_network(parts)

    if options.output:
        writers = {
                'adjlist':nx.write_adjlist,
                'dot':nx.write_dot,
                'xdot':nx.write_dot,
                'edges':nx.write_edgelist,
                'elist':nx.write_edgelist,
                'edgelist':nx.write_edgelist,
                'weighted_edgelist':nx.write_weighted_edgelist,
                'graphml':nx.write_graphml,
                'gml':nx.write_gml,
                'gpickle':nx.write_gpickle,
                'pajek':nx.write_pajek,
                'yaml':nx.write_yaml}

        graph_type = os.path.splitext(options.output)[1][1:]
        if graph_type in writers:
            try:
                writers[graph_type](G=G, path=options.output)
            except Exception, inst:
                print 'Graph write error:'
                print inst
        else:
            raise Exception,'Unable to write graphs of type: '+str(graph_type)
    else:
        import matplotlib.pyplot as plt
        pos = nx.circular_layout(G) # positions for all nodes
        #pos = nx.spring_layout(G, iterations=20) # positions for all nodes
        # nodes
        nx.draw_networkx_nodes(G, pos)
        # edges
        nx.draw_networkx_edges(G, pos)
        # node labels
        nx.draw_networkx_labels(G, pos)
        # edge labels
        #nx.draw_networkx_edge_labels(G, pos)

        plt.axis('off')
        plt.show() # display
