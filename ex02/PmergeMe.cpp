/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 17:26:02 by yanzhao           #+#    #+#             */
/*   Updated: 2026/07/06 22:26:20 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void):
_time_vector(0.0),
_time_deque(0.0),
_cmp_vec(0),
_cmp_deque(0)
{

}

PmergeMe::PmergeMe(const PmergeMe &src):
_jacob_seq_vec(src._jacob_seq_vec),
_jacob_seq_deq(src._jacob_seq_deq),
_raw_vec(src._raw_vec),
_raw_deque(src._raw_deque),
_sorted_vec(src._sorted_vec),
_sorted_deque(src._sorted_deque),
_time_vector(src._time_vector),
_time_deque(src._time_deque),
_cmp_vec(src._cmp_vec),
_cmp_deque(src._cmp_deque)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src)
{
    if (this == &src)
        return (*this);
    _jacob_seq_vec = src._jacob_seq_vec;
    _jacob_seq_deq = src._jacob_seq_deq;
    _raw_vec = src._raw_vec;
    _raw_deque = src._raw_deque;
    _sorted_vec = src._sorted_vec;
    _sorted_deque = src._sorted_deque;
    _time_vector = src._time_vector;
    _time_deque = src._time_deque;
    _cmp_vec = src._cmp_vec;
    _cmp_deque = src._cmp_deque;
    return (*this);
}

PmergeMe::~PmergeMe(void)
{

}

//main handler to execute algo
void PmergeMe::handle_sort(int argc, char **argv, int con_type)
{
    struct timespec start, end;
    long long   diff_time;

    if (con_type == VECTOR)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
        _parse_input(argc, argv, con_type);
        _build_jacob_seq(con_type);
        std::vector<int> input(_raw_vec);
        if (_raw_vec.size() >= 2)
        {
            _recursive_sort_vec(input, 0);
            _sorted_vec = input;
        }
        else
            _sorted_vec = _raw_vec;

        clock_gettime(CLOCK_MONOTONIC, &end);
        diff_time = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
        _time_vector = static_cast<double>(diff_time) / 1000.0;
    }
    else if (con_type == DEQUE)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
        _parse_input(argc, argv, con_type);
        _build_jacob_seq(con_type);

        std::deque<int> input(_raw_deque);
        if (_raw_deque.size() >= 2)
        {
            _recursive_sort_deque(input, 0);
            diff_time = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
            _time_deque = static_cast<double>(diff_time) / 1000.0;

            _sorted_deque = input;
        }
        else
            _sorted_deque = _raw_deque;

        clock_gettime(CLOCK_MONOTONIC, &end);
        diff_time = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
        _time_deque = static_cast<double>(diff_time) / 1000.0;
    }
}

void PmergeMe::print_sorted_result(void)const
{
    std::size_t i = _sorted_vec.size();
    std::size_t j = _sorted_deque.size();

    //if (i != j)
     //   throw std::runtime_error("Error: the size of vector is not equal to the size of deque!");
    for (std::size_t k = 0; k < i; k++) 
    {
      //  if (_sorted_vec[k] != _sorted_deque[k])
       //     throw std::runtime_error("Error: the sorted result is not the same between two different containers!");
       // if (k < _sorted_vec.size() - 1 && _sorted_deque[k] > _sorted_deque[k + 1])
    //         throw std::runtime_error("Error: the result has not been sorted correctly!");
    }
    _print_container("After:  ", _sorted_vec);
    //_print_container("After:  ", _sorted_deque);
}

void PmergeMe::print_sorting_time(void)const
{
    std::cout << "Time to process a range of " << _sorted_vec.size() << " elements with std::[vector] : " << std::fixed << std::setprecision(5) << _time_vector << " us" << std::endl;
    std::cout << "Time to process a range of " << _sorted_deque.size() << " elements with std::[deque]  : " << std::fixed << std::setprecision(5) << _time_deque << " us" << std::endl;
}

void PmergeMe::print_cmp_nb(void)const
{
    std::cout << "Total Comparing frequence(Vector): " << _cmp_vec << std::endl;
    std::cout << "Total Comparing frequence(Deque): " << _cmp_deque << std::endl;
}

//parsing input data, save it into the appropriate container
void PmergeMe::_parse_input(int argc, char **argv, int con_type)
{
    int i = 0;

    if (!argv)
        throw std::runtime_error("Error");
    while (i < argc)
    {
        if (!argv[i])
            return ;
        const std::string &str = argv[i];
        _convert_to_int(argv[i], con_type);
        i++;
    }
}

//build jacob sequence
void PmergeMe::_build_jacob_seq(int con_type)
{
    std::size_t j1 = 1;
    std::size_t j2 = 3;
    std::size_t j3;

    if (con_type == VECTOR)
    {
        _jacob_seq_vec.push_back(j1);
        _jacob_seq_vec.push_back(j2);
        while (_jacob_seq_vec.back() < _raw_vec.size() / 2) 
        {
            j3 = j2 + j1 * 2;
            _jacob_seq_vec.push_back(j3);
            j1 = j2;
            j2 = j3;
        }
        _print_container("JACOB VEC: " , _jacob_seq_vec);
    }
    else if (con_type == DEQUE) 
    {
        _jacob_seq_deq.push_back(j1);
        _jacob_seq_deq.push_back(j2);
        while (_jacob_seq_deq.back() < _raw_deque.size() / 2) 
        {
            j3 = j2 + j1 * 2;
            _jacob_seq_deq.push_back(j3);
            j1 = j2;
            j2 = j3;
        }
        //_print_container("JACOB DEQ: " , _jacob_seq_deq);
    }
}

int PmergeMe::_convert_to_int(const std::string &str, int con_type)
{
    long long tmp_nb;

    if (str.length() > 10)
        throw std::runtime_error("Error");
    if (!_is_digit_str(str))
        throw std::runtime_error("Error");
    tmp_nb = std::atol(str.c_str());
    if (tmp_nb <= 0 || tmp_nb > INT_MAX)
        throw std::runtime_error("Error");

    int num = static_cast<int>(tmp_nb);
    if (con_type == VECTOR)
        _raw_vec.push_back(num);
    else if (con_type == DEQUE)
        _raw_deque.push_back(num);
    return (0);
}

bool PmergeMe::_is_digit_str(const std::string &str)const
{
    for (std::size_t i = 0; i < str.length(); i++)
    {
        if (!std::isdigit(str[i]))
            return (false);
    }
    return (true);
}

//Vector sorting logic
void    PmergeMe::_recursive_sort_vec(std::vector<int> &input, int depth)
{
    int odd_element = -1;
    std::vector<int> larger_vec;

    if (input.size() < 2)
        return ;
 
    std::vector<std::pair<int, int> > pairs = _build_pair_vector(input, odd_element);

    larger_vec = _build_larger_vec(pairs);

    //_debug_recursive("Recursive debug[VECTOR]: ", depth + 1, input, larger_vec);
    _recursive_sort_vec(larger_vec, depth + 1);
    //_debug_recursive("Back_Tracking[VECTOR]: ", depth + 1, input, larger_vec);

    _merge_sort_vec(larger_vec, pairs, odd_element);

    input = larger_vec;
}

//Step 1 of Vector sorting (before recursive)
std::vector<std::pair<int, int> > PmergeMe::_build_pair_vector(std::vector<int> &input, int &odd_number)
{
    std::size_t i = 0;
    std::vector<std::pair<int, int> > pairs;

    if (input.size() % 2)
        odd_number = input.back();
    while (i + 1 < input.size())
    {
        if (input[i] < input[i + 1])
        {
            pairs.push_back(std::make_pair(input[i + 1], input[i]));
        }
        else
        {
            pairs.push_back(std::make_pair(input[i], input[i + 1]));
        }
        _cmp_vec++;
        i += 2;
    }
    return (pairs);
}

//Step 2 of Vector sorting (before recursive)
std::vector<int> PmergeMe::_build_larger_vec(std::vector<std::pair<int, int> > &pairs)
{
    std::vector<int> larger_vec;

    for (std::size_t i = 0; i < pairs.size(); i++)
    {
        larger_vec.push_back(pairs[i].first);
    }
    return (larger_vec);
}

//Step 3 of Vector sorting (after recursive)
void    PmergeMe::_merge_sort_vec(std::vector<int> &input ,std::vector<std::pair <int, int> > pairs, int odd_element)
{
    std::size_t pre_jacob;
    std::size_t jacob;
    std::size_t i;

    _insert_element(input, pairs[0].second, VECTOR);
    pre_jacob = _jacob_seq_vec[0];
    jacob = _jacob_seq_vec[1];
    i = 1;
   std:size_t threshold; 
    std::vector<std::size_t>::const_iterator it = std::lower_bound(_jacob_seq_vec.begin(), _jacob_seq_vec.end(), pairs.size());
    if (it != _jacob_seq_vec.end())
        threshold = it - _jacob_seq_vec.begin();
    else
        threshold = _jacob_seq_vec.back();


//    std::cout << "it value = " << *it << std::endl;
    std::cout << "threshold = " << threshold << std::endl;
//    if (*it > pairs.size())
 //       --threshold;
 
    while (i <= threshold)
    {
        while (jacob > pre_jacob)
        {
            _insert_element(input, pairs[jacob - 1].second, VECTOR);
            jacob--;
        }
        pre_jacob = jacob; 
        i++;
        if (i < _jacob_seq_vec.size())
            jacob = _jacob_seq_vec[i];
        else
            break ;
    }
    if (odd_element > 0)
        _insert_element(input, odd_element, VECTOR);
}

//Step 3 of Vector sorting (after recursive)
/*void    PmergeMe::_merge_sort_vec(std::vector<int> &input ,std::vector<std::pair <int, int> > pairs, int odd_element)
{
    std::size_t pre_jacob;
    std::size_t jacob;
    std::size_t i;

    _insert_element(input, pairs[0].second, VECTOR);
    pre_jacob = _jacob_seq_vec[0];
    jacob = _jacob_seq_vec[1];
    i = 0;
   
    std::vector<std::size_t>::const_iterator it = std::lower_bound(_jacob_seq_vec.begin(), _jacob_seq_vec.end(), pairs.size());
    std::size_t threshold = *it - 1;

    std::size_t k = jacob - 1;

    while (k <= threshold)
    {
        while (k > pre_jacob - 1)
        {
            if (k < pairs.size())
               _insert_element(input, pairs[k].second, VECTOR); 
            k--;
        }
        pre_jacob = jacob;
        i++;
        if (i < _jacob_seq_vec.size())
            jacob = _jacob_seq_vec[i];
        else 
            break ;
        k = jacob - 1;
    }
    if (odd_element > 0)
        _insert_element(input, odd_element, VECTOR);
    
}*/

