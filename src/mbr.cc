#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include <cstdio>
#include <iostream>
#include <string>

#include "CLI11.h"
#include "disk-partition-tools/mbr-sector.h"

int main(int argc, char* argv[]) {
  CLI::App app{
      "A CLI tool to read MBR formatted disk and format a disk file with MBR."};
  CLI::App* mbr_read =
      app.add_subcommand("read", "Reads MBR sector from a selected drive.");

  std::string file_path;
  mbr_read->add_option("file", file_path, "Disk file to read from.")
      ->required()
      ->check(CLI::ExistingFile);
  CLI11_PARSE(app, argc, argv);
  // Prints MBR contents in a readable format
  if (mbr_read->parsed()) {
    FILE* fp = fopen(file_path.data(), "rb");
    MBRSector mbr_sector;
    fread(&mbr_sector, sizeof(MBRSector), 1, fp);
    std::cout << mbr_sector.Repr();
    fclose(fp);
  }

  return 0;
}
