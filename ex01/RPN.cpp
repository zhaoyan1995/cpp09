/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 17:24:46 by yanzhao           #+#    #+#             */
/*   Updated: 2026/07/04 17:24:51 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void)
{

}

RPN::RPN(const RPN &src):
_st_number(src._st_number)
{
}

RPN &RPN::operator=(const RPN &src)
{
    if (this == &src)
        return (*this);
    _st_number = src._st_number;
    return (*this);
}

RPN::~RPN(void)
{

}

void    RPN::process_calculation(const std::string &str)
{
    _tokenize_input(str);
}

void    RPN::print_result()const
{
    std::cout << _st_number.top()  << std::endl;
}

void    RPN::_tokenize_input(const std::string &str)
{
    std::stringstream ss(str);
    std::string token;
 
    while (ss >> token)
    {
        if (token == "+" || token == "-" || token == "/" || token == "*")
        {
            if (_st_number.size() < 2)
                throw std::runtime_error("Error");
            else
                _handle_operation(token);
        }
        else if (token.length() > 2)
            throw std::runtime_error("Error");
        else if (token.length() == 1)
        {
            if (!std::isdigit(token[0]))
                throw std::runtime_error("Error");
            else
                _st_number.push(std::atoi(token.c_str()));
        }
        else
            throw std::runtime_error("Error");
    }
    if (_st_number.size() != 1)
        throw std::runtime_error("Error");
}

void    RPN::_handle_operation(const std::string &token)
{
    int num1 = _st_number.top();
    _st_number.pop();
    int num2 = _st_number.top();
    _st_number.pop();
    long long tmp_result;

    if (token.length() != 1)
        return ;
    char op = token[0];
    switch (op)
    {
        case '+':
            _st_number.push(num2 + num1);
            break ;
        case '-':
            _st_number.push(num2 - num1);
            break ;
        case '*':
            tmp_result = static_cast<long long>(num2) * static_cast<long long>(num1);
            if (tmp_result < INT_MIN || tmp_result > INT_MAX)
                throw std::runtime_error("Error");
            _st_number.push(num2 * num1);
            break ;
        case '/':
            if (num1 == 0)
                throw std::runtime_error("Error");
            _st_number.push(num2 / num1);
            break ;
        default:
            break ;
    }
}
