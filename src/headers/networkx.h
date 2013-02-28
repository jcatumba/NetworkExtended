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

#include "parser.h"

//
// Loading NetworkX functions
//
void init_networkx (void);
NX_object* load_nx(NX_object *nxobject, const char* attr_name);
NX_object* load_networkx();
void load_objects(NX_object *nxobj);

//--- Callable NetworkX functions
/*** NetworkX Basic Classes (Graph types). TODO: Allow the user to use Attributes ***/
NX_object* Graph (stack *p);
/*NX_object* Graph(params p);*/
NX_object* DiGraph(params p);
NX_object* MultiGraph(params p);
NX_object* MultiDiGraph(params p);
/*** NetworkX Basic Methods ***/
NX_object* len(params p);
NX_object* add_node(params p);
NX_object* add_nodes_from(params p);
NX_object* remove_node(params p);
NX_object* remove_nodes_from(params p);
NX_object* add_edge(params p);
NX_object* add_edges_from(params p);
NX_object* add_weighted_edges_from(params p);
NX_object* remove_edge(params p);
NX_object* remove_edges_from(params p);
NX_object* add_star(params p);
NX_object* add_path(params p);
NX_object* add_cycle(params p);
NX_object* clear(params p);
NX_object* nodes(params p);
NX_object* nodes_iter(params p);
NX_object* edges(params p);
NX_object* edges_iter(params p);
NX_object* out_edges(params p); /* [Multi]DiGraph specific */
NX_object* out_edges_iter(params p); /* [Multi]DiGraph specific */
NX_object* in_edges(params p); /* [Multi]DiGraph specific */
NX_object* in_edges_iter(params p); /* [Multi]DiGraph specific */
NX_object* get_edge_data(params p);
NX_object* neighbors(params p);
NX_object* neighbors_iter(params p);
NX_object* successors(params p); /* [Multi]DiGraph specific */
NX_object* successors_iter(params p); /* [Multi]DiGraph specific */
NX_object* predecessors(params p); /* [Multi]DiGraph specific */
NX_object* predecessors_iter(params p); /* [Multi]DiGraph specific */
NX_object* adjacency_list(params p);
NX_object* adjacency_iter(params p);
NX_object* nbunch_iter(params p);
NX_object* has_node(params p);
NX_object* has_edge(params p);
NX_object* order(params p);
NX_object* degree(params p);
NX_object* degree_iter(params p);
NX_object* in_degree(params p); /* [Multi]DiGraph specific */
NX_object* in_degree_iter(params p); /* [Multi]DiGraph specific */
NX_object* out_degree(params p); /* [Multi]DiGraph specific */
NX_object* out_degree_iter(params p); /* [Multi]DiGraph specific */
NX_object* size(params p);
NX_object* number_of_edges(params p);
NX_object* nodes_with_selfloops(params p);
NX_object* selfloop_edges(params p);
NX_object* number_of_selfloops(params p);
NX_object* copy(params p);
NX_object* to_undirected(params p);
NX_object* to_directed(params p);
NX_object* subgraph(params p);
NX_object* reverse(params p); /* [Multi]DiGraph specific */

/*** NetworkX Algorithms ***/
NX_object* max_clique(params p);
NX_object* clique_removal(params p);
NX_object* min_weighted_dominating_set(params p);
NX_object* min_edge_dominating_set(params p);
NX_object* maximum_independet_set(params p);
NX_object* min_maximal_matching(params p);
NX_object* ramsey_R2(params p);
NX_object* min_weighted_vertex_cover(params p);
NX_object* degree_assortativity_coefficient(params p);
NX_object* attribute_assortativity_coefficient(params p);
NX_object* numeric_assortativity_coefficient(params p);
NX_object* degree_pearson_correlation_coefficient(params p);
NX_object* average_neighbor_degree(params p);
NX_object* average_degree_connectivity(params p);
NX_object* k_nearest_neighbors(params p);
NX_object* attribute_mixing_matrix(params p);
NX_object* degree_mixing_matrix(params p);
NX_object* degree_mixing_dict(params p);
NX_object* attribute_mixing_dict(params p);
NX_object* is_bipartite(params p);
NX_object* is_bipartite_node_set(params p);
NX_object* sets(params p);
NX_object* color(params p);
NX_object* density(params p);
NX_object* degrees(params p);
NX_object* biadjacency_Matrix(params p);
NX_object* projected_graph(params p);
NX_object* weighted_projected_graph(params p);
NX_object* collaboration_weighted_projected_graph(params p);
NX_object* overlap_weighted_projected_graph(params p);
NX_object* generic_weighted_projected_graph(params p);
NX_object* spectral_bipartivity(params p);
NX_object* clustering(params p);
NX_object* redundancy(params p);
NX_object* closeness_centrality(params p);
NX_object* degree_centrality(params p);
NX_object* in_degree_centrality(params p);
NX_object* out_degree_centrality(params p);
NX_object* betweenness_centrality(params p);
NX_object* edge_betweenness_centrality(params p);
NX_object* blockmodel(params p);
NX_object* edge_boundary(params p);
NX_object* node_boundary(params p);
NX_object* current_flow_closeness_centrality(params p);
NX_object* current_flow_betweenness_centrality(params p);
NX_object* edge_current_flow_betweenness_centrality(params p);
NX_object* approximate_current_flow_betweenness_centrality(params p);
NX_object* eigenvector_centrality(params p);
NX_object* eigenvector_centrality_numpy(params p);
NX_object* communicability(params p);
NX_object* communicability_exp(params p);
NX_object* communicability_centrality(params p);
NX_object* communicability_centrality_exp(params p);
NX_object* communicability_betwenness_centrality(params p);
NX_object* estrada_index(params p);
NX_object* load_centrality(params p);
NX_object* edge_load(params p);

NX_object* dijkstra_path(params p);

/*** NetworkX Drawing ***/

#endif //NETWORKX_H
