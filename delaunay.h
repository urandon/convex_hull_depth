#pragma once

#include <vector>
#include <utility>
#include <algorithm>

#include "utils.h"


/**
* The implementation of Kirkpatrick–Seidel algorithm
* "Divide and conqueror" strategy
*/
class CDelanayTriangulation {
public:
    CDelanayTriangulation(const vtype points);
    void Init();
    
    const vtype get_convex_set() const;
    void remove_node(pointidxtype p);


private:
    void triangulate(rangetype range);
    void add_edge(pointidxtype l, pointidxtype r);
    void rem_edge(pointidxtype l, pointidxtype r);
    void join (rangetype left, rangetype right);

private:
    vtype points;
    vtype convex_set;

};




