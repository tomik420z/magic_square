#pragma once 
#include "square.h"
#include <unordered_set>

class algorithm_magic_sq {
public:
    template<size_t N>
    static bool is_magic_square_opt(const square<N>& matrix, std::array<bool, (N + 1) * (N + 1)> _digits) {
        static constexpr int _n = N + 1;
        static constexpr int sum = (_n *  (_n * _n + 1)) / 2;
        
        // вычислить диагональ 
        int sm = 0;
        for(size_t i = 0; i < N; ++i) {
            sm += matrix(i, i);
        }
        // угловой элемент 
        int corner_element = sum - sm;
        
        if (1 <= corner_element && corner_element <= _digits.size()) {
            if (!_digits[corner_element - 1]) {
                return false;
            } else {
                _digits[corner_element - 1] = false;
            }
        } else {
            return false;
        }

        std::array<int, N> rows;
        std::array<int, N> cols;

        // сумма по строкам 
        for(size_t i = 0; i < N; ++i) {
            int curr_sum = 0;
            for(size_t j = 0; j < N; ++j) {
                curr_sum += matrix(i, j);
            }

            rows[i] = sum - curr_sum;
            int current_v = rows[i];

            if (1 <= current_v && current_v <= _digits.size()) {
                if (!_digits[current_v - 1]) {
                    return false;
                } else {
                    _digits[current_v - 1] = false;
                }
            } else {
                return false;
            }
        }
            
        // сумма по столбцам  
        for(size_t i = 0; i < N; ++i) {
            int curr_sum = 0;
            for(size_t j = 0; j < N; ++j) {
                curr_sum += matrix(j, i);    
            }

            cols[i] = sum - curr_sum;
            int current_v = cols[i];
            
            if (1 <= current_v && current_v <= _digits.size()) {
                if (!_digits[current_v - 1]) {
                    return false;
                } else {
                    _digits[current_v - 1] = false;
                }
            } else {
                return false;
            }   
        }
        
        int sum_cols = 0;
        int sum_rows = 0;
        // проверить дополнительные столбцы
        for(size_t i = 0; i < N; ++i) {
           sum_cols += cols[i];
           sum_rows += rows[i]; 
        }

        if (sum_cols + corner_element != sum || sum_rows + corner_element != sum) {
            return false;
        }

        int sum_add_diag = cols[0] + rows[0];
        for(std::size_t i = 1; i < N; ++i) {
            sum_add_diag  += matrix(i, N - i);
        }

        return sum_add_diag == sum;
    }

    template<std::size_t N>  
    static bool is_magic_square(const square<N>& matrix) {
        // вычислить сумму главной диаг 
        int val = calc_diagonal(matrix);
        //вычисляить сумму по строкам
        if (!calc<N, true>(matrix, val)) {
            return false;
        }

        // вычислить сумму по столбцам 
        if (!calc<N, false>(matrix, val)) {
            return false;
        }
        // вычислить доп диагональ 
        return calc_add_diagonal(matrix) == val;
    }
private:
    template<std::size_t N>  
    static int calc_diagonal(const square<N>& matrix) {
        int sum = 0;
        for(std::size_t i = 0; i < N; ++i) {
            sum += matrix(i,i);
        }
        return sum;

    }

    template<std::size_t N>  
    static int calc_add_diagonal(const square<N>& matrix) {
        int sum = 0;
        for(std::size_t i = 0; i < N; ++i) {
            sum += matrix(i, N - i - 1);
        }
        return sum;
    }


    template<std::size_t N, bool _calcRow = true>  
    static bool calc(const square<N>& matrix, int _value) {
        
        for(std::size_t i = 0; i < N; ++i) { 
            int sum = 0;
            for(std::size_t j = 0; j < N; ++j) {
                if constexpr (_calcRow) {
                    sum += matrix(i, j);
                } else {
                    sum += matrix(j, i);
                }
            }

            if (sum != _value) {
                return false;
            }
        }

        return true;
    }

};