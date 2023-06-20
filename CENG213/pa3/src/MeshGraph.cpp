#include "MeshGraph.h"
#include "BinaryHeap.h"

// For printing
#include <fstream>
#include <iostream>
#include <sstream>

MeshGraph::MeshGraph(const std::vector<Double3>& vertexPositions, const std::vector<IdPair>& edges)
{
    vertices.resize(vertexPositions.size());
    adjList.resize(vertexPositions.size());
    for (long unsigned int i = 0; i < vertexPositions.size(); i++){
        vertices[i].id = i;
        vertices[i].position3D = vertexPositions[i];
    }
    for (std::vector<IdPair>::const_iterator it = edges.begin(); it != edges.end(); ++it){
        adjList[it->vertexId0].push_back(&vertices[it->vertexId1]);
        adjList[it->vertexId1].push_back(&vertices[it->vertexId0]);
    }
} //DONE


double MeshGraph::AverageDistanceBetweenVertices() const
{
    double fin = 0, rtn = 0;
    int cnt = 0;
    for (long unsigned int i = 0; i < vertices.size(); i++){
        for (std::list<Vertex*>::const_iterator itr = adjList[i].begin(); itr != adjList[i].end(); ++itr){
            Vertex* v = *itr;
            fin += Double3::Distance(vertices[i].position3D, v->position3D);
            cnt++;
        }
    }
    rtn = fin/cnt;
    return rtn;
} //DONE


double MeshGraph::AverageEdgePerVertex() const
{
    double ttl = 0, rtn = 0;
    for (long unsigned int i = 0; i < vertices.size(); i++){
        ttl += adjList[i].size();
    }
    rtn = ttl/(vertices.size()*2);
    return rtn;
} //DONE


int MeshGraph::TotalVertexCount() const
{
    return vertices.size();
} //DONE


int MeshGraph::TotalEdgeCount() const
{
    int cnt = 0;
    for (long unsigned int i = 0; i < vertices.size(); i++){
        cnt += adjList[i].size();
    }
    return cnt/2;
} //DONE

int MeshGraph::VertexEdgeCount(int vertexId) const
{
    if (vertexId < 0 || vertexId >= vertices.size()){
        return -1;
    }
    else{
        return adjList[vertexId].size();
    }
} //DONE


void MeshGraph::ImmediateNeighbours(std::vector<int>& outVertexIds,
                                    int vertexId) const
{
    for (std::list<Vertex*>::const_iterator itr = adjList[vertexId].begin(); itr != adjList[vertexId].end(); ++itr){
        outVertexIds.push_back((*itr)->id);
    }
} //DONE

void MeshGraph::PaintInBetweenVertex(std::vector<Color>& outputColorAllVertex,
                                     int vertexIdFrom, int vertexIdTo,
                                     const Color& color) const
{
    outputColorAllVertex.clear();

    if (vertexIdFrom < 0 || vertexIdFrom >= vertices.size() || vertexIdTo < 0 || vertexIdTo >= vertices.size())
    {
        return;
    }
    
    outputColorAllVertex.resize(vertices.size());
    for (int i = 0; i < vertices.size(); i++)
    {
        outputColorAllVertex[i].r = 0;
        outputColorAllVertex[i].g = 0;
        outputColorAllVertex[i].b = 0;
    }

    BinaryHeap heap;
    std::vector<bool> visited(vertices.size(), false);
    std::vector<int> previousVertexId(vertices.size());
    std::vector<double> distances(vertices.size(), INFINITY);
    distances[vertexIdFrom] = 0.0;
    heap.Add(vertexIdFrom, 0.0);
    visited[vertexIdFrom] = true;

    while (heap.HeapSize() > 0)
    {
        int currentVertexId;
        double currentVertexDistance;
        heap.PopHeap(currentVertexId, currentVertexDistance);
        std::vector<int> neighbours;
        ImmediateNeighbours(neighbours, currentVertexId);
        for (std::vector<int>::const_iterator it = neighbours.begin(); it != neighbours.end(); ++it)
        {
            int neighbourId = *it;
            if (!visited[neighbourId])
            {
                double distance = distances[currentVertexId] + Double3::Distance(vertices[currentVertexId].position3D, vertices[neighbourId].position3D);
                distances[neighbourId] = distance;
                heap.Add(neighbourId, distance);
                visited[neighbourId] = true;
                previousVertexId[neighbourId] = currentVertexId;
                
            }
            else{
                double distance = distances[currentVertexId] + Double3::Distance(vertices[currentVertexId].position3D, vertices[neighbourId].position3D);
                if (distances[neighbourId] > distance){
                    distances[neighbourId] = distance;
                    heap.ChangePriority(neighbourId, distance);
                    previousVertexId[neighbourId] = currentVertexId;
                }
            }
        }
    }
    
    int currentVertexId = vertexIdTo;
    while(currentVertexId != vertexIdFrom){
        outputColorAllVertex[currentVertexId] = color;
        currentVertexId = previousVertexId[currentVertexId];
        if(currentVertexId == vertexIdFrom){
            outputColorAllVertex[currentVertexId] = color;
        }
    }
}//DONE

