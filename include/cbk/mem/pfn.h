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
 *  MODULE  : Page frame number                                                  *
 *  DATE    : 2026                                                               *
 *  PURPOSE : Assigns each page(4kb) a unique number for easy tracking.          *
 ********************************************************************************/
#pragma once

#include <macros.h>
#include <types.h>

#include <cbk/mem/page.h>

namespace trunk::mem
{
    inline constexpr SIZE_T BUDDY_MAX_ORDER = 11;

    struct FreeAreaNode
    {
        FreeAreaNode *next;
    };

    struct Page
    {
        BYTE order;
        BOOL is_free;
        FreeAreaNode node;
    };

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : AddrToPfn                                                          *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Shift address to Page frame number                                 *
     ********************************************************************************/
    NO_DISCARD inline constexpr QWORD AddrToPfn(QWORD addr) noexcept
    {
        return addr >> PAGE_SHIFT;
    }

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : PfnToAddr                                                          *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Shift Page frame number to address                                 *
     ********************************************************************************/
    NO_DISCARD inline constexpr QWORD PfnToAddr(QWORD pfn) noexcept
    {
        return pfn << PAGE_SHIFT;
    }
} // namespace trunk::mem