#ifndef PARTITION_TOOLS_EFI_GUID_H_
#define PARTITION_TOOLS_EFI_GUID_H_

#include <cstdint>
class EFI_GUID {
  uint32_t data1;
  uint16_t data2;
  uint16_t data3;
  uint8_t data4[8];
} __attribute__((packed));

#endif  // PARTITION_TOOLS_EFI_GUID_H_