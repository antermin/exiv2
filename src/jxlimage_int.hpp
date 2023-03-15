#ifndef JXLIMAGE_INT_HPP
#define JXLIMAGE_INT_HPP

#include <stdint.h>
#include <vector>
#include <cmath>

namespace Exiv2 {
    namespace Internal {
        class JxlStream {
            public:
                uint64_t databits;
                int position;
                uint64_t width;
                uint64_t height;
                uint64_t getBits(int);
                uint64_t readU32(int, int, int, int, int, int, int, int);
        }; // class JxlStream

        void parseJxlDimensions(JxlStream *stream);
    }  // namespace Internal
}  // namespace Exiv2

#endif  // JXLIMAGE_INT_HPP
