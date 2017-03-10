#pragma once

#include <vector>
#include <utility>

struct SPoint {
    double x;
    double y;

    friend inline bool operator< (const SPoint& lhs, const SPoint& rhs)
    {
        return (lhs.x != rhs.x) ? (lhs.x < rhs.x) : (lhs.y < rhs.y);
    }

    friend inline bool operator== (const SPoint& lhs, const SPoint& rhs)
    {
        return (lhs.x == rhs.x) && (lhs.y == rhs.y);
    }

    friend inline SPoint operator- (const SPoint& lhs, const SPoint& rhs)
    {
        return{ lhs.x - rhs.x, lhs.y - rhs.y };
    }
};

typedef std::vector<SPoint> vtype;
// these types have the same real type but different semantics
typedef std::pair < vtype::iterator, vtype::iterator > rangetype;
typedef vtype::iterator pointidxtype;
typedef std::pair < pointidxtype, pointidxtype > edgetype;

bool is_more_right(const SPoint& pivot, const SPoint& who, const SPoint& than);
bool is_more_right_and_closier(const SPoint& pivot, const SPoint& who, const SPoint& than);

