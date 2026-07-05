/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 17:23:45 by yanzhao           #+#    #+#             */
/*   Updated: 2026/07/04 17:34:01 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return (1);
    }

    BitcoinExchange bitcoinCheck;

    if (!bitcoinCheck.loadOriginData("data.csv"))
	return (1);

    const std::string& input_file(argv[1]);

    bitcoinCheck.handleInputData(input_file);

    return (0);
}
