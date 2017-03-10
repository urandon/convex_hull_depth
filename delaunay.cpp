#include "delaunay.h"


CDelanayTriangulation::CDelanayTriangulation(const vtype points_) :
points(points_)
{
    std::make_heap(points.begin(), points.end());
    std::sort_heap(points.begin(), points.end());

}

void CDelanayTriangulation::Init()
{
    triangulate(rangetype(points.begin(), points.end()));
}


const vtype CDelanayTriangulation::get_convex_set() const
{
    return convex_set;
}


// TODO
void CDelanayTriangulation::remove_node(pointidxtype p)
{

}

// TODO
void CDelanayTriangulation::join(rangetype left, rangetype right)
{
    
}

// TODO
void CDelanayTriangulation::add_edge(pointidxtype l, pointidxtype r)
{

}

// TODO
void CDelanayTriangulation::rem_edge(pointidxtype l, pointidxtype r)
{

}


