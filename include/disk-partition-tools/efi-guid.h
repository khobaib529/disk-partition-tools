#ifndef PARTITION_TOOLS_EFI_GUID_H_
#define PARTITION_TOOLS_EFI_GUID_H_

#include <cstdint>
#include <iomanip>
#include <ios>
#include <sstream>
#include <string>
class EFI_GUID {
 public:
  std::string Repr() {
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0');
    oss << std::setw(8) << GetData1() << "-";
    oss << std::setw(4) << GetData2() << "-";
    oss << std::setw(4) << GetData3() << "-";

    oss << std::setw(2) << static_cast<unsigned>(GetData4()[0]) << std::setw(2)
        << static_cast<unsigned>(GetData4()[1]) << "-";
    for (int i = 2; i < 8; i++) {
      oss << std::setw(2) << static_cast<unsigned>(GetData4()[i]);
    }
    return oss.str();
  }

  uint32_t GetData1() { return data1_; }
  uint16_t GetData2() { return data2_; }
  uint16_t GetData3() { return data3_; }
  uint8_t* GetData4() { return data4_; }

 private:
  uint32_t data1_;
  uint16_t data2_;
  uint16_t data3_;
  uint8_t data4_[8];
} __attribute__((packed));

#endif  // PARTITION_TOOLS_EFI_GUID_H_