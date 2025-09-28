#ifndef PARTITION_TOOLS_GPT_HEADER_H_
#define PARTITION_TOOLS_GPT_HEADER_H_
#include "disk-partition-tools/efi-guid.h"
#include <CRC.h>
#include <cstdint>
#include <ios>
#include <sstream>
#include <string>
class GPTHeader {
public:
  std::string Repr() {
    std::ostringstream oss;
    oss << std::hex << std::showbase;
    oss << "Signature: " << GetSignature() << '\n';
    oss << "Revision: " << GetRevision() << '\n';
    oss << std::dec;
    oss << "Header Size: " << GetHeaderSize() << '\n';
    oss << "Header CRC32: " << std::hex << std::showbase << GetHeaderCRC32()
        << '\n';
    oss << std::dec;
    oss << "Reserved: " << GetReserved() << '\n';
    oss << "MyLBA: " << GetMyLBA() << '\n';
    oss << "Alternate LBA: " << GetAlternateLBA() << '\n';
    oss << "First Usable LBA: " << GetFirstUsabeLBA() << '\n';
    oss << "Last Usable LBA: " << GetLastUsableLBA() << '\n';
    oss << "Disk GUID: " << GetDiskGUID().Repr() << '\n';
    oss << std::dec;
    oss << "Partition Entry LBA: " << GetPartitionEntryLBA() << '\n';
    oss << "Number Of Partition Entries: " << GetNumberOfPartitionEntries()
        << '\n';
    oss << "Size Of Partiton Entry: " << GetSizeOfPartitionEntry() << '\n';
    oss << "Partition Entry Array CRC32: " << std::hex
        << GetPartitionEntryArrayCRC32() << '\n';
    oss << "*** Skipped printing Reserved padding of 420 bytes ***";
    return oss.str();
  }
  uint64_t GetSignature() { return signature_; }
  uint32_t GetRevision() { return revision_; }
  uint32_t GetHeaderSize() { return header_size_; }
  uint32_t GetHeaderCRC32() { return header_crc32_; }
  uint32_t GetReserved() { return reserved_; }
  uint64_t GetMyLBA() { return my_lba_; }
  uint64_t GetAlternateLBA() { return alternate_lba_; }
  uint64_t GetFirstUsabeLBA() { return first_usable_lba_; }
  uint64_t GetLastUsableLBA() { return last_usable_lba_; }
  EFI_GUID GetDiskGUID() { return disk_guid_; }
  uint64_t GetPartitionEntryLBA() { return partition_entry_lba_; }
  uint32_t GetNumberOfPartitionEntries() {
    return number_of_partition_entries_;
  }
  uint32_t GetSizeOfPartitionEntry() { return size_of_partition_entry_; }
  uint32_t GetPartitionEntryArrayCRC32() {
    return partition_entry_array_crc32_;
  }

  bool IsVerified() {
    uint32_t header_crc32 = header_crc32_;
    header_crc32_ = 0;
    std::uint32_t crc = CRC::Calculate(this, header_size_, CRC::CRC_32());
    header_crc32_ = header_crc32;
    return crc == header_crc32;
  }

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
  uint8_t reserved_padding_[420]; // padding to fill the 512 byte
} __attribute__((packed));

static_assert(sizeof(GPTHeader) == 512,
              "GPTHeader class size must be 512 bytes.");

#endif // PARTITION_TOOLS_GPT_HEADER_H_
