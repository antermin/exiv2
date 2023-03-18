// SPDX-License-Identifier: GPL-2.0-or-later

/*!
  @author  antermin
  @date    18-Mar-2023, antermin: created
 */
#ifndef JXLIMAGE_HPP_
#define JXLIMAGE_HPP_

// *****************************************************************************
#include "exiv2lib_export.h"

// included header files
#include "image.hpp"

// *****************************************************************************
// namespace extensions
namespace Exiv2 {
// *****************************************************************************
// class definitions

/*!
  @brief Class to access JPEG XL bare codestream. This is just a stub - we only
      read width and height.
*/
class EXIV2API JxlImage : public Image {
 public:
  //! @name Creators
  //@{
  /*!
    @brief Constructor to open a JPEG XL bare codestream. Since the
        constructor can not return a result, callers should check the
        good() method after object construction to determine success
        or failure.
    @param io An auto-pointer that owns a BasicIo instance used for
        reading and writing image metadata. \b Important: The constructor
        takes ownership of the passed in BasicIo instance through the
        auto-pointer. Callers should not continue to use the BasicIo
        instance after it is passed to this method.  Use the Image::io()
        method to get a temporary reference.
   */
  explicit JxlImage(BasicIo::UniquePtr io);
  //@}

  //! @name Manipulators
  //@{
  void readMetadata() override;

  /// @throws Error(ErrorCode::kerWritingImageFormatUnsupported).
  void writeMetadata() override;

  /// @throws Error(ErrorCode::kerInvalidSettingForImage)
  void setExifData(const ExifData& exifData) override;

  /// @throws Error(ErrorCode::kerInvalidSettingForImage)
  void setIptcData(const IptcData& iptcData) override;

  /// @throws Error(ErrorCode::kerInvalidSettingForImage)
  void setComment(const std::string&) override;
  //@}

  //! @name Accessors
  //@{
  [[nodiscard]] std::string mimeType() const override;
  //@}
};  // class JxlImage

// *****************************************************************************
// template, inline and free functions

// These could be static private functions on Image subclasses but then
// ImageFactory needs to be made a friend.
/*!
  @brief Create a new JxlImage instance and return an auto-pointer to it.
         Caller owns the returned object and the auto-pointer ensures that
         it will be deleted.
 */
EXIV2API Image::UniquePtr newJxlInstance(BasicIo::UniquePtr io, bool create);

//! Check if the file iIo is a JPEG XL bare codestream.
EXIV2API bool isJxlType(BasicIo& iIo, bool advance);

}  // namespace Exiv2

#endif  // #ifndef JXLIMAGE_HPP_
