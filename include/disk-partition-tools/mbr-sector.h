#ifndef PARTITION_TOOLS_MBR_SECTOR_H_
#define PARTITION_TOOLS_MBR_SECTOR_H_

#include <cstdint>
#include <cstdio>
#include <ios>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <string>

#include "disk-partition-tools/utils.h"
#include "mbr-partition-entry.h"

class MBRSector {
 public:
  std::string Repr() {
    std::ostringstream oss;
    oss << "Bootsrap code: \n";
    oss << GetHexStringFromUint8Array(bootsrap_code_, 446);
    oss << std::endl;
    for (int i = 0; i < 4; i++) {
      oss << "## Partition " << i << " ##\n";
      oss << partition_table_[i].Repr() << "\n";
    }
    oss << "Boot signature: ";
    oss << GetHexStringFromUint16(GetBootSignature()) << "\n";
    return oss.str();
  }
  uint8_t* GetBootstrapCode() { return bootsrap_code_; }
  uint16_t GetBootSignature() { return boot_signature_; }

 private:
  uint8_t bootsrap_code_[446];
  MBRPartitionEntry partition_table_[4];
  uint16_t boot_signature_;
} __attribute__((packed));

#endif  // PARTITION_TOOLS_MBR_SECTOR_H_