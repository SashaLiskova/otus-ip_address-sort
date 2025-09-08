#include "Ipv4.h"
#include <istream>
#include <vector>

namespace utils
{
std::vector<ipv4::Ipv4> parseAddresses(std::istream &inputstream);
}