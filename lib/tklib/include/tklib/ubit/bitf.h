/* *******************************************************************************
 *                                                                               *
 *  Copyright 2026 Trollycat                                                     *
 *                                                                               *
 *  Licensed under the Apache License, Version 2.0 (the "License");              *
 *  you may not use this file except in compliance with the License.             *
 *  You may obtain a copy of the License at                                      *
 *                                                                               *
 *      http://www.apache.org/licenses/LICENSE-2.0                               *
 *                                                                               *
 *  Unless required by applicable law or agreed to in writing, software          *
 *  distributed under the License is distributed on an "AS IS" BASIS,            *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.     *
 *  See the License for the specific language governing permissions and          *
 *  limitations under the License.                                               *
 *                                                                               *
 *********************************************************************************
 *  AUTHOR  : Trollycat                                                          *
 *  MODULE  : Standard library utilites                                          *
 *  DATE    : 2026                                                               *
 *  PURPOSE : Bit-based helper functions                                         *
 ********************************************************************************/
#pragma once

#include <macros.h>
#include <types.h>

namespace tklib
{

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : popcount                                                           *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Returns the number of set bits in value.                           *
     ********************************************************************************/
    NO_DISCARD constexpr DWORD popcount(DWORD value) noexcept
    {
        return static_cast<DWORD>(__builtin_popcount(value));
    }

    NO_DISCARD constexpr DWORD popcount(QWORD value) noexcept
    {
        return static_cast<DWORD>(__builtin_popcountll(value));
    }

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : clz                                                                *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Count leading zero bits.                                           *
     ********************************************************************************/
    NO_DISCARD constexpr DWORD clz(DWORD value) noexcept
    {
        return static_cast<DWORD>(__builtin_clz(value));
    }

    NO_DISCARD constexpr DWORD clz(QWORD value) noexcept
    {
        return static_cast<DWORD>(__builtin_clzll(value));
    }

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : ctz                                                                *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Count trailing zero bits.                                          *
     ********************************************************************************/
    NO_DISCARD constexpr DWORD ctz(DWORD value) noexcept
    {
        return static_cast<DWORD>(__builtin_ctz(value));
    }

    NO_DISCARD constexpr DWORD ctz(QWORD value) noexcept
    {
        return static_cast<DWORD>(__builtin_ctzll(value));
    }

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : bit_width                                                          *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Returns the number of bits needed to represent value.              *
     ********************************************************************************/
    NO_DISCARD constexpr DWORD bit_width(DWORD value) noexcept
    {
        return value == 0 ? 0u : 32u - clz(value);
    }

    NO_DISCARD constexpr DWORD bit_width(QWORD value) noexcept
    {
        return value == 0 ? 0u : 64u - clz(value);
    }

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : bit_floor                                                          *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Returns the largest power of two not greater than value.           *
     ********************************************************************************/
    NO_DISCARD constexpr DWORD bit_floor(DWORD value) noexcept
    {
        return value == 0 ? 0u : 1u << (bit_width(value) - 1u);
    }

    NO_DISCARD constexpr QWORD bit_floor(QWORD value) noexcept
    {
        return value == 0 ? 0ull : 1ull << (bit_width(value) - 1u);
    }

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : bit_ceil                                                           *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Returns the smallest power of two not less than value.             *
     ********************************************************************************/
    NO_DISCARD constexpr DWORD bit_ceil(DWORD value) noexcept
    {
        if (value <= 1)
            return 1u;
        return 1u << bit_width(value - 1u);
    }

    NO_DISCARD constexpr QWORD bit_ceil(QWORD value) noexcept
    {
        if (value <= 1)
            return 1ull;
        return 1ull << bit_width(value - 1ull);
    }

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : has_single_bit                                                     *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Returns true if value is a non-zero power of two.                  *
     ********************************************************************************/
    template <typename T> NO_DISCARD constexpr BOOL has_single_bit(T value) noexcept
    {
        return value != 0 && (value & (value - 1)) == 0;
    }

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : test_bit                                                           *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Returns true if bit at position pos is set in value.               *
     ********************************************************************************/
    template <typename T> NO_DISCARD constexpr BOOL test_bit(T value, DWORD pos) noexcept
    {
        return (value >> pos) & T{1};
    }

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : set_bit                                                            *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Returns value with bit at position pos set.                        *
     ********************************************************************************/
    template <typename T> NO_DISCARD constexpr T set_bit(T value, DWORD pos) noexcept
    {
        return value | (T{1} << pos);
    }

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : clear_bit                                                          *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Returns value with bit at position pos cleared.                    *
     ********************************************************************************/
    template <typename T> NO_DISCARD constexpr T clear_bit(T value, DWORD pos) noexcept
    {
        return value & ~(T{1} << pos);
    }

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : toggle_bit                                                         *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Returns value with bit at position pos toggled.                    *
     ********************************************************************************/
    template <typename T> NO_DISCARD constexpr T toggle_bit(T value, DWORD pos) noexcept
    {
        return value ^ (T{1} << pos);
    }

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : rotl                                                               *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Rotate value left by shift bits.                                   *
     ********************************************************************************/
    NO_DISCARD constexpr DWORD rotl(DWORD value, DWORD shift) noexcept
    {
        shift &= 31u;
        return (value << shift) | (value >> (32u - shift));
    }

    NO_DISCARD constexpr QWORD rotl(QWORD value, DWORD shift) noexcept
    {
        shift &= 63u;
        return (value << shift) | (value >> (64u - shift));
    }

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : rotr                                                               *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Rotate value right by shift bits.                                  *
     ********************************************************************************/
    NO_DISCARD constexpr DWORD rotr(DWORD value, DWORD shift) noexcept
    {
        shift &= 31u;
        return (value >> shift) | (value << (32u - shift));
    }

    NO_DISCARD constexpr QWORD rotr(QWORD value, DWORD shift) noexcept
    {
        shift &= 63u;
        return (value >> shift) | (value << (64u - shift));
    }

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : byteswap                                                           *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Reverse the byte order of value.                                   *
     ********************************************************************************/
    NO_DISCARD constexpr WORD byteswap(WORD value) noexcept
    {
        return static_cast<WORD>(__builtin_bswap16(value));
    }

    NO_DISCARD constexpr DWORD byteswap(DWORD value) noexcept
    {
        return __builtin_bswap32(value);
    }

    NO_DISCARD constexpr QWORD byteswap(QWORD value) noexcept
    {
        return __builtin_bswap64(value);
    }

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : mask                                                               *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Returns a QWORD mask with the lowest n bits set.                     *
     ********************************************************************************/
    NO_DISCARD constexpr QWORD mask(DWORD n) noexcept
    {
        return n >= 64 ? ~QWORD{0} : (QWORD{1} << n) - 1;
    }

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : extract_bits                                                       *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Extract a field of width bits starting at bit position pos.        *
     ********************************************************************************/
    NO_DISCARD constexpr QWORD extract_bits(QWORD value, DWORD pos, DWORD width) noexcept
    {
        return (value >> pos) & mask(width);
    }

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : insert_bits                                                        *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Insert field into value at bit position pos with given width.      *
     ********************************************************************************/
    NO_DISCARD constexpr QWORD insert_bits(QWORD value, QWORD field, DWORD pos,
                                           DWORD width) noexcept
    {
        const QWORD m = mask(width);
        return (value & ~(m << pos)) | ((field & m) << pos);
    }

} // namespace tklib