void MeshGraph::PaintInRangeGeodesic(std::vector<Color>& outputColorAllVertex,
                                    int vertexId, const Color& color,
                                    int maxDepth, FilterType type,
                                    double alpha) const
{
outputColorAllVertex.clear();

    if ( vertexId < 0 || vertexId >= vertices.size())
    {
        return;
    }
    
    outputColorAllVertex.resize(vertices.size());
    for (int i = 0; i < vertices.size(); i++)
    {
        outputColorAllVertex[i].r = 0;
        outputColorAllVertex[i].g = 0;
        outputColorAllVertex[i].b = 0;
    }

    BinaryHeap heap;
    std::vector<bool> visited(vertices.size(), false);
    std::vector<double> paint(vertices.size(), INFINITY);
    std::vector<int> path(vertices.size(), -1);
    paint[vertexId] = 0.0;
    heap.Add(vertexId, 0.0);
    visited[vertexId] = true;
    int bas = 0;

    while (heap.HeapSize() > 0)
    {
        int currentVertexId;
        double currentVertexDistance;
        heap.PopHeap(currentVertexId, currentVertexDistance);
        std::vector<int> neighbours;
        ImmediateNeighbours(neighbours, currentVertexId);
        for (std::vector<int>::const_iterator it = neighbours.begin(); it != neighbours.end(); ++it)
        {
            int neighbourId = *it;
            if (!visited[neighbourId])
            {
                double distance = paint[currentVertexId] + 1;
                paint[neighbourId] = distance;
                heap.Add(neighbourId, bas++);
                visited[neighbourId] = true;
               path[neighbourId]=currentVertexId;
            }
            else{
                double distance = paint[currentVertexId] + 1;
                if (paint[neighbourId] > distance){
                    paint[neighbourId] = distance;
                    heap.ChangePriority(neighbourId, bas++);
                    path[neighbourId] = currentVertexId;
                }
            }
        }
    }
    
    for(int i = 0; i < vertices.size(); i++){
        if(paint[i] <= maxDepth){
            double coefficient=0;
            int n=i;
        while(n!=vertexId){
                coefficient += Double3::Distance(vertices[n].position3D, vertices[path[n]].position3D);
                n=path[n];
            }
            
            if(type == FILTER_BOX){
                if(coefficient <= alpha && coefficient >= (-alpha)){
                    outputColorAllVertex[i].r = color.r;
                    outputColorAllVertex[i].g = color.g;
                    outputColorAllVertex[i].b = color.b;
                }
                else{
                    outputColorAllVertex[i].b = 0;
                    outputColorAllVertex[i].r = 0;
                    outputColorAllVertex[i].g = 0;
                }
            }
            else if(type == FILTER_GAUSSIAN){
                double factor = exp((-coefficient*coefficient)/(alpha*alpha));
                short int temp = factor*color.r;
                outputColorAllVertex[i].r = temp;
                temp = factor*color.b;
                outputColorAllVertex[i].b = temp;
                temp = factor*color.g;
                outputColorAllVertex[i].g = temp;
            }
        }
    }
}

