/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 17:25:02 by yanzhao           #+#    #+#             */
/*   Updated: 2026/07/04 17:25:04 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <sstream>
#include <stack>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <climits>

class RPN
{
    public:
        RPN(void);
        RPN(const RPN &src);
        RPN &operator=(const RPN &src);
        ~RPN(void);

        void process_calculation(const std::string &str);
        void print_result()const;

    private:
        std::stack<int>  _st_number;

        void _tokenize_input(const std::string &str);
        void _handle_operation(const std::string &token);

};

#endif
