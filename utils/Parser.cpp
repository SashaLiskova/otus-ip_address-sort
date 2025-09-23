#include "Parser.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace utils
{

std::vector<std::string> split(const std::string &line, const char character)
{
  std::vector<std::string> splitedLine;
  std::string::size_type start = 0;
  std::string::size_type end = line.find_first_of(character);

  while (end != std::string::npos)
  {
    splitedLine.push_back(line.substr(start, end - start));
    start = end + 1;
    end = line.find_first_of(character, start);
  }

  splitedLine.push_back(line.substr(start));
  return splitedLine;
}

std::vector<ipv4::Ipv4> parseAddresses(std::istream &inputstream)
{
  std::vector<ipv4::Ipv4> ipPoll;
  std::string line = "";

  while (std::getline(inputstream, line))
  {
    try
    {
      auto parsedLine = split(line, '\t');
      if (parsedLine.empty())
        throw std::invalid_argument("empty columns");

      ipPoll.emplace_back(ipv4::makeIpv4Address(split(parsedLine.at(0), '.')));
    }
    catch (...)
    {
      continue;
    }
  }

  return ipPoll;
}

} // namespace utils
