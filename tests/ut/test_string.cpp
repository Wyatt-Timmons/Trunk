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
 *  PURPOSE : Unit tests for tklib::string                                       *
 *                                                                               *
 ********************************************************************************/

#include <gtest/gtest.h>
#include <tklib/string.h>

TEST(String, Memcpy)
{
    CHAR dst[16] = {};
    CHAR src[]   = "hello";
    tklib::memcpy(dst, src, 6);
    EXPECT_STREQ(dst, "hello");
}

TEST(String, Memset)
{
    CHAR buf[8] = {};
    tklib::memset(buf, 0xAA, 4);
    EXPECT_EQ((unsigned CHAR)buf[0], 0xAAu);
    EXPECT_EQ((unsigned CHAR)buf[3], 0xAAu);
    EXPECT_EQ((unsigned CHAR)buf[4], 0x00u);
}

TEST(String, Memcmp)
{
    CHAR a[] = "abc";
    CHAR b[] = "abc";
    CHAR c[] = "abd";
    EXPECT_EQ(tklib::memcmp(a, b, 3), 0);
    EXPECT_LT(tklib::memcmp(a, c, 3), 0);
    EXPECT_GT(tklib::memcmp(c, a, 3), 0);
}

TEST(String, Memmove)
{
    CHAR buf[] = "12345678";
    tklib::memmove(buf + 2, buf, 5);
    EXPECT_EQ(buf[2], '1');
    EXPECT_EQ(buf[6], '5');
}

TEST(String, Strlen)
{
    EXPECT_EQ(tklib::strlen(""), 0u);
    EXPECT_EQ(tklib::strlen("hello"), 5u);
    EXPECT_EQ(tklib::strlen("a"), 1u);
}

TEST(String, Strnlen)
{
    EXPECT_EQ(tklib::strnlen("hello", 3u), 3u);
    EXPECT_EQ(tklib::strnlen("hello", 10u), 5u);
    EXPECT_EQ(tklib::strnlen("", 5u), 0u);
}

TEST(String, Strcmp)
{
    EXPECT_EQ(tklib::strcmp("abc", "abc"), 0);
    EXPECT_LT(tklib::strcmp("abc", "abd"), 0);
    EXPECT_GT(tklib::strcmp("abd", "abc"), 0);
    EXPECT_EQ(tklib::strcmp("", ""), 0);
    EXPECT_LT(tklib::strcmp("", "a"), 0);
}

TEST(String, Strncmp)
{
    EXPECT_EQ(tklib::strncmp("abcX", "abcY", 3u), 0);
    EXPECT_NE(tklib::strncmp("abcX", "abcY", 4u), 0);
}

TEST(String, Strcasecmp)
{
    EXPECT_EQ(tklib::strcasecmp("ABC", "abc"), 0);
    EXPECT_EQ(tklib::strcasecmp("Hello", "hello"), 0);
    EXPECT_NE(tklib::strcasecmp("abc", "abd"), 0);
}

TEST(String, Strcpy)
{
    CHAR dst[16] = {};
    tklib::strcpy(dst, "hello");
    EXPECT_STREQ(dst, "hello");
}

TEST(String, Strlcpy)
{
    CHAR dst[4] = {};
    SIZE_T ret  = tklib::strlcpy(dst, "hello", 4u);
    EXPECT_STREQ(dst, "hel");
    EXPECT_EQ(ret, 5u);
}

TEST(String, Strcat)
{
    CHAR dst[16] = "hello";
    tklib::strcat(dst, " world");
    EXPECT_STREQ(dst, "hello world");
}

TEST(String, Strlcat)
{
    CHAR dst[8] = "hi";
    SIZE_T ret  = tklib::strlcat(dst, " world", 8u);
    EXPECT_STREQ(dst, "hi worl");
    EXPECT_EQ(ret, 8u);
}

TEST(String, Strchr)
{
    PCSTR s = "hello";
    EXPECT_EQ(tklib::strchr(s, 'e'), s + 1);
    EXPECT_EQ(tklib::strchr(s, 'z'), nullptr);
    EXPECT_EQ(tklib::strchr(s, 'l'), s + 2);
}

TEST(String, Strrchr)
{
    PCSTR s = "hello";
    EXPECT_EQ(tklib::strrchr(s, 'l'), s + 3);
    EXPECT_EQ(tklib::strrchr(s, 'z'), nullptr);
}

TEST(String, Strstr)
{
    PCSTR s = "hello world";
    EXPECT_EQ(tklib::strstr(s, "world"), s + 6);
    EXPECT_EQ(tklib::strstr(s, "xyz"), nullptr);
    EXPECT_EQ(tklib::strstr(s, ""), s);
}

TEST(String, CharClassification)
{
    EXPECT_TRUE(tklib::is_alpha('a'));
    EXPECT_TRUE(tklib::is_alpha('Z'));
    EXPECT_FALSE(tklib::is_alpha('1'));
    EXPECT_FALSE(tklib::is_alpha(' '));

    EXPECT_TRUE(tklib::is_digit('0'));
    EXPECT_TRUE(tklib::is_digit('9'));
    EXPECT_FALSE(tklib::is_digit('a'));

    EXPECT_TRUE(tklib::is_space(' '));
    EXPECT_TRUE(tklib::is_space('\t'));
    EXPECT_TRUE(tklib::is_space('\n'));
    EXPECT_FALSE(tklib::is_space('a'));

    EXPECT_TRUE(tklib::is_upper('A'));
    EXPECT_FALSE(tklib::is_upper('a'));

    EXPECT_TRUE(tklib::is_lower('a'));
    EXPECT_FALSE(tklib::is_lower('A'));

    EXPECT_TRUE(tklib::is_alnum('a'));
    EXPECT_TRUE(tklib::is_alnum('1'));
    EXPECT_FALSE(tklib::is_alnum(' '));

    EXPECT_TRUE(tklib::is_hex_digit('f'));
    EXPECT_TRUE(tklib::is_hex_digit('F'));
    EXPECT_TRUE(tklib::is_hex_digit('9'));
    EXPECT_FALSE(tklib::is_hex_digit('g'));

    EXPECT_TRUE(tklib::is_print('a'));
    EXPECT_FALSE(tklib::is_print('\n'));
}

TEST(String, CaseConversion)
{
    EXPECT_EQ(tklib::to_upper('a'), 'A');
    EXPECT_EQ(tklib::to_upper('Z'), 'Z');
    EXPECT_EQ(tklib::to_upper('1'), '1');

    EXPECT_EQ(tklib::to_lower('A'), 'a');
    EXPECT_EQ(tklib::to_lower('z'), 'z');
    EXPECT_EQ(tklib::to_lower('1'), '1');
}