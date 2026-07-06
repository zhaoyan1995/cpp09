/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 17:26:10 by yanzhao           #+#    #+#             */
/*   Updated: 2026/07/06 20:55:09 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_ME_HPP
# define PMERGE_ME_HPP

#include <utility>
#include <vector>
#include <deque>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <climits>
#include <iterator>
#include <iomanip>
#include <algorithm>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define VECTOR 1
#define DEQUE 2

class PmergeMe
{
    public:
        PmergeMe(void);
        PmergeMe(int argc);
        PmergeMe(const PmergeMe &src);
        PmergeMe &operator=(const PmergeMe &src);
        ~PmergeMe(void);

        void handle_sort(int argc, char **argv, int con_type);
        void print_sorted_result()const;
        void print_sorting_time()const;
        void print_cmp_nb()const;

        typedef std::pair<int, int> pair;

    private:
        std::vector<std::size_t> _jacob_seq_vec;
        std::deque<std::size_t> _jacob_seq_deq;

        std::vector<int> _raw_vec;
        std::deque<int> _raw_deque;

        std::vector<int> _sorted_vec;
        std::deque<int> _sorted_deque;

        double _time_vector; 
        double _time_deque;

        std::size_t _cmp_vec;
        std::size_t _cmp_deque;

        //PARSE INPUT LOGIC
        void    _parse_input(int argc, char **argv, int con_type);
        bool    _is_digit_str(const std::string &str)const;
        int     _convert_to_int(const std::string &str, int con_type);

        //BUILD JACOB SEQUENCE
        void    _build_jacob_seq(int con_type);

        //VECTOR ALGO LOGIC
        void    _recursive_sort_vec(std::vector<int>& input, int depth);
        //VECTOR ALGO recursive funct
        std::vector<std::pair<int, int> >    _build_pair_vector(std::vector<int>& input, int &odd_number);
        std::vector<int> _build_larger_vec(std::vector<std::pair<int, int> > &pairs); 
        //VECTOR ALGO backtracking funct 
        void    _merge_sort_vec(std::vector<int> &input, std::vector<std::pair<int, int> > pairs, int odd_element); 

        //DEQUE ALGO LOGIC
        void    _recursive_sort_deque(std::deque<int>& input, int depth);
        //DEQUE ALGO recursive funct
        std::deque<std::pair<int, int> >    _build_pair_deque(std::deque<int>& input, int &odd_number);
        std::deque<int> _build_larger_deque(std::deque<std::pair<int, int> > &pairs);
        //DEQUE ALGO backtracking funct
        void    _merge_sort_deque(std::deque<int> &input, std::deque<std::pair<int, int> > pairs, int odd_element);

        template <typename T>
        void _insert_element(T &container, int target , int con_type);

        template <typename T>
        std::size_t _binary_search_index(T &container, std::size_t low, std::size_t high, int target, int con_type);

        template <typename T>
        void      _print_container(const std::string &str, const T &container)const;

        template <typename V, typename U>
        void    _debug_recursive(const std::string &str, int depth, const V &input_con, const U &larger_con)const;

};

#endif

template <typename T>
std::size_t    PmergeMe::_binary_search_index(T &container, std::size_t low, std::size_t high, int target, int con_type)
{
    std::size_t middle;

    while (low < high)
    {
       middle = low + (high - low) / 2; //avoid overflow issue due to addtion op!
       if (target > container[middle])
       {
            low = middle + 1;
       }
       else
       {
            high = middle;
       }
       if (con_type == VECTOR)
            _cmp_vec++;
       else if (con_type == DEQUE)
            _cmp_deque++;
    }
    return (low);
}

template <typename T>
void     PmergeMe::_insert_element(T &container, int target, int con_type)
{
    std::size_t low = 0;
    std::size_t high = container.size();
    std::size_t index_to_insert = _binary_search_index(container, low, high, target, con_type);

    container.insert(container.begin() + index_to_insert, target);
}

template <typename T>
void     PmergeMe::_print_container(const std::string &str, const T &container)const
{
    if (!str.empty())
        std::cout << str;
    for (std::size_t i = 0 ; i < container.size() ; i++)
    {
        std::cout << container[i] << " ";
    }
    std::cout << std::endl;
}

template <typename V, typename U>
void PmergeMe::_debug_recursive(const std::string &str, int depth, const V &input_con, const U &larger_con)const
{
    std::cout << "===========" << str << "===========" << std::endl;
    std::cout << "depth = " << depth << std::endl;
    std::cout << "input address  = " << &input_con << std::endl;
    std::cout << "larger address = " << &larger_con << std::endl;

    _print_container("input : ", input_con);
    _print_container("larger: ", larger_con);
    std::cout << "===========" << str << "===========" << std::endl;
}
