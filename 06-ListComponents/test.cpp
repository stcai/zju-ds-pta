#include <iostream>
#include <vector>
#include <queue>

class Graph
{
 public:
  typedef int Weight;
  typedef std::vector<Weight>::size_type size_type;
  typedef size_type Vertex;

  class Edge
  {
   public:
    friend std::istream& operator>>(std::istream& in, Edge& e)
    {
      in >> e.v1_ >> e.v2_;
      return in;
    }

    Vertex getV1()const {return v1_;}
    Vertex getV2()const {return v2_;}

   private:
    Vertex v1_;
    Vertex v2_;
  };

  class SearchContext
  {
   public:
    SearchContext(const Graph& g)
        :visitedStatus_(g.vertexNum_)
    {}

    bool isVisited(Vertex v)
    {
      return visitedStatus_[v];
    }

    void setVisited(Vertex v)
    {
      visitedStatus_[v] = true;
    }

   private:
    std::vector<bool> visitedStatus_;
  };

  Graph(size_type vertexNum)
      :vertexNum_(vertexNum)
      ,g_(vertexNum*(vertexNum+1)/2)
  {}

  void insertEdge(const Edge& e);

  void listComponetsByDfs(std::ostream& out, SearchContext& context)const;
  void listComponetsByBfs(std::ostream& out, SearchContext& context)const;

 private:
  static size_type calIndex(Vertex v1, Vertex v2)
  {
    if(v1 < v2)
      return v2*(v2+1)/2 + v1;
    else
      return v1*(v1+1)/2 + v2;
  }

  void bfs(Vertex v, std::ostream& out, SearchContext& context)const;
  void dfs(Vertex v, std::ostream& out, SearchContext& context)const;

  size_type vertexNum_;
  std::vector<Weight> g_;
};

/////////////////////////////////////////////////////////
void Graph::insertEdge(const Edge& e)
{
  size_type index = calIndex(e.getV1(), e.getV2());
  g_[index] = 1;
}

void Graph::listComponetsByDfs(std::ostream& out, SearchContext& context)const
{
  for(Vertex v = 0; v < vertexNum_; ++v)
  {
    if(!context.isVisited(v))
    {
      out << "{ ";
      dfs(v, out, context);
      out << "}" << std::endl;
    }
  }
}

void Graph::listComponetsByBfs(std::ostream& out, SearchContext& context)const
{
  for(Vertex v = 0; v < vertexNum_; ++v)
  {
    if(!context.isVisited(v))
    {
      out << "{ ";
      bfs(v, out, context);
      out << "}" << std::endl;
    }
  }
}

void Graph::dfs(Vertex v, std::ostream& out, SearchContext& context)const
{
  out << v << " ";
  context.setVisited(v);

  for(Vertex w = 0; w < vertexNum_; ++w)
  {
    if(!context.isVisited(w))
    {
      size_type index = calIndex(w, v);
      if(g_[index] != 0)
      {
        dfs(w, out, context);
      }
    }
  }
}

void Graph::bfs(Vertex v, std::ostream& out, SearchContext& context)const
{
  std::queue<Vertex> vertexQueue;
  vertexQueue.push(v);
  while(!vertexQueue.empty())
  {
    v = vertexQueue.front(); vertexQueue.pop();
    if(!context.isVisited(v))
    {
      out << v << " ";
      context.setVisited(v);

      for(Vertex w = 0; w < vertexNum_; ++w)
      {
        if(!context.isVisited(w))
        {
          size_type index = calIndex(w, v);
          if(g_[index] != 0)
            vertexQueue.push(w);
        }
      }
    }
  }
}

/////////////////////////////////////////////////////////
int main()
{
  Graph::size_type vertexNum;
  size_t edgeNum;
  std::cin >> vertexNum >> edgeNum;
  Graph graph(vertexNum);

  Graph::Edge e;
  for(size_t i = 0; i < edgeNum; ++i)
  {
    std::cin >> e;
    graph.insertEdge(e);
  }

  Graph::SearchContext dfsContext(graph);
  graph.listComponetsByDfs(std::cout, dfsContext);
  Graph::SearchContext bfsContext(graph);
  graph.listComponetsByBfs(std::cout, bfsContext);
}
