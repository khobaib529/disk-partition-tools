#ifndef PARTITION_TOOLS_GPT_HEADER_H_
#define PARTITION_TOOLS_GPT_HEADER_H_
#include <cstdint>

#include "disk-partition-tools/efi-guid.h"
class GPTHeader {
 private:
  uint64_t signature_;
  uint32_t revision_;
  uint32_t header_size_;
  uint32_t header_crc32_;
  uint32_t reserved_;
  uint64_t my_lba_;
  uint64_t alternate_lba_;
  uint64_t first_usable_lba_;
  uint64_t last_usable_lba_;
  EFI_GUID disk_guid_;
  uint64_t partition_entry_lba_;
  uint32_t number_of_partition_entries_;
  uint32_t size_of_partition_entry_;
  uint32_t partition_entry_array_crc32_;
  uint8_t reserved_padding_[420];  // padding to fill the 512 byte
} __attribute__((packed));
#endif  // PARTITION_TOOLS_GPT_HEADER_H_