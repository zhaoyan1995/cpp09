/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 17:25:43 by yanzhao           #+#    #+#             */
/*   Updated: 2026/07/04 17:25:45 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void    print_argv(int argc, char **argv)
{
    if (!argv)
        return ;
    std::cout << "Before: ";
    for (int i = 0; i < argc; i++)
    {
        if (argv[i])
        {
            if (i < argc - 1)
                std::cout << argv[i]  << " ";
            else if (i == argc - 1)
                std::cout << argv[i] << std::endl;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc <= 1)
    {
        std::cerr << "Error: we need more than one argument!" << std::endl;
        return (1);
    }

    argc--;
    argv++;

    PmergeMe pmergeMe;

    try
    {
        pmergeMe.handle_sort(argc, argv, VECTOR);
        pmergeMe.handle_sort(argc, argv, DEQUE);
        print_argv(argc, argv);
        pmergeMe.print_sorted_result();
        pmergeMe.print_sorting_time();
        //pmergeMe.print_cmp_nb();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return (1);
    }
    return (0);
}
