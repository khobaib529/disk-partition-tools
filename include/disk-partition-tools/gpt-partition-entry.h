#ifndef PARTITION_TOOLS_GPT_PARTITION_ENTRY_H_
#define PARTITION_TOOLS_GPT_PARTITION_ENTRY_H_

#include <codecvt>
#include <cstddef>
#include <cstdint>
#include <locale>
#include <sstream>
#include <string>

#include "disk-partition-tools/efi-guid.h"
class GPTPartitionEntry {
 public:
  std::string Repr() {
    std::ostringstream oss;
    oss << "Partition type GUID: " << GetPartitionTypeGUID().Repr() << '\n';
    oss << "Unique partition GUID: " << GetUniquePartitionGUID().Repr() << '\n';
    oss << "Starting LBA: " << GetStartingLBA() << '\n';
    oss << "Ending LBA: " << GetEndingLBA() << '\n';
    oss << "Attributes: " << GetAttributes() << '\n';
    // just prints partition name. I might print it without using deprecated
    // wstring convert.
    std::u16string u16name(partition_name_, partition_name_ + 36);
    // trim trailing nulls
    size_t end = u16name.find(u'\0');
    if (end != std::u16string::npos) u16name.resize(end);
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;

    std::string nameutf8 = convert.to_bytes(u16name);
    oss << "Partition name: " << nameutf8 << '\n';
    return oss.str();
  }
  EFI_GUID GetPartitionTypeGUID() { return partition_type_guid_; }
  EFI_GUID GetUniquePartitionGUID() { return unique_partition_guid_; }
  uint64_t GetStartingLBA() { return starting_lba_; }
  uint64_t GetEndingLBA() { return ending_lba_; }
  uint64_t GetAttributes() { return attributes_; }
  uint16_t* GetPartitionName() { return partition_name_; }

 private:
  EFI_GUID partition_type_guid_;
  EFI_GUID unique_partition_guid_;
  uint64_t starting_lba_;
  uint64_t ending_lba_;
  uint64_t attributes_;
  uint16_t partition_name_[36];
} __attribute__((packed));

#endif  // PARTITION_TOOLS_GPT_PARTITION_ENTRY_H_