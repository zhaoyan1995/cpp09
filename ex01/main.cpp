/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 17:24:29 by yanzhao           #+#    #+#             */
/*   Updated: 2026/07/04 17:24:32 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    RPN rpn;

    if (argc != 2)
    {
        std::cerr << "We only need one argument." << std::endl;
        return (1);
    }

    const std::string &str(argv[1]);

    try {
        rpn.process_calculation(str);
        rpn.print_result();
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return (1);
    }

    return (0);
}
