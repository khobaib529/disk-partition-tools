#ifndef PARTITION_TOOLS_UTILS_H_
#define PARTITION_TOOLS_UTILS_H_
#include <cstdint>
#include <string>
// Returns a string representation of uint8_t array
// it add a newline character after printing 16 bytes
std::string GetHexStringFromUint8Array(uint8_t arr[], int n);

std::string GetHexStringFromUint8(uint8_t byte);
std::string GetHexStringFromUint16(uint16_t byte);
std::string GetHexStringFromUint32(uint32_t byte);
#endif
