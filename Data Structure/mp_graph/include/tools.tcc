/**
 * @file tools.tcc
 * Definition of utility functions on graphs.
 */

#include <limits>
#include <queue>
#include <iostream>


#include "dsets.h"
#include "tools.h"



using namespace std;

namespace cs225
{
namespace tools
{

template <class Graph>
typename Graph::edge_weight_type min_weight_edge(Graph& g)
{
    using weight_t = typename Graph::edge_weight_type;
    weight_t min = std::numeric_limits<weight_t>::max();
    edge min_edge{g.start_vertex(), g.start_vertex()};

    vertex_map<vertex_state> vtx_mark;
    for (const auto& v : g.vertices())
        vtx_mark[v] = vertex_state::UNEXPLORED;
     
    for (const auto& v : g.edges())
         g.edge_label(v, edge_state::UNEXPLORED);
    //vertex u,v;
    std::queue<vertex> q;
    auto start=g.start_vertex();
    q.push(start);
    vtx_mark[start]=vertex_state::VISITED;

    while(!q.empty())
    {
      auto u=q.front();
      q.pop();
     // std::cout
   
      for (const auto& v:g.adjacent(u))
       {
   
         if (vtx_mark[v]==vertex_state::UNEXPLORED)
         {
           vtx_mark[v]=vertex_state::VISITED;
            //g.vertex_label(v,vertex_state::VISITED);
           auto e = g.edge_weight(u, v);
                                if(e < min) {
                                        min = e;
                                        min_edge={u,v};
           }
           g.edge_label(u,v,edge_state::DISCOVERY);
           q.push(v);

         }
         //auto a=(u,v);
         else if (/*edge_mark[a]*/g.edge_label(u,v)==edge_state::UNEXPLORED)
         {
           auto e = g.edge_weight(u, v);
                                if(e < min) {
                                        min = e;
                                        min_edge={u,v};
                                }
 
         

           g.edge_label(u,v,edge_state::CROSS);
         }
       }

    }
    g.edge_label(min_edge, edge_state::MIN);

        return min;

 
    /// @todo your code here
}

template <class Graph>
uint64_t shortest_path_length(Graph& g, vertex start, vertex end)
{
if(g.edges().size() == 0) return 0;
 
     
      vertex_map<vertex_state> vtx_mark;
   for (const auto& v : g.vertices())
         vtx_mark[v]=vertex_state::UNEXPLORED;
    for (const auto& v : g.edges())
         g.edge_label(v, edge_state::UNEXPLORED);
        
 
        queue<vertex> vertexes;
        vertex u = start;
        vtx_mark[u]=vertex_state::VISITED;
        vertexes.push(u);
        vertex_map<vertex> plot;
 
        //vector<vertex> adjacent;
        bool done = false;
 
        while(!vertexes.empty() && !done){
                 u = vertexes.front();
                vertexes.pop();
                //auto adjacent = g.adjacent(v);
                for(const auto& v : g.adjacent(u)/*int i = 0; i < adjacent.size() && !done; i++*/){             
                        if(v == end){
                                done = true;
                        }
                        else if(vtx_mark[v] == vertex_state::UNEXPLORED){
                                g.edge_label(u,v, edge_state::DISCOVERY);
                                vtx_mark[v]=vertex_state::VISITED;
                                //g.vertex_label(v, vertex_state::VISITED);
                                vertexes.push(v);
                               //vertex temp=u; 
                               plot[v] = u;
                        }
                        else if(g.edge_label(u,v) == edge_state::UNEXPLORED)
                                g.edge_label(u,v, edge_state::CROSS);
                }
        }
        int c=1;
        g.edge_label(u ,end, edge_state::CROSS);
        g.edge_label(u ,end, edge_state::MINPATH);
        while(u != start){
                auto a = plot[u];
                g.edge_label(u, a, edge_state::MINPATH);
                u = a;
                c++;
        }
 
        return c;

    /// @todo your code here
}

template <class Graph>
void mark_mst(Graph& g)
{
    for (const auto& e : minimum_spanning_tree(g))
        g.edge_label(e, edge_state::MST);
}

template <class Graph>
edge_set minimum_spanning_tree(const Graph& g)
{
   // sort all the edges
    auto edges = g.edges();
    std::vector<edge> pq{edges.begin(), edges.end()};
    std::sort(pq.begin(), pq.end(), [&](edge e1, edge e2)
    { return g.edge_weight(e1) < g.edge_weight(e2); });
    

     dsets vertices;

    /* queue<edge> temp;
        for (const auto& a : g.edges())
              temp.push(a);*/
        
     
     edge_set edge2;
    auto vertex_list = g.vertices();
    vertices.add_elements(vertex_list.size());


     for (const auto& a : pq)
    {
        //inspect the current edge. if that edge connects two vertices from different sets, union their sets and mark the edge as part of the MST. otherwise do nothing
        //get vertices from this edge
        vertex u = a.source;
        vertex v = a.dest;

        //see if they are from different sets
        if (vertices.find(u) != vertices.find(v))
        {
            //different sets
            //1. Union 
            vertices.merge(u,v);
            //2. mark the edge
            edge b{u,v};
            edge2.insert(b);
            //g.edge_label(u,v,edge_state::MST);
        }
    }
    return edge2;
    /// @todo your code here
}



}
}
