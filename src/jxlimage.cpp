// SPDX-License-Identifier: GPL-2.0-or-later
/*
  File:      jxlimage.cpp
  Author(s): antermin
  History:   18-Mar-2023, antermin: created
 */

// included header files
#include "jxlimage.hpp"
#include "jxlimage_int.hpp"

#include "config.h"

#include "basicio.hpp"
#include "error.hpp"
#include "futils.hpp"
#include "helper_functions.hpp"
#include "image.hpp"

// + standard includes
#include <cstring>
#include <iostream>
#include <string>

// *****************************************************************************
// class member definitions
namespace Exiv2 {
JxlImage::JxlImage(BasicIo::UniquePtr io) : Image(ImageType::jxl, mdNone, std::move(io)) {
}

std::string JxlImage::mimeType() const {
  return "image/jxl";
}

void JxlImage::setExifData(const ExifData& /*exifData*/) {
  throw(Error(ErrorCode::kerInvalidSettingForImage, "Exif metadata", "JXL"));
}

void JxlImage::setIptcData(const IptcData& /*iptcData*/) {
  throw(Error(ErrorCode::kerInvalidSettingForImage, "IPTC metadata", "JXL"));
}

void JxlImage::setComment(const std::string&) {
  throw(Error(ErrorCode::kerInvalidSettingForImage, "Image comment", "JXL"));
}

void JxlImage::readMetadata() {
#ifdef EXIV2_DEBUG_MESSAGES
  std::cerr << "Exiv2::JxlImage::readMetadata: Reading JXL bare codestream " << io_->path() << "\n";
#endif
  if (io_->open() != 0) {
    throw Error(ErrorCode::kerDataSourceOpenFailed, io_->path(), strError());
  }
  IoCloser closer(*io_);

  // Ensure that this is the correct image type
  if (!isJxlType(*io_, false)) {
    if (io_->error() || io_->eof())
      throw Error(ErrorCode::kerFailedToReadImageData);
    throw Error(ErrorCode::kerNotAnImage, "JXL");
  }
  clearMetadata();

  DataBuf data(11); // Takes up to 11 bytes to parse width and height
  if (io_->read(data.data(), data.size())) {
    Internal::JxlStream jxlstream;
    jxlstream.databits = getUint64_t(data);
    Internal::parseJxlDimensions(&jxlstream, false); // false: !nosig
    pixelHeight_ = jxlstream.height;
    pixelWidth_ = jxlstream.width;
  }
}

void JxlImage::writeMetadata() {
  /// \todo implement me!
  throw(Error(ErrorCode::kerWritingImageFormatUnsupported, "JXL"));
}

// *************************************************************************
// free functions
Image::UniquePtr newJxlInstance(BasicIo::UniquePtr io, bool /*create*/) {
  auto image = std::make_unique<JxlImage>(std::move(io));
  if (!image->good()) {
    return nullptr;
  }
  return image;
}

bool isJxlType(BasicIo& iIo, bool advance) {
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
}  // namespace Exiv2
