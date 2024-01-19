#include <fstream>

using i64 = std::uint64_t;

const i64 SIZE = 20;
const i64 MOD = 1000000000 + 7;

struct mat {
    i64 arr[SIZE][SIZE];
};

const mat id = [](){
    mat id_{};
    for(i64 x = 0;x < SIZE;x++) {
        id_.arr[x][x] = 1;
    }
    return id_;
}();

mat mult(const mat &a, const mat &b) {
    mat ret{};
    for(i64 rx = 0;rx < SIZE;rx++) {
        for(i64 ry = 0;ry < SIZE;ry++) {
            i64 sum = 0;
            for(i64 i = 0;i < SIZE;i++) {
                sum += a.arr[rx][i] * b.arr[i][ry];
            }
            ret.arr[rx][ry] = sum % MOD;
        }
    }
    return ret;
}

int main() {
    std::ifstream in("power.in");
    std::ofstream out("power.out");
    i64 t;
    in >> t;
    while(t--) {
        i64 k, Q, di;
        in >> k >> Q;
        mat bits[64]{};
        int vals[SIZE];
        for(i64 x = 1;x < k;x++) {
            bits[0].arr[x][x - 1] = 1;
        }
        for(i64 x = 0;x < k;x++) {
            in >> bits[0].arr[0][x];
        }
        for(i64 x = 0;x < k;x++) {
            in >> vals[x];
        }
        for(int x = 1;x < 64;x++) {
            bits[x] = mult(bits[x - 1], bits[x - 1]);
        }
        while(Q--) {
            in >> di;
            di--;
            mat m = id;
            int bit = 0;
            while(di) {
                if(di & 1) {
                    m = mult(m, bits[bit]);
                }
                di /= 2;
                bit++;
            }
            i64 result = 0;
            for(i64 x = 0;x < k;x++) {
                result += m.arr[k - 1][x] * vals[k - 1 - x];
                result %= MOD;
            }
            out << result << '\n';
        }
    }
}
