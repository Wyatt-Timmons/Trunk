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
 *  MODULE  : Standard library utility                                           *
 *  DATE    : 2026                                                               *
 *  PURPOSE : Replacement for <utility> header (std)                             *
 ********************************************************************************/
#pragma once

#include <macros.h>
#include <types.h>

namespace tklib
{
    template <typename T> struct remove_reference
    {
        using type = T;
    };
    template <typename T> struct remove_reference<T &>
    {
        using type = T;
    };
    template <typename T> struct remove_reference<T &&>
    {
        using type = T;
    };

    /* ******************************************************************************
     *  AUTHOR  : Trollycat                                                         *
     *  FUNC    : forward                                                           *
     *  DATE    : 2026                                                              *
     *  PURPOSE : Perfect forward t as T.                                           *
     * *****************************************************************************/
    template <typename T>
    NO_DISCARD CONSTEXPR T &&forward(typename remove_reference<T>::type &t) noexcept
    {
        return static_cast<T &&>(t);
    }

    template <typename T>
    NO_DISCARD CONSTEXPR T &&forward(typename remove_reference<T>::type &&t) noexcept
    {
        return static_cast<T &&>(t);
    }

    /* ******************************************************************************
     *  AUTHOR  : Trollycat                                                         *
     *  FUNC    : move                                                              *
     *  DATE    : 2026                                                              *
     *  PURPOSE : Cast t to rvalue reference.                                       *
     * *****************************************************************************/
    template <typename T>
    NO_DISCARD CONSTEXPR typename remove_reference<T>::type &&move(T &&t) noexcept
    {
        return static_cast<typename remove_reference<T>::type &&>(t);
    }

    /* ******************************************************************************
     *  AUTHOR  : Trollycat                                                         *
     *  FUNC    : exchange                                                          *
     *  DATE    : 2026                                                              *
     *  PURPOSE : Replace obj with new_val, return old value.                       *
     * *****************************************************************************/
    template <typename T, typename U = T> CONSTEXPR T exchange(T &obj, U &&new_val) noexcept
    {
        T old = move(obj);
        obj   = forward<U>(new_val);
        return old;
    }

    /* ******************************************************************************
     *  AUTHOR  : Trollycat                                                         *
     *  FUNC    : addressof                                                         *
     *  DATE    : 2026                                                              *
     *  PURPOSE : Take address of ref bypassing overloaded operator&.               *
     * *****************************************************************************/
    template <typename T> NO_DISCARD CONSTEXPR T *addressof(T &ref) noexcept
    {
        return __builtin_addressof(ref);
    }

    /* ******************************************************************************
     *  AUTHOR  : Trollycat                                                         *
     *  FUNC    : declval                                                           *
     *  DATE    : 2026                                                              *
     *  PURPOSE : Produce T&& in unevaluated contexts without constructing T.       *
     * *****************************************************************************/
    template <typename T> typename remove_reference<T>::type &&declval() noexcept;

    template <typename A, typename B> struct is_same
    {
        static CONSTEXPR BOOL value = FALSE;
    };
    template <typename A> struct is_same<A, A>
    {
        static CONSTEXPR BOOL value = TRUE;
    };

    template <typename A, typename B> INLINE_CONST BOOL is_same_v = is_same<A, B>::value;

    template <typename T> struct is_integral
    {
        static CONSTEXPR BOOL value = FALSE;
    };
    template <> struct is_integral<BYTE>
    {
        static CONSTEXPR BOOL value = TRUE;
    };
    template <> struct is_integral<WORD>
    {
        static CONSTEXPR BOOL value = TRUE;
    };
    template <> struct is_integral<DWORD>
    {
        static CONSTEXPR BOOL value = TRUE;
    };
    template <> struct is_integral<QWORD>
    {
        static CONSTEXPR BOOL value = TRUE;
    };
    template <> struct is_integral<CHAR>
    {
        static CONSTEXPR BOOL value = TRUE;
    };
    template <> struct is_integral<SHORT>
    {
        static CONSTEXPR BOOL value = TRUE;
    };
    template <> struct is_integral<LONG>
    {
        static CONSTEXPR BOOL value = TRUE;
    };
    template <> struct is_integral<LONGLONG>
    {
        static CONSTEXPR BOOL value = TRUE;
    };
    template <> struct is_integral<BOOL>
    {
        static CONSTEXPR BOOL value = TRUE;
    };

    template <typename T> INLINE_CONST BOOL is_integral_v = is_integral<T>::value;

    template <typename T> struct is_pointer
    {
        static CONSTEXPR BOOL value = FALSE;
    };
    template <typename T> struct is_pointer<T *>
    {
        static CONSTEXPR BOOL value = TRUE;
    };
    template <typename T> struct is_pointer<T * CONST>
    {
        static CONSTEXPR BOOL value = TRUE;
    };

    template <typename T> INLINE_CONST BOOL is_pointer_v = is_pointer<T>::value;

    template <typename T> struct is_const
    {
        static CONSTEXPR BOOL value = FALSE;
    };
    template <typename T> struct is_const<CONST T>
    {
        static CONSTEXPR BOOL value = TRUE;
    };

    template <typename T> INLINE_CONST BOOL is_const_v = is_const<T>::value;

    template <BOOL Cond, typename A, typename B> struct conditional
    {
        using type = A;
    };
    template <typename A, typename B> struct conditional<FALSE, A, B>
    {
        using type = B;
    };

    template <BOOL Cond, typename A, typename B>
    using conditional_t = typename conditional<Cond, A, B>::type;

    template <BOOL Cond, typename T = VOID> struct enable_if
    {
    };
    template <typename T> struct enable_if<TRUE, T>
    {
        using type = T;
    };

    template <BOOL Cond, typename T = VOID> using enable_if_t = typename enable_if<Cond, T>::type;
} // namespace tklib