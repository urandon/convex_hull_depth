#include "utils.h"


bool is_more_right(const SPoint& pivot, const SPoint& who, const SPoint& than) {
    SPoint va = who - pivot;
    SPoint vb = than - pivot;

    return (va.x * vb.y - va.y * vb.x) >= 0;
}

bool is_more_right_and_closier(const SPoint& pivot, const SPoint& who, const SPoint& than) {
    SPoint va = who - pivot;
    SPoint vb = than - pivot;
    auto vprod = va.x * vb.y - va.y * vb.x;

    if (vprod != 0) {
        return vprod > 0;
    }
    
    // collinear case
    auto sprod = va.x * vb.x + va.y * vb.y;
    if (sprod > 0) { // cooriented
        return abs(va.x) + abs(va.y) <= abs(vb.x) + abs(vb.y);
    } else if (sprod == 0) {
        return true;
    } else {
        // who --- pivot --- than 
        // who is best candidate, who >= start_point
        // the case is possible only if (start, who, pivot) are collinear
        // i.e. 'who' have the same quality as 'start'
        // it means that 'than' not worse
        return true;
    }

    return vprod >= 0;
}
