#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

#include "CLI11.h"
#include "disk-partition-tools/gpt-header.h"
#include "disk-partition-tools/gpt-partition-entry.h"

bool AskContinueOnChecksumMismatch() {
  while (true) {
    std::cout << "err: CRC32 checksum doesn't match. Do you want to continue? "
                 "(y/n): ";
    std::string input;
    std::getline(std::cin, input);

    if (input.empty())
      continue; // ignore empty input

    char c = std::tolower(input[0]);
    if (c == 'y')
      return true;
    if (c == 'n')
      return false;

    std::cout << "Please enter y or n.\n";
  }
}

int main(int argc, char **argv) {
  CLI::App app{"A utility to work with gpt disks."};
  CLI::App *gpt_read = app.add_subcommand(
      "read", "read gpt disks and print useful information.");
  std::string file_path;
  gpt_read->add_option("file", file_path, "Disk file to read from.")
      ->required()
      ->check(CLI::ExistingFile);
  CLI11_PARSE(app, argc, argv);
  if (gpt_read->parsed()) {
    FILE *fp = fopen(file_path.data(), "rb");
    if (fp == NULL) {
      perror("Error opening file");
      return EXIT_FAILURE;
    }
    GPTHeader gpt_header;
    int result = fseek(fp, 512, SEEK_SET);
    if (result != 0) {
      perror("Error seeking 512 bytes into file");
      return EXIT_FAILURE;
    }
    result = fread(&gpt_header, 512, 1, fp);
    if (result != 1) {
      perror("Error reading 512 bytes GPT header from file at 512 byte offset");
      return EXIT_FAILURE;
    }
    if (gpt_header.IsVerified()) {
      std::cout << "** Verified integrity with CRC32 checksum **\n";
      std::cout << gpt_header.Repr() << "\n\n\n";
    } else {
      if (!AskContinueOnChecksumMismatch())
        return EXIT_FAILURE;
    }

    GPTPartitionEntry *partition_entries =
        new GPTPartitionEntry[gpt_header.GetNumberOfPartitionEntries()];

    // Read partition entries pointed by gpt header.
    result = fread(reinterpret_cast<char *>(partition_entries),
                   gpt_header.GetSizeOfPartitionEntry(),
                   gpt_header.GetNumberOfPartitionEntries(), fp);
    if (result != gpt_header.GetNumberOfPartitionEntries()) {
      perror("Error reading partition entries");
      return EXIT_FAILURE;
    }
    std::cout << std::left << std::setw(5) << "Idx" << std::setw(15)
              << "Start LBA" << std::setw(15) << "End LBA" << std::setw(12)
              << "Attributes" << "Name" << "\n";
    std::cout << std::string(70, '-') << "\n";
    for (int i = 0; i < gpt_header.GetNumberOfPartitionEntries(); i++) {
      std::cout << partition_entries[i].Repr(i) << "\n";
    }
    fclose(fp);
  }

  return 0;
}
