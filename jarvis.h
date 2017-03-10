#pragma once

#include <vector>
#include <algorithm>

#include "utils.h"

typedef std::vector<pointidxtype>::iterator observe_iterator;


/***
* modify observer_order due to convex hull observation
* return: number of points in convex hull
*/
int jarvis_cvxhull_find(const vtype& points, observe_iterator observer_order_begin, observe_iterator observer_order_end);
