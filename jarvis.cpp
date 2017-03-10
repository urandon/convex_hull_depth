#pragma once

#include <vector>
#include <algorithm>

#include "jarvis.h"


int jarvis_cvxhull_find(const vtype& points, observe_iterator observer_order_begin, observe_iterator observer_order_end)
{
    int hull_len;
    int observer_order_size = observer_order_end - observer_order_begin;
    if (observer_order_size <= 3) {
        return observer_order_size;
    }

    observe_iterator leftmost = observer_order_begin;
    for (observe_iterator tmp = observer_order_begin; tmp != observer_order_end; ++tmp) {
        if (**tmp < **leftmost) {
            leftmost = tmp;
        }
    }
    std::swap(*leftmost, *observer_order_begin);
    hull_len = 1;

    std::vector<pointidxtype>::iterator curr = observer_order_begin;
    while (curr + 1 != observer_order_end)
    {
        std::vector<pointidxtype>::iterator next_candidate = observer_order_begin; // first hull point

        for (auto candidate = curr + 1; candidate != observer_order_end; ++candidate) {
            if (is_more_right_and_closier(**curr, **candidate, **next_candidate)) {
                next_candidate = candidate;
            }
        }

        if (next_candidate == observer_order_begin) { // looped, hull is found
            break;
        } else {
            std::swap(*(curr + 1), *next_candidate);
            curr++;
            hull_len++;
        }
    }

    return hull_len;
}
