/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 17:23:19 by yanzhao           #+#    #+#             */
/*   Updated: 2026/07/04 17:23:24 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <cstdio>
#include <iterator>

class BitcoinExchange
{
    public:
        BitcoinExchange(void);
        BitcoinExchange(const BitcoinExchange &src);
        BitcoinExchange &operator=(const BitcoinExchange &src);
        ~BitcoinExchange(void);

        bool    loadOriginData(const std::string &filename);
        bool    handleInputData(const std::string &input_file);

    private:
        std::map<std::string, float> _originData;

        bool    _fillOriginData(const std::string &date, const std::string &exchangeRate);
        bool    _validDate(const std::string& date);
        float    _validInputValue(const std::string& value, const std::string& line);

        float    _validExchangeRate(const std::string& exchangeRate);

        bool _handleInputDataLine(const std::string &date, float value, const std::string &line);
        
        std::string _trim(const std::string& str);

};

#endif
