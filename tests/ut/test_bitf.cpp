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
 *                                                                               *
 *  AUTHOR  : Trollycat                                                          *
 *  MODULE  : Test framework                                                     *
 *  DATE    : 2026                                                               *
 *  PURPOSE : Unit tests for tklib::bitf                                         *
 *                                                                               *
 ********************************************************************************/

#include <gtest/gtest.h>
#include <tklib/ubit/bitf.h>

TEST(Bit, Popcount)
{
    EXPECT_EQ(tklib::popcount(0u), 0u);
    EXPECT_EQ(tklib::popcount(1u), 1u);
    EXPECT_EQ(tklib::popcount(0xFFu), 8u);
    EXPECT_EQ(tklib::popcount(0xFFFFFFFFu), 32u);
    EXPECT_EQ(tklib::popcount(0xFFFFFFFFFFFFFFFFull), 64u);
    EXPECT_EQ(tklib::popcount(0ull), 0u);
    EXPECT_EQ(tklib::popcount(0xAAAAAAAAull), 16u);
}

TEST(Bit, Clz)
{
    EXPECT_EQ(tklib::clz(1u), 31u);
    EXPECT_EQ(tklib::clz(0x80000000u), 0u);
    EXPECT_EQ(tklib::clz(0xFFFFFFFFu), 0u);
    EXPECT_EQ(tklib::clz(1ull), 63u);
    EXPECT_EQ(tklib::clz(0x8000000000000000ull), 0u);
}

TEST(Bit, Ctz)
{
    EXPECT_EQ(tklib::ctz(1u), 0u);
    EXPECT_EQ(tklib::ctz(2u), 1u);
    EXPECT_EQ(tklib::ctz(0x80000000u), 31u);
    EXPECT_EQ(tklib::ctz(1ull), 0u);
    EXPECT_EQ(tklib::ctz(0x8000000000000000ull), 63u);
}

TEST(Bit, BitWidth)
{
    EXPECT_EQ(tklib::bit_width(0u), 0u);
    EXPECT_EQ(tklib::bit_width(1u), 1u);
    EXPECT_EQ(tklib::bit_width(2u), 2u);
    EXPECT_EQ(tklib::bit_width(3u), 2u);
    EXPECT_EQ(tklib::bit_width(4u), 3u);
    EXPECT_EQ(tklib::bit_width(7u), 3u);
    EXPECT_EQ(tklib::bit_width(8u), 4u);
    EXPECT_EQ(tklib::bit_width(0xFFFFFFFFu), 32u);
}

TEST(Bit, BitFloor)
{
    EXPECT_EQ(tklib::bit_floor(0u), 0u);
    EXPECT_EQ(tklib::bit_floor(1u), 1u);
    EXPECT_EQ(tklib::bit_floor(2u), 2u);
    EXPECT_EQ(tklib::bit_floor(3u), 2u);
    EXPECT_EQ(tklib::bit_floor(4u), 4u);
    EXPECT_EQ(tklib::bit_floor(5u), 4u);
    EXPECT_EQ(tklib::bit_floor(8u), 8u);
}

TEST(Bit, BitCeil)
{
    EXPECT_EQ(tklib::bit_ceil(0u), 1u);
    EXPECT_EQ(tklib::bit_ceil(1u), 1u);
    EXPECT_EQ(tklib::bit_ceil(2u), 2u);
    EXPECT_EQ(tklib::bit_ceil(3u), 4u);
    EXPECT_EQ(tklib::bit_ceil(4u), 4u);
    EXPECT_EQ(tklib::bit_ceil(5u), 8u);
    EXPECT_EQ(tklib::bit_ceil(8u), 8u);
    EXPECT_EQ(tklib::bit_ceil(9u), 16u);
}

TEST(Bit, HasSingleBit)
{
    EXPECT_FALSE(tklib::has_single_bit(0u));
    EXPECT_TRUE(tklib::has_single_bit(1u));
    EXPECT_TRUE(tklib::has_single_bit(2u));
    EXPECT_FALSE(tklib::has_single_bit(3u));
    EXPECT_TRUE(tklib::has_single_bit(4096u));
    EXPECT_FALSE(tklib::has_single_bit(4095u));
}

TEST(Bit, TestSetClearToggle)
{
    EXPECT_TRUE(tklib::test_bit(0b1010u, 1u));
    EXPECT_FALSE(tklib::test_bit(0b1010u, 0u));
    EXPECT_TRUE(tklib::test_bit(0b1010u, 3u));

    EXPECT_EQ(tklib::set_bit(0u, 0u), 1u);
    EXPECT_EQ(tklib::set_bit(0u, 3u), 8u);
    EXPECT_EQ(tklib::set_bit(0b1010u, 0u), 0b1011u);

    EXPECT_EQ(tklib::clear_bit(0xFFu, 0u), 0xFEu);
    EXPECT_EQ(tklib::clear_bit(0xFFu, 7u), 0x7Fu);

    EXPECT_EQ(tklib::toggle_bit(0b1010u, 0u), 0b1011u);
    EXPECT_EQ(tklib::toggle_bit(0b1010u, 1u), 0b1000u);
}

TEST(Bit, Rotation)
{
    EXPECT_EQ(tklib::rotl(1u, 1u), 2u);
    EXPECT_EQ(tklib::rotl(1u, 31u), 0x80000000u);
    EXPECT_EQ(tklib::rotl(0x80000000u, 1u), 1u);

    EXPECT_EQ(tklib::rotr(1u, 1u), 0x80000000u);
    EXPECT_EQ(tklib::rotr(2u, 1u), 1u);
    EXPECT_EQ(tklib::rotr(0x80000000u, 31u), 1u);
}

TEST(Bit, Byteswap)
{
    EXPECT_EQ(tklib::byteswap((uint16_t)0x1234u), (uint16_t)0x3412u);
    EXPECT_EQ(tklib::byteswap(0x12345678u), 0x78563412u);
    EXPECT_EQ(tklib::byteswap(0x123456789ABCDEF0ull), 0xF0DEBC9A78563412ull);
}

TEST(Bit, MaskExtractInsert)
{
    EXPECT_EQ(tklib::mask(0u), 0ull);
    EXPECT_EQ(tklib::mask(1u), 1ull);
    EXPECT_EQ(tklib::mask(4u), 0xFull);
    EXPECT_EQ(tklib::mask(8u), 0xFFull);
    EXPECT_EQ(tklib::mask(64u), 0xFFFFFFFFFFFFFFFFull);

    EXPECT_EQ(tklib::extract_bits(0xABCDull, 4u, 4u), 0xCull);
    EXPECT_EQ(tklib::extract_bits(0xABCDull, 0u, 8u), 0xCDull);
    EXPECT_EQ(tklib::extract_bits(0xABCDull, 12u, 4u), 0xAull);

    EXPECT_EQ(tklib::insert_bits(0ull, 0xFull, 4u, 4u), 0xF0ull);
    EXPECT_EQ(tklib::insert_bits(0xFFull, 0x0ull, 4u, 4u), 0x0Full);
    EXPECT_EQ(tklib::insert_bits(0xABCDull, 0x0ull, 4u, 8u), 0xA00Dull);
}