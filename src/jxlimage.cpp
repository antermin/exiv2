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
#include "jxlimage_int.hpp"
#include "error.hpp"
#include "futils.hpp"
#include "image.hpp"

// + standard includes
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>

namespace Exiv2
{
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
            Internal::JxlStream jxlstream;
            //! Function used to convert buffer data into 64-bit Integer, information stored in littleEndian format
            jxlstream.databits = 0;
            for(int i = 0; i < 11; ++i){
                jxlstream.databits = jxlstream.databits + static_cast<uint64_t>(data.pData_[i]*(pow(static_cast<float>(256), i)));
            }
            Internal::parseJxlDimensions(&jxlstream, false); // false: !nosig
            pixelHeight_ = jxlstream.height;
            pixelWidth_ = jxlstream.width;
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
