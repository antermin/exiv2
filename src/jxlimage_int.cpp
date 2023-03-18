// SPDX-License-Identifier: GPL-2.0-or-later

#include "jxlimage_int.hpp"

#include "error.hpp"
#include "types.hpp"

#include <cassert>

namespace Exiv2::Internal {

uint64_t JxlStream::getBits(int length) {
  uint64_t bitmask = (1 << length) -1;
  uint64_t value = (databits >> position) & bitmask;
  position += length; //advance position after getting bits
  return value;
}

uint64_t JxlStream::readU32(int c0, int u0, int c1, int u1, int c2, int u2, int c3, int u3) {
  int dist = getBits(2);
  int c[] = {c0, c1, c2, c3};
  int u[] = {u0, u1, u2, u3};
  return c[dist] + getBits(u[dist]);
}

void parseJxlDimensions(JxlStream *stream, bool nosig) {
  // if stream has signature, we need to skip it
  nosig ? stream->position = 0 : stream->position = 16;

  int div8 = stream->getBits(1);
  if (div8) {
      stream->height = (1 + stream->getBits(5)) << 3; // multiply 8
  } else {
      stream->height = stream->readU32(1, 9, 1, 13, 1, 18, 1, 30);
  }
  int ratio = stream->getBits(3);
  if ((div8) && (!ratio)) {
      stream->width = (1 + stream->getBits(5)) << 3; // multiply 8
  } else if (!ratio) {
      stream->width = stream->readU32(1, 9, 1, 13, 1, 18, 1, 30);
  } else {
    switch (ratio) {
      case 1:
        stream->width = stream->height;
        break;
      case 2:
        stream->width = (stream->height * 12) / 10;
        break;
      case 3:
        stream->width = (stream->height * 4) / 3;
        break;
      case 4:
        stream->width = (stream->height * 3) / 2;
        break;
      case 5:
        stream->width = (stream->height * 16) / 9;
        break;
      case 6:
        stream->width = (stream->height * 5) / 4;
        break;
      case 7:
        stream->width = (stream->height * 2);
        break;
    }
  }
}
}  // namespace Exiv2::Internal
