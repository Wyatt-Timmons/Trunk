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
 *  MODULE  : Memblock                                                           *
 *  DATE    : 2026                                                               *
 *  PURPOSE : Early boot-stage allocator, PFN is not available at this time      *
 ********************************************************************************/
#pragma once

#include <types.h>

#include <boot/trldr/mb2/boot.h>

#include <cbk/mem/mmarch.h>

// Memblock is used when we're in early boot-stage, and need to allocate some space to startup the
// advanced memory management system.
// For example, the PFN database needs an allocated spot in memory for it's structures
// After the system is allocated and setup, memblock is discarded and never used again
// Think of it like the 'initramfs' of memory management

// DOES NOT SUPPORT TABLE:
//        Hotplugging RAM
//        NUMA CPU node ID
//        Mirrored memory
//        Nomap for ARM

// Hotplugging RAM - support in the far future
// NUMA CPU node ID - support after scheduling
// Mirrored memory - support after scheduling
// Nomap from ARM - don't support, x86 only os

namespace cbk::mem
{
    struct BootAllocation
    {
        QWORD phys_addr;
        QWORD size;
        BOOL is_free;
    };

    using BOOT_ALLOCATION = BootAllocation;

    INLINE_CONST WORD BOOT_BLOCKS_SIZE = 32;

