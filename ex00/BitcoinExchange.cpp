/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanzhao <yanzhao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 17:23:34 by yanzhao           #+#    #+#             */
/*   Updated: 2026/07/04 17:48:52 by yanzhao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src):
_originData(src._originData)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
    if (this == &src)
        return (*this);
    _originData = src._originData;
    return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{

}

bool    BitcoinExchange::_validDate(const std::string& str_date) 
{
    int year = 0;
    char dash1 = 0;
    int month = 0;
    char dash2 = 0;
    int date = 0;

    if (str_date.length() != 10)
        return (false);

    int ret = std::sscanf(str_date.c_str(),"%d%c%d%c%d", &year, &dash1, &month, &dash2, &date);

    if (ret != 5 || dash1 != '-' || dash2 != '-')
        return (false);

    if (year < 1000 || year > 9999)
        return (false);

    if (month < 1 || month > 12)
        return (false);

    if (date < 1 || date > 31)
        return (false);

    return (true);
}

float    BitcoinExchange::_validExchangeRate(const std::string& exchangeRate) 
{
    float rate = 0.0f;
    char remain_char = 0;

    int ret = std::sscanf(exchangeRate.c_str(), "%f%c", &rate, &remain_char);

    if (ret != 1)
        return (-1.0f);
    return (rate);
}

bool    BitcoinExchange::loadOriginData(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    
    if (!file.is_open())
    {
        std::cerr << "Error: could not open " << filename << std::endl;
        return (false);
    }

    std::string line;

    while (std::getline(file, line))
    {
        std::string date;
        std::string exchangeRate;
        std::size_t pos;

        if (line.empty()) continue;

        pos = line.find(',');
        if (pos == std::string::npos)
        {
            //std::cerr << "Error: bad input in " << filename << " => \"" << line << "\"" << std::endl; 
            return (false);
        }

        date = line.substr(0, pos);
        exchangeRate = line.substr(pos + 1, line.length() - (pos + 1));

        date = _trim(date);
        exchangeRate = _trim(exchangeRate);

        if (date == "date" && exchangeRate == "exchange_rate")
            continue ;

        if (!_fillOriginData(date, exchangeRate))
            return (false);
    }
    return (true);
}

bool    BitcoinExchange::_fillOriginData(const std::string &date, const std::string &exchangeRate)
{
    if (!_validDate(date))
        return (false);

    float rate = _validExchangeRate(exchangeRate);

    if (rate < 0.0f)
        return (false);

    if (_originData.count(date) > 0)
    {
        //std::cerr << "Error: duplicate data found in " << filename << std::endl;
        return (false);
    }

    _originData[date] = rate;
    return (true);
}

bool    BitcoinExchange::handleInputData(const std::string &input_file)
{
    std::ifstream file(input_file.c_str());

    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return (false);
    }

    std::string line;
   
    while (std::getline(file, line))
    {
        std::string date;
        std::string str_value;
        std::size_t pos;

        if (line.empty()) continue;

        pos = line.find('|');
        date = line.substr(0, pos);
        str_value = line.substr(pos + 1, line.length() - (pos + 1));

        date = _trim(date);
        str_value = _trim(str_value);
        if (date == "date" && str_value == "value")
            continue ;
        if (!_validDate(date))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue ;
        }

        float value = _validInputValue(str_value, line);
        if (value < 0.0f)
            continue ;

        _handleInputDataLine(date, value, line);
    }
    return (true);
}

float    BitcoinExchange::_validInputValue(const std::string& value, const std::string& line)
{
    float rate = 0.0f;
    char remain_char = 0;

    int ret = std::sscanf(value.c_str(), "%f%c", &rate, &remain_char);
    if (ret != 1)
    {
        std::cerr << "Error: bad input => " << line << std::endl;
        return (-1.0f);
    }
    if (rate < 0.0f)
        std::cerr << "Error: Not a positive number." << std::endl;
    else if (rate > 1000.0f)
    {
        std::cerr << "Error: too large a number." << std::endl;
        return (-1.0f);
    }
    return (rate);
}

bool    BitcoinExchange::_handleInputDataLine(const std::string &date, float value, const std::string &line)
{
    float exchange_value;

    if (_originData.count(date) > 0)
    {
        exchange_value = value * _originData[date];
        std::cout << date  << " => " << value << " = " << exchange_value << std::endl;
    }
    else
    {
        std::map<std::string, float>::iterator it = _originData.upper_bound(date);
        if (it == _originData.begin())
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            return (false);
        }
        --it;
        exchange_value = it->second * value;
        std::cout << date  << " => " << value << " = " << exchange_value << std::endl; 
    }
    return (true);
}

std::string BitcoinExchange::_trim(const std::string &str)
{
    std::string whitespace = " \t\r\n";

    std::size_t pos1 = str.find_first_not_of(whitespace);

    if (pos1 == std::string::npos)
        return ("");

    std::size_t pos2 = str.find_last_not_of(whitespace);

    std::string result = str.substr(pos1, pos2 - pos1 + 1);

    return (result);
}
