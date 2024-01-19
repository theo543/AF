#include <fstream>
#include <cstdint>

using i64 = std::uint64_t;

const i64 MOD = 666013;

struct mat {
    i64 arr[3][3];
};

mat mult(const mat &a, const mat &b) {
    mat ret{};
    for(i64 rx = 0;rx < 3;rx++) {
        for(i64 ry = 0;ry < 3;ry++) {
            i64 sum = 0;
            for(i64 i = 0;i < 3;i++) {
                sum += a.arr[rx][i] * b.arr[i][ry];
            }
            ret.arr[rx][ry] = sum % MOD;
        }
    }
    return ret;
}

mat pow(const mat &a, i64 exponent) {
    mat result {{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}};
    mat pow = a;
    while(exponent) {
        if(exponent & 1) {
            result = mult(result, pow);
        }
        pow = mult(pow, pow);
        exponent /= 2;
    }
    return result;
}

int main() {
    std::ifstream in("iepuri.in");
    std::ofstream out("iepuri.out");
    i64 t;
    in >> t;
    while(t--) {
        i64 x, y, z, a, b, c, n;
        in >> x >> y >> z >> a >> b >> c >> n;
        mat eqs = pow({{{0, 1, 0}, {0, 0, 1}, {c, b, a}}}, n);
        i64 answer = eqs.arr[0][0] * x + eqs.arr[0][1] * y + eqs.arr[0][2] * z;
        out << answer % MOD << '\n';
    }
    return 0;
}