//Deque sorting logic
void    PmergeMe::_recursive_sort_deque(std::deque<int> &input, int depth)
{
    int odd_element = -1;

    std::deque<int> larger_deque;

    if (input.size() < 2)
        return ;
    std::deque<std::pair<int, int> > pairs = _build_pair_deque(input, odd_element);
    larger_deque = _build_larger_deque(pairs);

    //_debug_recursive("Recursive debug[DEQUE]: ", depth + 1, input, larger_deque);
    _recursive_sort_deque(larger_deque, depth + 1);
    //_debug_recursive("Recursive debug[DEQUE]: ", depth + 1, input, larger_deque);

    _merge_sort_deque(larger_deque, pairs, odd_element);

    input = larger_deque;
}

//Step 1 of Deque sorting (before recursive)
std::deque<std::pair<int, int> > PmergeMe::_build_pair_deque(std::deque<int>& input, int &odd_number)
{
    std::deque<std::pair<int, int> > pairs;
    std::size_t i = 0;

    if (input.size() % 2)
        odd_number = input.back();
    while (i + 1 < input.size())
    {
        if (input[i] < input[i + 1])
        {
            pairs.push_back(std::make_pair(input[i + 1], input[i]));
        }
        else
        {
            pairs.push_back(std::make_pair(input[i], input[i + 1]));
        }
        _cmp_deque++;
        i += 2;
    }
    return (pairs);
}

//Step 2 of Deque sorting (before recursive)
std::deque<int> PmergeMe::_build_larger_deque(std::deque<std::pair<int, int> >& pairs)
{
    std::deque<int> larger_deque;

    for (std::size_t i = 0; i < pairs.size(); i++)
    {
        larger_deque.push_back(pairs[i].first);
    }
    return (larger_deque);
}

//Step 3 of Deque sorting (after recursive)
void    PmergeMe::_merge_sort_deque(std::deque<int> &input, std::deque<std::pair<int, int> > pairs, int odd_element)
{
    std::size_t low;
    std::size_t high;

    for (std::size_t i = 0; i < pairs.size(); i++)
    {
        low = 0;
        high = input.size();
        std::size_t index_to_insert = _binary_search_index(input, low, high, pairs[i].second, DEQUE);
        input.insert(input.begin() + index_to_insert, pairs[i].second);
    }
    if (odd_element != -1)
    {
        low = 0;
        high = input.size();
        std::size_t index_to_insert = _binary_search_index(input, low, high, odd_element, DEQUE);
        input.insert(input.begin() + index_to_insert, odd_element);
    }
}
