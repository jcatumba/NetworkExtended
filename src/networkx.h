/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#ifndef NETWORKX_H
#define NETWORKX_H

#include "python_load.h" 

#ifdef __cplusplus
extern "C" {
#endif

extern PyObject* nxGraph;
extern PyObject* nx_add_node;
extern PyObject* nx_remove_node;
extern PyObject* nx_add_edge;
extern PyObject* nx_remove_edge;
extern PyObject* nx_write_gml;

//
// Loading NetworkX functions
//
void init_networkx (void);
void load_nx_objects(PyObject*);

//--- Callable NetworkX functions
/*** NetworkX Basic Classes (Graph types). TODO: Allow the user to use Attributes ***/
//NX_object* Graph (stack *p);
//NX_object* DiGraph(stack *p);
//NX_object* MultiGraph(stack *p);
//NX_object* MultiDiGraph(stack *p);
///*** NetworkX Basic Methods ***/
//double len(stack *p);
//NX_object* add_node(stack *p);
//NX_object* add_nodes_from(stack *p);
//NX_object* remove_node(stack *p);
//NX_object* remove_nodes_from(stack *p);
//NX_object* add_edge(stack *p);
//NX_object* add_edges_from(stack *p);
//NX_object* add_weighted_edges_from(stack *p);
//NX_object* remove_edge(stack *p);
//NX_object* remove_edges_from(stack *p);
//NX_object* add_star(stack *p);
//NX_object* add_path(stack *p);
//NX_object* add_cycle(stack *p);
//NX_object* clear(stack *p);
//NX_object* nodes(stack *p);
//NX_object* nodes_iter(stack *p);
//NX_object* edges(stack *p);
//NX_object* edges_iter(stack *p);
//NX_object* out_edges(stack *p); /* [Multi]DiGraph specific */
//NX_object* out_edges_iter(stack *p); /* [Multi]DiGraph specific */
//NX_object* in_edges(stack *p); /* [Multi]DiGraph specific */
//NX_object* in_edges_iter(stack *p); /* [Multi]DiGraph specific */
//NX_object* get_edge_data(stack *p);
//NX_object* neighbors(stack *p);
//NX_object* neighbors_iter(stack *p);
//NX_object* successors(stack *p); /* [Multi]DiGraph specific */
//NX_object* successors_iter(stack *p); /* [Multi]DiGraph specific */
//NX_object* predecessors(stack *p); /* [Multi]DiGraph specific */
//NX_object* predecessors_iter(stack *p); /* [Multi]DiGraph specific */
//NX_object* adjacency_list(stack *p);
//NX_object* adjacency_iter(stack *p);
//NX_object* nbunch_iter(stack *p);
//NX_object* has_node(stack *p);
//NX_object* has_edge(stack *p);
//double order(stack *p);
//NX_object* degree(stack *p);
//NX_object* degree_iter(stack *p);
//NX_object* in_degree(stack *p); /* [Multi]DiGraph specific */
//NX_object* in_degree_iter(stack *p); /* [Multi]DiGraph specific */
//NX_object* out_degree(stack *p); /* [Multi]DiGraph specific */
//NX_object* out_degree_iter(stack *p); /* [Multi]DiGraph specific */
//NX_object* size(stack *p);
//NX_object* number_of_edges(stack *p);
//NX_object* nodes_with_selfloops(stack *p);
//NX_object* selfloop_edges(stack *p);
//NX_object* number_of_selfloops(stack *p);
//NX_object* copy(stack *p);
//NX_object* to_undirected(stack *p);
//NX_object* to_directed(stack *p);
//NX_object* subgraph(stack *p);
//NX_object* reverse(stack *p); /* [Multi]DiGraph specific */
//
///*** NetworkX Algorithms ***/
//NX_object* max_clique(stack *p);
//NX_object* clique_removal(stack *p);
//NX_object* min_weighted_dominating_set(stack *p);
//NX_object* min_edge_dominating_set(stack *p);
//NX_object* maximum_independet_set(stack *p);
//NX_object* min_maximal_matching(stack *p);
//NX_object* ramsey_R2(stack *p);
//NX_object* min_weighted_vertex_cover(stack *p);
//NX_object* degree_assortativity_coefficient(stack *p);
//NX_object* attribute_assortativity_coefficient(stack *p);
//NX_object* numeric_assortativity_coefficient(stack *p);
//NX_object* degree_pearson_correlation_coefficient(stack *p);
//NX_object* average_neighbor_degree(stack *p);
//NX_object* average_degree_connectivity(stack *p);
//NX_object* k_nearest_neighbors(stack *p);
//NX_object* attribute_mixing_matrix(stack *p);
//NX_object* degree_mixing_matrix(stack *p);
//NX_object* degree_mixing_dict(stack *p);
//NX_object* attribute_mixing_dict(stack *p);
//NX_object* is_bipartite(stack *p);
//NX_object* is_bipartite_node_set(stack *p);
//NX_object* sets(stack *p);
//NX_object* color(stack *p);
//NX_object* density(stack *p);
//NX_object* degrees(stack *p);
//NX_object* biadjacency_Matrix(stack *p);
//NX_object* projected_graph(stack *p);
//NX_object* weighted_projected_graph(stack *p);
//NX_object* collaboration_weighted_projected_graph(stack *p);
//NX_object* overlap_weighted_projected_graph(stack *p);
//NX_object* generic_weighted_projected_graph(stack *p);
//NX_object* spectral_bipartivity(stack *p);
//NX_object* clustering(stack *p);
//NX_object* redundancy(stack *p);
//NX_object* closeness_centrality(stack *p);
//NX_object* degree_centrality(stack *p);
//NX_object* in_degree_centrality(stack *p);
//NX_object* out_degree_centrality(stack *p);
//NX_object* betweenness_centrality(stack *p);
//NX_object* edge_betweenness_centrality(stack *p);
//NX_object* blockmodel(stack *p);
//NX_object* edge_boundary(stack *p);
//NX_object* node_boundary(stack *p);
//NX_object* current_flow_closeness_centrality(stack *p);
//NX_object* current_flow_betweenness_centrality(stack *p);
//NX_object* edge_current_flow_betweenness_centrality(stack *p);
//NX_object* approximate_current_flow_betweenness_centrality(stack *p);
//NX_object* eigenvector_centrality(stack *p);
//NX_object* eigenvector_centrality_numpy(stack *p);
//NX_object* communicability(stack *p);
//NX_object* communicability_exp(stack *p);
//NX_object* communicability_centrality(stack *p);
//NX_object* communicability_centrality_exp(stack *p);
//NX_object* communicability_betwenness_centrality(stack *p);
//NX_object* estrada_index(stack *p);
//NX_object* load_centrality(stack *p);
//NX_object* edge_load(stack *p);
//
//NX_object* dijkstra_path(stack *p);

/*** NetworkX Drawing ***/

#ifdef __cplusplus
}
#endif

#endif //NETWORKX_H
