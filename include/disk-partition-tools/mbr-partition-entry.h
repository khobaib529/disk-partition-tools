#ifndef PARTITION_TOOLS_MBR_PARTITION_ENTRY_H_
#define PARTITION_TOOLS_MBR_PARTITION_ENTRY_H_

#include <cstdint>
#include <iomanip>
#include <ios>
#include <sstream>
#include <string>

#include "disk-partition-tools/utils.h"

// Represents a MBR partition entry. sizeof(MBRPartitionEntry) must be 16 bytes.
class MBRPartitionEntry {
 public:
  // returns a human readable string representation of this classe's internal
  // data

  std::string Repr(int indent_len = 2, int max_key_len = 16) {
    std::ostringstream oss;
    PrintField(oss, "Status: ", GetHexStringFromUint8(GetStatus()), indent_len,
               max_key_len);
    PrintField(oss, "Type: ", GetHexStringFromUint8(GetPartitionType()),
               indent_len, max_key_len);
    PrintField(oss, "Start LBA: ", GetHexStringFromUint32(GetLBAStart()),
               indent_len, max_key_len);
    PrintField(oss,
               "Total Sectors: ", GetHexStringFromUint32(GetTotalSectors()),
               indent_len, max_key_len);
    return oss.str();
  }
  // Getter functions.

  uint8_t GetStatus() { return status_; }
  uint8_t GetStartHead() { return start_head_; }
  uint8_t GetStartSector() { return start_sector_; }
  uint16_t GetStartCylinder() { return start_cylinder_; }
  uint8_t GetPartitionType() { return partition_type_; }
  uint8_t GetEndHead() { return end_head_; }
  uint8_t GetEndSector() { return end_sector_; }
  uint16_t GetEndCylinder() { return end_cylinder_; }
  uint32_t GetLBAStart() { return lba_start_; }
  uint32_t GetTotalSectors() { return total_sectors_; }

 private:
  void PrintField(std::ostringstream& oss, std::string key, std::string value,
                  int indent_len, int max_key_len) {
    oss << std::string(indent_len, ' ') << std::left << std::setw(max_key_len)
        << key << value << std::endl;
  }

 private:
  uint8_t status_;
  uint8_t start_head_;
  uint8_t start_sector_ : 6;
  uint16_t start_cylinder_ : 10;
  uint8_t partition_type_;
  uint8_t end_head_;
  uint8_t end_sector_ : 6;
  uint16_t end_cylinder_ : 10;
  uint32_t lba_start_;
  uint32_t total_sectors_;
} __attribute__((packed));

#endif  // PARTITION_TOOLS_MBR_PARTITION_ENTRY_H_