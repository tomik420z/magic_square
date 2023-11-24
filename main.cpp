#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <cmath>
#include <list>
#include <fstream>
#include <algorithm>

#include <ctime>
#include <cassert>

#include "combination.h"
#include "algotihm_magic_sq.h"
#include "factorial.h"

template<std::size_t _N>
class matrix_enumeration_algorithm {
private:
    static_assert(_N != 0, "bad size magic square");
    static constexpr size_t N = _N - 1;
    static constexpr size_t count_permutation = factorial_v<N * N>;
public:
    matrix_enumeration_algorithm() {}
    ~matrix_enumeration_algorithm() = default;

    std::list<square<N + 1>> alg() {
    
        combinations comb((N + 1) * (N + 1), N * N);
        
        size_t count_thr = std::thread::hardware_concurrency();

        //буффер, куда будут записаны найденные матрицы 
        std::vector<std::list<square<N + 1>>> vec_buffers(count_thr);
        
        while(!comb.completed) {

            std::vector<std::future<void>> vec_thr;
            vec_thr.reserve(count_thr); 
            for(size_t i = 0; i < count_thr && !comb.completed; ++i) {
                vec_thr.emplace_back(std::async(calculate_current_combination, 
                                                this, 
                                                std::ref(vec_buffers[i]),
                                                comb.next() 
                                                )
                                    );
            }

            for(auto& fut : vec_thr) {
                fut.wait();
            }


        }

        return splice_lists(vec_buffers);
    }
private:

    square<N> get_permutation(size_t M) {
        std::vector<int8_t> init_permutation;
        
        init_permutation.reserve(N * N);

        for(size_t i = 1; i <= N * N; ++i) {
            init_permutation.push_back(static_cast<int8_t>(i));
        }

        square<N> result_mx;

        int n = N * N;
        
        for(size_t i = 0; i < N * N; ++i) {
            
            size_t k_i = M / fact(n - 1);
            
            result_mx(i) = init_permutation[k_i];
            
            init_permutation.erase(init_permutation.begin() + k_i);
            
            M = M % fact(n - 1);
            --n;
        }
        return result_mx;
    }   

    void calculate_current_combination(std::list<square<N + 1>>& _li,  
                                      std::vector<long long> currnet_combination) {

        // инициализация квадрата 
        square<N> sq;
        
        for(size_t i = 0; i < currnet_combination.size(); ++i) {
            sq(i) =  currnet_combination[i];
        }

        // инициализация массива 
        std::array<bool, (N + 1) * (N + 1)> array_visited;

        std::fill(array_visited.begin(), array_visited.end(), true);

        for(auto num : sq) {
            array_visited[num - 1] = false;   
        }
        
        for(size_t i = 0; i < count_permutation; ++i) {
            if (auto magic_sq = algorithm_magic_sq::is_magic_square_opt(sq, array_visited); magic_sq) {
                _li.emplace_back(*magic_sq);
            } 

            std::next_permutation(sq.begin(), sq.end());
        }
    }   
    /*
    void calculate_range(size_t _first, size_t _last, 
                        std::list<square<N + 1>>& _li, 
                        std::vector<bool> _visit) {
        
        auto sq = get_permutation(_first);
        
        for(; _first < _last; ++_first)  {
            
            if (algorithm_magic_sq::is_magic_square_opt(sq, _visit)) {
                _li.push_back(square<N>(sq));
            } 

            std::next_permutation(sq.begin(), sq.end());
            
        }
    }*/

    std::list<square<N + 1>> splice_lists(std::vector<std::list<square<N + 1>>>& _vec_buffers) {
        std::list<square<N + 1>> result_li;

        for(auto&& list_squares : _vec_buffers) {
            result_li.splice(result_li.begin(), std::move(list_squares));
        }

        return result_li; 
    }

};

template<size_t N>
void write_file(const std::list<square<N>> & _li)  {
    std::ofstream ofs(std::string("out_" + std::to_string(N) + "x" + std::to_string(N) + ".txt"));

    if (!ofs.is_open()) {
        throw std::string("file not opened");
    }

    for(const auto& sq : _li) {
        ofs << sq << std::endl;
    }

    ofs.close();

}


int main(int argc, char* argv[]) {
    clock_t t1 = clock();
    matrix_enumeration_algorithm<3> enumeration_matrix;
    auto ans = enumeration_matrix.alg();
    clock_t t2 = clock();
    std::cout << "time execution: " << t2 - t1 << " ms" << std::endl;

    write_file(ans);

    std::cout << "size magic square: " << ans.size() << std::endl;
    
    return 0;
}