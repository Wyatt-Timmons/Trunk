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
 *  MODULE  : Struct definitions                                                 *
 *  DATE    : 2026                                                               *
 *  PURPOSE : Stores the GDT, IDT, and TSS structures                            *
 ********************************************************************************/
#pragma once

#include <macros.h>
#include <types.h>

struct GNU_PACKED Tss
{
    DWORD reserved0;
    QWORD rsp0;
    QWORD rsp1;
    QWORD rsp2;
    QWORD reserved1;
    QWORD ist[7];
    QWORD reserved2;
    WORD reserved3;
    WORD iopb_offset;
};

struct GNU_PACKED TssDescriptor
{
    WORD limit_low;
    WORD base_low;
    BYTE base_middle;

    BYTE type : 4;
    BYTE zero : 1;
    BYTE dpl : 2;
    BYTE p : 1;

    BYTE limit_high : 4;
    BYTE avl : 1;
    BYTE l : 1;
    BYTE db : 1;
    BYTE g : 1;

    BYTE base_high;
    DWORD base_upper;
    DWORD reserved;
};

struct GNU_PACKED GdtEntry
{
    WORD limit_low;
    WORD base_low;
    BYTE base_middle;
    BYTE access;
    BYTE flags_limit_high;
    BYTE base_high;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : Create                                                             *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Creates a new GdtEntry with passed in paramaters                   *
     ********************************************************************************/
    static CONSTEXPR GdtEntry Create(BYTE access, BYTE flags) noexcept
    {
        return GdtEntry{.limit_low        = 0,
                        .base_low         = 0,
                        .base_middle      = 0,
                        .access           = access,
                        .flags_limit_high = static_cast<BYTE>((flags & 0xF0)),
                        .base_high        = 0};
    }
};

struct GNU_PACKED GdtLayout
{
    GdtEntry null_desc;
    GdtEntry kernel_code;
    GdtEntry kernel_data;
    GdtEntry user_code;
    GdtEntry user_data;
    TssDescriptor tss_desc;
};

struct GNU_PACKED GdtPointer
{
    WORD limit;
    ULONG_PTR base;
};

struct GNU_PACKED IdtDescriptor
{
    WORD offset_low;
    WORD segment_selector;

    // clang-format off
        WORD ist_index   : 3;
        WORD reserved_0  : 5;
        WORD gate_type   : 4;
        WORD reserved_1  : 1;
        WORD privilege   : 2;
        WORD present     : 1;
    // clang-format on

    WORD offset_mid;
    DWORD offset_high;

    DWORD reserved_2;
};

struct GNU_PACKED IdtrPointer
{
    WORD limit;
    QWORD base_address;
};