    extern BOOT_ALLOCATION boot_blocks[];
    extern DWORD boot_blocks_count;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockInitialize                                                 *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Initialize the memory block allocator                              *
     ********************************************************************************/
    VOID MemblockInitialize(const boot::BootInfo &info) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockSetCurrentLimit                                            *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Set limit on highest physical address allowed to be given out      *
     ********************************************************************************/
    VOID MemblockSetCurrentLimit(QWORD limit) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockGetCurrentLimit                                            *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Get the current limit set by the function above                    *
     ********************************************************************************/
    NO_DISCARD QWORD MemblockGetCurrentLimit() noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockAllowResize                                                *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Allows tracking arrays to expand if they run out of slots          *
     ********************************************************************************/
    VOID MemblockAllowResize() noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockSetBottomUp                                                *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Flips the search direction for the allocator                       *
     *            If enabled, LOWEST-TO-HIGHEST, if disabled, HIGHEST-TO-LOWEST      *
     ********************************************************************************/
    VOID MemblockSetBottomUp(BOOL enable) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockBottomUp                                                   *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Checks if set to bottom-up allocator                               *
     ********************************************************************************/
    NO_DISCARD BOOL MemblockBottomUp() noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockEnforceMemoryLimit                                         *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Chops off any memory regions that exist above 'limit'              *
     ********************************************************************************/
    VOID MemblockEnforceMemoryLimit(QWORD limit) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockCapMemoryRange                                             *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Clips everything outside of the window away                        *
     ********************************************************************************/
    VOID MemblockCapMemoryRange(QWORD base, QWORD size) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockDiscard                                                    *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Untracks and releases the temporary arrays                         *
     ********************************************************************************/
    VOID MemblockDiscard() noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockAdd                                                        *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Insert a raw chunk of RAM into tracking pool                       *
     ********************************************************************************/
    NO_DISCARD BOOL MemblockAdd(QWORD base, QWORD size) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockRemove                                                     *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Removes a raw chunk of RAM from the tracking pool                  *
     ********************************************************************************/
    NO_DISCARD BOOL MemblockRemove(QWORD base, QWORD size) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockReserve                                                    *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Marks a chunk of added RAM as 'in-use'                             *
     ********************************************************************************/
    NO_DISCARD BOOL MemblockReserve(QWORD base, QWORD size) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockReserveKern                                                *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Same as MemblockReserve, but specialized for the kernel regions    *
     ********************************************************************************/
    NO_DISCARD BOOL MemblockReserveKern(QWORD base, QWORD size) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockPhysFree                                                   *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Un-reserves a chunk of RAM and adds to 'free' pool                 *
     ********************************************************************************/
    NO_DISCARD BOOL MemblockPhysFree(QWORD base, QWORD size) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockTrimMemory                                                 *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Clips off the tiny unaligned edges                                 *
     ********************************************************************************/
    VOID MemblockTrimMemory(QWORD align);

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockAlloc                                                      *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Finds a free chunk of memory matching size and alignment and       *
     *                                              reserves it                      *
     ********************************************************************************/
    NO_DISCARD QWORD MemblockAlloc(QWORD size, QWORD align) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockAllocRaw                                                   *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Same as MemblockAlloc but doesn't zero the memory                  *
     ********************************************************************************/
    NO_DISCARD QWORD MemblockAllocRaw(QWORD size, QWORD align) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockAllocFrom                                                  *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Alloc a chunk of memory but block must start at or above min_addr  *
     ********************************************************************************/
    NO_DISCARD QWORD MemblockAllocFrom(QWORD size, QWORD align, QWORD min_addr) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockAllocLow                                                   *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Exact opposite of MemblockAllocFrom                                *
     ********************************************************************************/
    NO_DISCARD QWORD MemblockAllocLow(QWORD size, QWORD align) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockAllocOrPanic                                               *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Standard alloc but panics if it fails (used for core systems)      *
     ********************************************************************************/
    NO_DISCARD QWORD MemblockAllocOrPanic(QWORD size, QWORD align) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockFree                                                       *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Unreserves the exact region in the tracking list                   *
     ********************************************************************************/
    VOID MemblockFree(PVOID ptr, SIZE_T size) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockIsMemory                                                   *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Check if the address is inside a valid RAM block                   *
     ********************************************************************************/
    NO_DISCARD BOOL MemblockIsMemory(QWORD addr) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockIsReserved                                                 *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Check if a address sits inside a block that's currently not free   *
     ********************************************************************************/
    NO_DISCARD BOOL MemblockIsReserved(QWORD addr) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockIsRegionMemory                                             *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Check if the memory region rests within valid RAM sectors          *
     ********************************************************************************/
    NO_DISCARD BOOL MemblockIsRegionMemory(QWORD base, QWORD size) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockIsRegionReserved                                           *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Checks if a piece of memory crosses over area marked as reserved   *
     ********************************************************************************/
    NO_DISCARD BOOL MemblockIsRegionReserved(QWORD base, QWORD size) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockIsMapAnywhere                                              *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Check if a region is free of special usage constraints like NOMAP  *
     ********************************************************************************/
    NO_DISCARD BOOL MemblockIsMapAnywhere(QWORD base, QWORD size) noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockPhysMemSize                                                *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Gets the total amount of RAM discovered on the system              *
     ********************************************************************************/
    NO_DISCARD QWORD MemblockPhysMemSize() noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockReservedSize                                               *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Calculate how many bytes are currently tied up in boot-stage       *
     ********************************************************************************/
    NO_DISCARD QWORD MemblockReservedSize() noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockMemSizeLimit                                               *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Returns current allocation limit cap (only if set)                 *
     ********************************************************************************/
    NO_DISCARD QWORD MemblockMemSizeLimit() noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockStartOfDRam                                                *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Locate the lowest address of RAM                                   *
     ********************************************************************************/
    NO_DISCARD QWORD MemblockStartOfDRam() noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockEndOfDRam                                                  *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Locate the highest address of RAM                                  *
     ********************************************************************************/
    NO_DISCARD QWORD MemblockEndOfDRam() noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockFreeAll                                                    *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Registers free blocks into our physical page manager               *
     ********************************************************************************/
    VOID MemblockFreeAll() noexcept;

    /* *******************************************************************************
     *  AUTHOR  : Trollycat                                                          *
     *  FUNC    : MemblockFreeLate                                                   *
     *  DATE    : 2026                                                               *
     *  PURPOSE : Delivers patch of memory to page allocator                         *
     ********************************************************************************/
    VOID MemblockFreeLate(QWORD base, QWORD size) noexcept;
} // namespace cbk::mem