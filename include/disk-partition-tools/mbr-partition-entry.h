#ifndef PARTITION_TOOLS_MBR_PARTITION_ENTRY_H_
#define PARTITION_TOOLS_MBR_PARTITION_ENTRY_H_

#include <cstdint>
#include <iomanip>
#include <ios>
#include <iostream>
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
    PrintField(oss, "Legacy CHS Start: ", GetCHSStartRepr(), indent_len,
               max_key_len);
    PrintField(oss, "Legacy CHS End: ", GetCHSEndRepr(), indent_len,
               max_key_len);
    return oss.str();
  }
  // Getter functions.

  uint8_t GetStatus() { return status_; }
  uint8_t GetStartHead() { return chs_start_[0]; }
  uint8_t GetStartSector() { return chs_start_[1] & 0x3f; }
  uint16_t GetStartCylinder() {
    return ((chs_start_[1] & 0xc0) << 2) | chs_start_[2];
  }

  uint8_t GetEndHead() { return chs_end_[0]; }
  uint8_t GetEndSector() { return chs_end_[1] & 0x3f; }
  uint16_t GetEndCylinder() {
    return ((chs_end_[1] & 0xc0) << 2) | chs_end_[2];
  }

  uint8_t GetPartitionType() { return partition_type_; }
  uint32_t GetLBAStart() { return lba_start_; }
  uint32_t GetTotalSectors() { return total_sectors_; }

 private:
  void PrintField(std::ostringstream& oss, std::string key, std::string value,
                  int indent_len, int max_key_len) {
    std::string indent(indent_len, ' ');
    oss << indent << std::left << std::setw(max_key_len) << key << value
        << '\n';
  }
  std::string GetCHSStartRepr() {
    std::ostringstream oss;
    // since uint8_t is a typedef of unsigned char oss tries to interpret is as
    // ascii characters. but wes want to print number. so we casr is in uit16_t
    // to see sector and head as number.
    oss << "C: " << GetStartCylinder()
        << ", H: " << static_cast<uint16_t>(GetStartHead())
        << ", S: " << static_cast<uint16_t>(GetStartSector());
    return oss.str();
  }

  std::string GetCHSEndRepr() {
    std::ostringstream oss;
    // since uint8_t is a typedef of unsigned char oss tries to interpret is as
    // ascii characters. but wes want to print number. so we casr is in uit16_t
    // to see sector and head as number.
    oss << "C: " << GetEndCylinder()
        << ", H: " << static_cast<uint16_t>(GetEndHead())
        << ", S: " << static_cast<uint16_t>(GetEndSector());
    return oss.str();
  }

 private:
  uint8_t status_;
  uint8_t chs_start_[3];
  uint8_t partition_type_;
  uint8_t chs_end_[3];
  uint32_t lba_start_;
  uint32_t total_sectors_;
} __attribute__((packed));

#endif  // PARTITION_TOOLS_MBR_PARTITION_ENTRY_H_