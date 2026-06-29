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
 *  MODULE  : Central processing unit flags                                      *
 *  DATE    : 2026                                                               *
 *  PURPOSE : Stores hardware bitmask flags for the CPU                          *
 ********************************************************************************/
#pragma once

#include <types.h>

namespace cbk::cpu
{
    constexpr QWORD CR0_PE = 0x00000001;
    constexpr QWORD CR0_MP = 0x00000002;
    constexpr QWORD CR0_EM = 0x00000004;
    constexpr QWORD CR0_TS = 0x00000008;
    constexpr QWORD CR0_ET = 0x00000010;
    constexpr QWORD CR0_NE = 0x00000020;
    constexpr QWORD CR0_WP = 0x00010000;
    constexpr QWORD CR0_AM = 0x00040000;
    constexpr QWORD CR0_NW = 0x20000000;
    constexpr QWORD CR0_CD = 0x40000000;
    constexpr QWORD CR0_PG = 0x80000000;

    constexpr QWORD CR4_PCE = 0x00000100;
    constexpr QWORD CR4_MCE = 0x00000040;
    constexpr QWORD CR4_PSE = 0x00000010;
    constexpr QWORD CR4_DE  = 0x00000008;
    constexpr QWORD CR4_TSD = 0x00000004;
    constexpr QWORD CR4_PVI = 0x00000002;
    constexpr QWORD CR4_VME = 0x00000001;
    constexpr QWORD CR4_PGE = 0x80;

    constexpr QWORD FL_CF        = 0x00000001;
    constexpr QWORD FL_PF        = 0x00000004;
    constexpr QWORD FL_AF        = 0x00000010;
    constexpr QWORD FL_ZF        = 0x00000040;
    constexpr QWORD FL_SF        = 0x00000080;
    constexpr QWORD FL_TF        = 0x00000100;
    constexpr QWORD FL_IF        = 0x00000200;
    constexpr QWORD FL_DF        = 0x00000400;
    constexpr QWORD FL_OF        = 0x00000800;
    constexpr QWORD FL_IOPL_MASK = 0x00003000;
    constexpr QWORD FL_IOPL_0    = 0x00000000;
    constexpr QWORD FL_IOPL_1    = 0x00001000;
    constexpr QWORD FL_IOPL_2    = 0x00002000;
    constexpr QWORD FL_IOPL_3    = 0x00003000;
    constexpr QWORD FL_NT        = 0x00004000;
    constexpr QWORD FL_RF        = 0x00010000;
    constexpr QWORD FL_VM        = 0x00020000;
    constexpr QWORD FL_AC        = 0x00040000;
    constexpr QWORD FL_VIF       = 0x00080000;
    constexpr QWORD FL_VIP       = 0x00100000;
    constexpr QWORD FL_ID        = 0x00200000;

    constexpr QWORD FEC_PR = 0x1;
    constexpr QWORD FEC_WR = 0x2;
    constexpr QWORD FEC_U  = 0x4;

    constexpr QWORD EFER_NXE = 11;
} // namespace cbk::cpu