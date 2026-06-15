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
 *  MODULE  : Test framework                                                     *
 *  DATE    : 2026                                                               *
 *  PURPOSE : Unit tests for tklib::math                                         *
 ********************************************************************************/

#include <gtest/gtest.h>
#include <tklib/math.h>

TEST(Math, AlignUp)
{
    EXPECT_EQ(tklib::math::align_up(0u, 4u), 0u);
    EXPECT_EQ(tklib::math::align_up(1u, 4u), 4u);
    EXPECT_EQ(tklib::math::align_up(4u, 4u), 4u);
    EXPECT_EQ(tklib::math::align_up(5u, 4u), 8u);
    EXPECT_EQ(tklib::math::align_up(4095u, 4096u), 4096u);
    EXPECT_EQ(tklib::math::align_up(4096u, 4096u), 4096u);
    EXPECT_EQ(tklib::math::align_up(4097u, 4096u), 8192u);
}

TEST(Math, AlignDown)
{
    EXPECT_EQ(tklib::math::align_down(0u, 4u), 0u);
    EXPECT_EQ(tklib::math::align_down(1u, 4u), 0u);
    EXPECT_EQ(tklib::math::align_down(4u, 4u), 4u);
    EXPECT_EQ(tklib::math::align_down(7u, 4u), 4u);
    EXPECT_EQ(tklib::math::align_down(4097u, 4096u), 4096u);
}

TEST(Math, IsAligned)
{
    EXPECT_TRUE(tklib::math::is_aligned(0u, 4u));
    EXPECT_TRUE(tklib::math::is_aligned(4u, 4u));
    EXPECT_TRUE(tklib::math::is_aligned(4096u, 4096u));
    EXPECT_FALSE(tklib::math::is_aligned(1u, 4u));
    EXPECT_FALSE(tklib::math::is_aligned(4095u, 4096u));
}

TEST(Math, AlignUpPow2)
{
    EXPECT_EQ(tklib::math::align_up_pow2(0ull), 1ull);
    EXPECT_EQ(tklib::math::align_up_pow2(1ull), 1ull);
    EXPECT_EQ(tklib::math::align_up_pow2(2ull), 2ull);
    EXPECT_EQ(tklib::math::align_up_pow2(3ull), 4ull);
    EXPECT_EQ(tklib::math::align_up_pow2(5ull), 8ull);
    EXPECT_EQ(tklib::math::align_up_pow2(16ull), 16ull);
    EXPECT_EQ(tklib::math::align_up_pow2(17ull), 32ull);
}

TEST(Math, IsPowerOfTwo)
{
    EXPECT_FALSE(tklib::math::is_power_of_two(0u));
    EXPECT_TRUE(tklib::math::is_power_of_two(1u));
    EXPECT_TRUE(tklib::math::is_power_of_two(2u));
    EXPECT_TRUE(tklib::math::is_power_of_two(4u));
    EXPECT_TRUE(tklib::math::is_power_of_two(4096u));
    EXPECT_FALSE(tklib::math::is_power_of_two(3u));
    EXPECT_FALSE(tklib::math::is_power_of_two(5u));
    EXPECT_FALSE(tklib::math::is_power_of_two(4095u));
}

TEST(Math, OverflowDetection)
{
    EXPECT_FALSE(tklib::math::add_would_overflow(0ull, 0ull));
    EXPECT_FALSE(tklib::math::add_would_overflow(1ull, 1ull));
    EXPECT_TRUE(tklib::math::add_would_overflow(0xFFFFFFFFFFFFFFFFull, 1ull));
    EXPECT_TRUE(tklib::math::add_would_overflow(0xFFFFFFFFFFFFFFFFull, 0xFFFFFFFFFFFFFFFFull));

    EXPECT_FALSE(tklib::math::mul_would_overflow(0ull, 0ull));
    EXPECT_FALSE(tklib::math::mul_would_overflow(2ull, 4ull));
    EXPECT_TRUE(tklib::math::mul_would_overflow(0xFFFFFFFFFFFFFFFFull, 2ull));
}

