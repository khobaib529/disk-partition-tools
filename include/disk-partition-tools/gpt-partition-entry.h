#ifndef PARTITION_TOOLS_GPT_PARTITION_ENTRY_H_
#define PARTITION_TOOLS_GPT_PARTITION_ENTRY_H_
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

#include "disk-partition-tools/efi-guid.h"
class GPTPartitionEntry {
public:
  static std::string PartitionNameToUTF8(const uint16_t *name, size_t len) {
    std::string result;
    for (size_t i = 0; i < len; i++) {
      if (name[i] == 0)
        break; // stop at first null terminator

      char32_t ch = name[i]; // UTF-16 code unit (no surrogate handling for now)

      if (ch < 0x80) {
        // Plain ASCII
        result.push_back(static_cast<char>(ch));
      } else {
        // Non-ASCII chars → mark as '?'
        result.push_back('?');
      }
    }
    return result;
  }
  // return a representation assuming a header is already printed in following
  // format:
  //     std::cout << std::left << std::setw(5) << "Idx" << std::setw(15)
  //     << "Start LBA" << std::setw(15) << "End LBA" << std::setw(12)
  //     << "Attributes" << "Name" << "\n";
  std::string Repr(size_t index) {
    std::ostringstream oss;

    uint16_t namebuf[36];
    memcpy(namebuf, partition_name_, sizeof(namebuf));
    std::string nameutf8 = PartitionNameToUTF8(namebuf, 36);

    oss << std::left << std::setw(5) << index << std::setw(15)
        << GetStartingLBA() << std::setw(15) << GetEndingLBA() << std::setw(12)
        << GetAttributes() << nameutf8;
    return oss.str();
  }

  EFI_GUID GetPartitionTypeGUID() { return partition_type_guid_; }
  EFI_GUID GetUniquePartitionGUID() { return unique_partition_guid_; }
  uint64_t GetStartingLBA() { return starting_lba_; }
  uint64_t GetEndingLBA() { return ending_lba_; }
  uint64_t GetAttributes() { return attributes_; }
  // Getter for partition_name_ is not implemented to avoid accessing packed
  // memeber value warning.

private:
  EFI_GUID partition_type_guid_;
  EFI_GUID unique_partition_guid_;
  uint64_t starting_lba_;
  uint64_t ending_lba_;
  uint64_t attributes_;
  uint16_t partition_name_[36];
} __attribute__((packed));

#endif // PARTITION_TOOLS_GPT_PARTITION_ENTRY_H_