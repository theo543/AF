#include "eqsat.cpp"
#include <iostream>

void run_test(const std::vector<std::string> &input) {
    std::cout << "\nRunning test:\n";
    std::cout << "Equations:\n";
    int count = 0;
    for(auto x : input) {
        std::cout << x << '\n';
        count++;
        if(count == 10) {
            std::cout << "...\n";
            break;
        }
    }
    std::cout << "Result: " << Solution::equationsPossible(input) << '\n';
}

int main() {
    run_test({"a==b", "a!=b"});
    run_test({"b==a", "a==b"});
    run_test({"b==a", "b!=a"});
    run_test({"a==b", "b==c", "a==c"});
    run_test({"a==b", "b!=c", "c==a"});
    run_test({"c==c", "b==d", "x!=z"});
    run_test({"a!=a"});
    run_test({"a==b", "b==c", "a==c", "a==d", "b!=d"});
    {
        std::vector<std::string> all_eqs;
        for(char x = 'a';x <= 'z';x++) {
            for(char y = 'a';y <= 'z';y++) {
                if(x != y) {
                    all_eqs.push_back(std::string(1, x) + "==" + std::string(1, y));
                }
            }
        }
        run_test(all_eqs);
        // change all to !=
        for(auto &x : all_eqs) {
            x[1] = '!';
        }
        run_test(all_eqs);
        // now add back in a ==
        all_eqs[30][1] = '=';
        run_test(all_eqs);
    }
}
