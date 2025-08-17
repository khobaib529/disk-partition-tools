#ifndef PARTITION_TOOLS_GPT_PARTITION_ENTRY_H_
#define PARTITION_TOOLS_GPT_PARTITION_ENTRY_H_

#include <cstdint>

#include "disk-partition-tools/efi-guid.h"
class GPTPartitionEntry {
 private:
  EFI_GUID partition_type_guid_;
  EFI_GUID unique_partition_guid_;
  uint64_t starting_lba_;
  uint64_t ending_lba_;
  uint64_t attributes_;
  uint16_t partition_name_[36];
} __attribute__((packed));

#endif  // PARTITION_TOOLS_GPT_PARTITION_ENTRY_H_