TEST(Math, MinMaxClamp)
{
    EXPECT_EQ(tklib::math::min(3, 7), 3);
    EXPECT_EQ(tklib::math::min(7, 3), 3);
    EXPECT_EQ(tklib::math::min(-1, 1), -1);
    EXPECT_EQ(tklib::math::max(3, 7), 7);
    EXPECT_EQ(tklib::math::max(7, 3), 7);
    EXPECT_EQ(tklib::math::max(-1, 1), 1);
    EXPECT_EQ(tklib::math::clamp(5, 0, 10), 5);
    EXPECT_EQ(tklib::math::clamp(-1, 0, 10), 0);
    EXPECT_EQ(tklib::math::clamp(11, 0, 10), 10);
}

TEST(Math, AbsSign)
{
    EXPECT_EQ(tklib::math::abs(0), 0);
    EXPECT_EQ(tklib::math::abs(5), 5);
    EXPECT_EQ(tklib::math::abs(-5), 5);
    EXPECT_EQ(tklib::math::sign(5), 1);
    EXPECT_EQ(tklib::math::sign(-5), -1);
    EXPECT_EQ(tklib::math::sign(0), 0);
}

TEST(Math, IntegerDivision)
{
    EXPECT_EQ(tklib::math::div_round_up(10u, 3u), 4u);
    EXPECT_EQ(tklib::math::div_round_up(9u, 3u), 3u);
    EXPECT_EQ(tklib::math::div_round_up(1u, 3u), 1u);
    EXPECT_EQ(tklib::math::div_round_down(10u, 3u), 3u);
    EXPECT_EQ(tklib::math::div_round_down(9u, 3u), 3u);
    EXPECT_EQ(tklib::math::div_round_nearest(10u, 3u), 3u);
    EXPECT_EQ(tklib::math::div_round_nearest(11u, 3u), 4u);
}

TEST(Math, Log2)
{
    EXPECT_EQ(tklib::math::log2_floor(1ull), 0u);
    EXPECT_EQ(tklib::math::log2_floor(2ull), 1u);
    EXPECT_EQ(tklib::math::log2_floor(3ull), 1u);
    EXPECT_EQ(tklib::math::log2_floor(4ull), 2u);
    EXPECT_EQ(tklib::math::log2_floor(8ull), 3u);
    EXPECT_EQ(tklib::math::log2_floor(15ull), 3u);
    EXPECT_EQ(tklib::math::log2_floor(16ull), 4u);

    EXPECT_EQ(tklib::math::log2_ceil(1ull), 0u);
    EXPECT_EQ(tklib::math::log2_ceil(2ull), 1u);
    EXPECT_EQ(tklib::math::log2_ceil(3ull), 2u);
    EXPECT_EQ(tklib::math::log2_ceil(4ull), 2u);
    EXPECT_EQ(tklib::math::log2_ceil(5ull), 3u);
}

TEST(Math, Log10)
{
    EXPECT_EQ(tklib::math::log10_floor(1ull), 0u);
    EXPECT_EQ(tklib::math::log10_floor(9ull), 0u);
    EXPECT_EQ(tklib::math::log10_floor(10ull), 1u);
    EXPECT_EQ(tklib::math::log10_floor(99ull), 1u);
    EXPECT_EQ(tklib::math::log10_floor(100ull), 2u);
}

TEST(Math, Pow)
{
    EXPECT_EQ(tklib::math::pow(2u, 0u), 1u);
    EXPECT_EQ(tklib::math::pow(2u, 1u), 2u);
    EXPECT_EQ(tklib::math::pow(2u, 8u), 256u);
    EXPECT_EQ(tklib::math::pow(2u, 10u), 1024u);
    EXPECT_EQ(tklib::math::pow(3u, 3u), 27u);
    EXPECT_EQ(tklib::math::pow(10u, 3u), 1000u);
}