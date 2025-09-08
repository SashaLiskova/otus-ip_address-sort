#include "Ipv4.h"
#include "Parser.h"
#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <iterator>

int main()
{
  using namespace ipv4;

  auto ipv4Poll = utils::parseAddresses(std::cin);

  std::sort(ipv4Poll.begin(), ipv4Poll.end(), std::greater<Ipv4>());
  std::copy(ipv4Poll.begin(), ipv4Poll.end(),
            std::ostream_iterator<Ipv4>(std::cout, "\n"));

  std::copy_if(ipv4Poll.begin(), ipv4Poll.end(),
               std::ostream_iterator<Ipv4>(std::cout, "\n"),
               [](const Ipv4 address)
               { return address.getByte(ipv4::Bytes::FIRST_BYTE) == 1; });

  std::copy_if(ipv4Poll.begin(), ipv4Poll.end(),
               std::ostream_iterator<ipv4::Ipv4>(std::cout, "\n"),
               [](const ipv4::Ipv4 &address)
               {
                 return address.getByte(Bytes::FIRST_BYTE) == 46 and
                        address.getByte(Bytes::SECOND_BYTE) == 70;
               });

  std::copy_if(ipv4Poll.begin(), ipv4Poll.end(),
               std::ostream_iterator<Ipv4>(std::cout, "\n"),
               [](const Ipv4 &ipv4)
               {
                 const auto &address = ipv4.getAddress();
                 return std::any_of(address.begin(), address.end(),
                                    [](const uint8_t byte)
                                    { return byte == 46; });
               });
}
