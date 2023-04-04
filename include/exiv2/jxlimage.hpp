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
/*!
  @file    jxlimage.hpp
  @brief   JPEG XL (JXL) bare codestream image
  @author  antermin
  @date    09-Mar-2023, antermin: created
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

    // Add JPEG XL (JXL) bare codestream to the supported image formats
    namespace ImageType {
        const int jxl = 25; //!< JPEG XL (JXL) bare codestream image type (see class JxlImage)
        // TODO need to check whether the above is correct
    }

    /*!
      @brief Class to access JPEG XL bare codestream. This is just a stub - we only
          read width and height.
     */
    class EXIV2API JxlImage : public Image {
        //! @name NOT Implemented
        //@{
        //! Copy constructor
        JxlImage(const JxlImage& rhs);
        //! Assignment operator
        JxlImage& operator=(const JxlImage& rhs);
        //@}

    public:
        //! @name Creators
        //@{
        /*!
          @brief Constructor to open a Windows bitmap image. Since the
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
        explicit JxlImage(BasicIo::AutoPtr io);
        //@}

        //! @name Manipulators
        //@{
        void readMetadata();
        /*!
          @brief Todo: Write metadata back to the image. This method is not
              yet(?) implemented. Calling it will throw an Error(kerWritingImageFormatUnsupported).
         */
        void writeMetadata();
        /*!
          @brief Todo: Not supported yet(?). Calling this function will throw
              an instance of Error(kerInvalidSettingForImage).
         */
        void setExifData(const ExifData& exifData);
        /*!
          @brief Todo: Not supported yet(?). Calling this function will throw
              an instance of Error(kerInvalidSettingForImage).
         */
        void setIptcData(const IptcData& iptcData);
        /*!
          @brief Not supported. Calling this function will throw an instance
              of Error(kerInvalidSettingForImage).
         */
        void setComment(const std::string& comment);
        //@}

        //! @name Accessors
        //@{
        std::string mimeType() const;
        //@}

    }; // class JxlImage

// *****************************************************************************
// template, inline and free functions

    // These could be static private functions on Image subclasses but then
    // ImageFactory needs to be made a friend.
    /*!
      @brief Create a new JxlImage instance and return an auto-pointer to it.
             Caller owns the returned object and the auto-pointer ensures that
             it will be deleted.
     */
    EXIV2API Image::AutoPtr newJxlInstance(BasicIo::AutoPtr io, bool create);

    //! Check if the file iIo is a JPEG XL bare codestream image.
    EXIV2API bool isJxlType(BasicIo& iIo, bool advance);

}                                       // namespace Exiv2

#endif                                  // #ifndef JXLIMAGE_HPP_
