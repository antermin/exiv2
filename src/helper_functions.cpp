// ***************************************************************** -*- C++ -*-
/*
 * Copyright (C) 2004-2021 Exiv2 authors
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

#include "helper_functions.hpp"
#include <string.h>

std::string string_from_unterminated(const char* data, size_t data_length)
{
    const size_t StringLength = strnlen(data, data_length);

    return std::string(data, StringLength);
}

uint64_t getUint64_t(Exiv2::DataBuf& buf) {
    uint64_t temp = 0;

    for(size_t i = 0; i < static_cast<size_t>(buf.size_); ++i){
        temp = temp + static_cast<uint64_t>(buf.pData_[i]*(pow(static_cast<float>(256), i)));
    }
    return temp;
}
