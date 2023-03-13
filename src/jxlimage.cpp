// ***************************************************************** -*- C++ -*-
/*
 * Copyright (C) 2004-2023 Exiv2 authors
 * This program is part of the Exiv2 distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, 5th Floor, Boston, MA 02110-1301 USA.
 */
/*
  File:      jxlimage.cpp
  Author(s): antermin
  History:   09-Mar-2023, antermin: created
 */
// *****************************************************************************
// included header files
#include "config.h"

#include "basicio.hpp"
#include "jxlimage.hpp"
#include "error.hpp"
#include "futils.hpp"
#include "image.hpp"

// + standard includes
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>

// *****************************************************************************
namespace {
    class JxlStream {
        public:
            uint64_t databits;
            int position;
            uint64_t getBits(int);
            uint64_t readU32(int, int, int, int, int, int, int, int);
    }; // class JxlStream

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
}

// *****************************************************************************
// class member definitions
namespace Exiv2 {
    namespace Internal {
        //! Function used to convert buffer data into 64-bit Integer, information stored in littleEndian format
        uint64_t getUint64_t_jxl(Exiv2::DataBuf& buf) {
            uint64_t temp = 0;

            for(int i = 0; i < 11; ++i){
                temp = temp + static_cast<uint64_t>(buf.pData_[i]*(pow(static_cast<float>(256), i)));
            }
            return temp;
        }
    }
}
namespace Exiv2
{
    using namespace Exiv2::Internal;

    JxlImage::JxlImage(BasicIo::AutoPtr io) : Image(ImageType::jxl, mdNone, io)
    {
    }

    std::string JxlImage::mimeType() const
    {
        return "image/jxl";
    }

    void JxlImage::setExifData(const ExifData& /*exifData*/)
    {
        // not supported for JXL bare codestream
        throw(Error(kerInvalidSettingForImage, "Exif metadata", "JXL"));
    }

    void JxlImage::setIptcData(const IptcData& /*iptcData*/)
    {
        // not supported for JXL bare codestream
        throw(Error(kerInvalidSettingForImage, "IPTC metadata", "JXL"));
    }

    void JxlImage::setComment(const std::string& /*comment*/)
    {
        // not supported
        throw(Error(kerInvalidSettingForImage, "Image comment", "JXL"));
    }

    void JxlImage::readMetadata()
    {
#ifdef EXIV2_DEBUG_MESSAGES
        std::cerr << "Exiv2::JxlImage::readMetadata: Reading JXL bare codestream file " << io_->path() << "\n";
#endif
        if (io_->open() != 0) {
            throw Error(kerDataSourceOpenFailed, io_->path(), strError());
        }
        IoCloser closer(*io_);
        // Ensure that this is the correct image type
        if (!isJxlType(*io_, false)) {
            if (io_->error() || io_->eof()) throw Error(kerFailedToReadImageData);
            throw Error(kerNotAnImage, "JXL");
        }
        clearMetadata();

        DataBuf data(11); // 11 bytes at most for width and height
        if (io_->read(data.pData_, data.size_)) {
            JxlStream jxlstream;
            jxlstream.databits = getUint64_t_jxl(data);
            jxlstream.position = 16; // skip signature
            
            int div8 = jxlstream.getBits(1);
            if (div8) {
                pixelHeight_ = (1 + jxlstream.getBits(5)) << 3; // multiply 8
            } else {
                pixelHeight_ = jxlstream.readU32(1, 9, 1, 13, 1, 18, 1, 30);
            }
            int ratio = jxlstream.getBits(3);
            if ((div8) && (!ratio)) {
                pixelWidth_ = (1 + jxlstream.getBits(5)) << 3; // multiply 8
            } else if (!ratio) {
                pixelWidth_ = jxlstream.readU32(1, 9, 1, 13, 1, 18, 1, 30);
            } else {
                switch (ratio) {
                    case 1:
                        pixelWidth_ = pixelHeight_;
                        break;
                    case 2:
                        pixelWidth_ = (pixelHeight_ * 12) / 10;
                        break;
                    case 3:
                        pixelWidth_ = (pixelHeight_ * 4) / 3;
                        break;
                    case 4:
                        pixelWidth_ = (pixelHeight_ * 3) / 2;
                        break;
                    case 5:
                        pixelWidth_ = (pixelHeight_ * 16) / 9;
                        break;
                    case 6:
                        pixelWidth_ = (pixelHeight_ * 5) / 4;
                        break;
                    case 7:
                        pixelWidth_ = (pixelHeight_ * 2);
                        break;
                }
            }
        }
    }

    void JxlImage::writeMetadata()
    {
        // Todo: implement me!
        throw(Error(kerWritingImageFormatUnsupported, "JXL"));
    }

    // *************************************************************************
    // free functions
    Image::AutoPtr newJxlInstance(BasicIo::AutoPtr io, bool /*create*/)
    {
        Image::AutoPtr image(new JxlImage(io));
        if (!image->good()) {
            image.reset();
        }
        return image;
    }

    bool isJxlType(BasicIo& iIo, bool advance)
    {
        const int32_t len = 2;
        const unsigned char JxlImageId[2] = { 0xFF, 0x0A };
        byte buf[len];
        iIo.read(buf, len);
        if (iIo.error() || iIo.eof()) {
            return false;
        }
        bool matched = (memcmp(buf, JxlImageId, len) == 0);
        if (!advance || !matched) {
            iIo.seek(-len, BasicIo::cur);
        }
        return matched;
    }
}
