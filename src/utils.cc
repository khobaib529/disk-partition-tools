#include "disk-partition-tools/utils.h"

#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

std::string GetHexStringFromUint8Array(uint8_t arr[], int n) {
  std::ostringstream oss;
  for (int i = 0; i < n; i++) {
    oss << "0x" << std::hex << std::uppercase << std::setw(2)
        << std::setfill('0') << static_cast<int>(arr[i]) << " ";
    if ((i + 1) % 16 == 0) {
      oss << "\n";
    }
  }
  return oss.str();
}

std::string GetHexStringFromUint8(uint8_t byte) {
  std::ostringstream oss;
  oss << "0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
      << static_cast<int>(byte);
  return oss.str();
}

std::string GetHexStringFromUint16(uint16_t byte) {
  std::ostringstream oss;
  oss << "0x" << std::hex << std::uppercase << std::setw(4) << std::setfill('0')
      << static_cast<int>(byte);
  return oss.str();
}

std::string GetHexStringFromUint32(uint32_t byte) {
  std::ostringstream oss;
  oss << "0x" << std::hex << std::uppercase << std::setw(8) << std::setfill('0')
      << static_cast<int>(byte);
  return oss.str();
}
