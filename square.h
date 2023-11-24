#pragma once 

#include <array>


/// @brief класс реализации квадрата
template<std::size_t N> 
class square {
public:
    using value_type = int8_t;
    
    using matrix_t = std::array<value_type, N * N>;

    using iterator = typename matrix_t::iterator;
    
    using const_iterator = typename matrix_t::const_iterator;

    using reverse_iterator = typename matrix_t::reverse_iterator;

    //using const_reverse_iterator = typename matrix_t::const_reverse_iterator;
public: 
    square() {
        std::fill(m_matrix.begin(), m_matrix.end(), 1);
    }
    value_type& operator()(size_t _i, size_t _j) {
        return m_matrix[N * _i + _j]; 
    }

    const value_type& operator()(size_t _i, size_t _j) const {
        return m_matrix[N * _i + _j]; 
    } 

    const value_type& operator()(size_t _i) const {
        return m_matrix[_i]; 
    }

    
    value_type& operator()(size_t _i) {
        return m_matrix[_i]; 
    }

    iterator begin() noexcept {
        return m_matrix.begin();
    } 

    const_iterator begin() const noexcept {
        return m_matrix.cbegin();
    }

    const_iterator cbegin() const noexcept {
        return m_matrix.cbegin();
    }

    iterator end() noexcept {
        return m_matrix.end();
    } 

    const_iterator end() const noexcept {
        return m_matrix.end();
    }

    const_iterator cend() const noexcept {
        return m_matrix.cend();
    }

    reverse_iterator rbegin() noexcept {
        return m_matrix.rbegin();
    }

    reverse_iterator rend() noexcept {
        return m_matrix.rend();
    }

    reverse_iterator rbegin() const noexcept   {
        return m_matrix.rbegin();
    }

    reverse_iterator rend() const noexcept {
        return m_matrix.rend();
    }

    constexpr int size() const noexcept {
        return N * N;
    }


private:
    matrix_t m_matrix;
};


template<std::size_t N>
std::ostream& operator<<(std::ostream& os, const square<N>& sq) {
    for(size_t i = 0; i < N; ++i) {
        for(size_t j = 0; j < N; ++j) {
            os << static_cast<int>(sq(i, j)) << " ";
        }
        os << std::endl;
    }
    os << "-------------------------";
    return os;
}
