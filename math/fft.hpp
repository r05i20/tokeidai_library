// https://github.com/r05i20/tokeidai_library/blob/main/math/fft.hpp
using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd>& a, bool inverse)
{
    int n = a.size();

    // 要素数1なら終了
    if (n == 1) return;

    // 偶数番目と奇数番目に分ける
    vector<cd> even(n / 2);
    vector<cd> odd(n / 2);

    for (int i = 0; i < n / 2; i++) {
        even[i] = a[2 * i];
        odd[i] = a[2 * i + 1];
    }

    // 再帰的にFFT
    fft(even, inverse);
    fft(odd, inverse);

    // 1のn乗根
    double angle = 2 * PI / n;
    if (inverse) angle = -angle;

    cd w(1);
    cd wn(cos(angle), sin(angle));

    // 合成
    for (int i = 0; i < n / 2; i++) {
        cd t = w * odd[i];
        a[i] = even[i] + t;
        a[i + n / 2] = even[i] - t;
        w *= wn;
    }

    // 逆FFTの場合
    if (inverse) {
        for (auto& x : a) {
            x /= 2;
        }
    }
}