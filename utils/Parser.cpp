#include "Parser.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace utils
{

std::string getFirstColumn(const std::string &line)
{
  std::stringstream ss(line);
  std::string token;
  if (std::getline(ss, token, '\t'))
  {
    return line;
  }
  return "";
}

std::vector<ipv4::Ipv4> parseAddresses(std::istream &inputstream)
{

  // input: ip address splitted by /t
  std::vector<ipv4::Ipv4> ipPoll;
  std::string line = "";

  while (std::getline(inputstream, line))
  {
    try
    {
      ipPoll.emplace_back(ipv4::parseStringIntoIpv4(getFirstColumn(line)));
    }
    catch (std::invalid_argument &ex)
    {
      //    std::cerr << line << " will be ignored due to wrong input\n";
    }
  }

  return ipPoll;
}
} // namespace utils