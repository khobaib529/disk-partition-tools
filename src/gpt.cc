#include <cstdint>
#include <cstdio>
#include <iostream>

#include "CLI11.h"
#include "disk-partition-tools/gpt-header.h"
#include "disk-partition-tools/gpt-partition-entry.h"

int main(int argc, char** argv) {
  CLI::App app{"A utility to work with gpt disks."};
  CLI::App* gpt_read = app.add_subcommand(
      "read", "read gpt disks and print useful information.");
  std::string file_path;
  gpt_read->add_option("file", file_path, "Disk file to read from.")
      ->required()
      ->check(CLI::ExistingFile);
  CLI11_PARSE(app, argc, argv);
  if (gpt_read->parsed()) {
    FILE* fp = fopen(file_path.data(), "rb");
    GPTHeader gpt_header;
    fseek(fp, 512, SEEK_SET);
    fread(&gpt_header, 512, 1, fp);
    GPTPartitionEntry* partition_entries =
        new GPTPartitionEntry[gpt_header.GetNumberOfPartitionEntries()];
    // Read partition entries pointed by gpt header.
    fread(reinterpret_cast<char*>(partition_entries),
          gpt_header.GetSizeOfPartitionEntry(),
          gpt_header.GetNumberOfPartitionEntries(), fp);
    std::cout << gpt_header.Repr() << "\n\n\n";
    for (int i = 0; i < gpt_header.GetNumberOfPartitionEntries(); i++) {
      std::cout << "## Partition entry " << i << " ##\n";
      std::cout << partition_entries[i].Repr() << "\n\n";
    }
    fclose(fp);
  }
  return 0;
}
