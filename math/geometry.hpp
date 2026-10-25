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