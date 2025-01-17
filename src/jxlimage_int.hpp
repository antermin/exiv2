// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef JXLIMAGE_INT_HPP
#define JXLIMAGE_INT_HPP

#include <stdint.h>
#include <vector>

namespace Exiv2::Internal {

class JxlStream {
 public:
  uint64_t databits;
  int position;
  uint64_t width;
  uint64_t height;
  uint64_t getBits(int);
  uint64_t readU32(int, int, int, int, int, int, int, int);
}; // class JxlStream

void parseJxlDimensions(JxlStream *stream, bool nosig);

}  // namespace Exiv2::Internal

#endif  // JXLIMAGE_INT_HPP