void MeshGraph::PaintInRangeEuclidian(std::vector<Color>& outputColorAllVertex,
                                      int vertexId, const Color& color,
                                      int maxDepth, FilterType type,
                                      double alpha) const
{
    outputColorAllVertex.clear();

    if ( vertexId < 0 || vertexId >= vertices.size())
    {
        return;
    }
    
    outputColorAllVertex.resize(vertices.size());
    for (int i = 0; i < vertices.size(); i++)
    {
        outputColorAllVertex[i].r = 0;
        outputColorAllVertex[i].g = 0;
        outputColorAllVertex[i].b = 0;
    }

    BinaryHeap heap;
    std::vector<bool> visited(vertices.size(), false);
    std::vector<double> paint(vertices.size(), INFINITY);
    paint[vertexId] = 0.0;
    heap.Add(vertexId, 0.0);
    visited[vertexId] = true;

    while (heap.HeapSize() > 0)
    {
        int currentVertexId;
        double currentVertexDistance;
        heap.PopHeap(currentVertexId, currentVertexDistance);
        std::vector<int> neighbours;
        ImmediateNeighbours(neighbours, currentVertexId);
        for (std::vector<int>::const_iterator it = neighbours.begin(); it != neighbours.end(); ++it)
        {
            int neighbourId = *it;
            if (!visited[neighbourId])
            {
                double distance = paint[currentVertexId] + 1;
                paint[neighbourId] = distance;
                heap.Add(neighbourId, distance);
                visited[neighbourId] = true;
                
            }
            else{
                double distance = paint[currentVertexId] + 1;
                if (paint[neighbourId] > distance){
                    paint[neighbourId] = distance;
                    heap.ChangePriority(neighbourId, distance);
                }
            }
        }
    }
    
    for(int i = 0; i < vertices.size(); i++){
        if(paint[i] <= maxDepth){
            double coefficient = Double3::Distance(vertices[i].position3D, vertices[vertexId].position3D);
            if(type == FILTER_BOX){
                if(coefficient <= alpha && coefficient >= (-alpha)){
                    outputColorAllVertex[i].r = color.r;
                    outputColorAllVertex[i].g = color.g;
                    outputColorAllVertex[i].b = color.b;
                }
                else{
                    outputColorAllVertex[i].b = 0;
                    outputColorAllVertex[i].r = 0;
                    outputColorAllVertex[i].g = 0;
                }
            }
            else if(type == FILTER_GAUSSIAN){
                double factor = exp((-coefficient*coefficient)/(alpha*alpha));
                short int temp = factor*color.r;
                outputColorAllVertex[i].r = temp;
                temp = factor*color.b;
                outputColorAllVertex[i].b = temp;
                temp = factor*color.g;
                outputColorAllVertex[i].g = temp;
            }
        }
    }
}//DONE

void MeshGraph::WriteColorToFile(const std::vector<Color>& colors,
                                 const std::string& fileName)
{
    // IMPLEMENTED
    std::stringstream s;
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        int r = static_cast<int>(colors[i].r);
        int g = static_cast<int>(colors[i].g);
        int b = static_cast<int>(colors[i].b);

        s << r << ", " << g << ", " << b << "\n";
    }
    std::ofstream f(fileName.c_str());
    f << s.str();
}

void MeshGraph::PrintColorToStdOut(const std::vector<Color>& colors)
{
    // IMPLEMENTED
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        std::cout << static_cast<int>(colors[i].r) << ", "
                  << static_cast<int>(colors[i].g) << ", "
                  << static_cast<int>(colors[i].b) << "\n";
    }
}