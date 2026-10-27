// https://github.com/r05i20/tokeidai_library/blob/main/math/geometry.hpp

// (x座標、y座標、半径)
bool circle_cross(tuple<long long, long long ,long long> A, tuple<long long, long long, long long> B)
{
    auto[ax,ay,ar] = A;
    auto[bx,by,br] = B;
    // どちらか一方の円が他方の円の内部または、外部にあるケースはfalse
    long long d = (ax-bx)*(ax-bx) + (ay-by)*(ay-by);
    if(d > (ar+br)*(ar+br) || d < (ar-br)*(ar-br))return false;
    else return true;
}

// 偏角ソート
// まず上下どちらの半平面に属しているかを判定
// 同一平面内の点については外積により順序判定ができる
struct point {int x, y;}

long long cross(const point &a, const point &b) {
    return (long long) a.x * b.y - (long long) a.y * b.x;
}

bool cmp(const point &a, const point &b) {
    int ah = (a.y < 0 or (a.y == 0 and a.x < 0));
    int bh = (b.y < 0 or (b.y == 0 and b.x < 0));
    if (ah != bh) return ah < bh;
    return cross(a, b) > 0;
}

void argument_sort(vector<point> &points) {
    sort(points.begin(), points.end(), cmp);
}