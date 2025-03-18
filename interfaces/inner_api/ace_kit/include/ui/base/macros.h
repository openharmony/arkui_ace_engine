/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_MACROS_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_MACROS_H

#define ACE_WEAK_SYM     __attribute__((weak))

#ifndef ACE_FORCE_EXPORT
#ifndef WINDOWS_PLATFORM
#define ACE_FORCE_EXPORT __attribute__((visibility("default")))
#else
#define ACE_FORCE_EXPORT __declspec(dllexport)
#endif
#endif

#ifndef ACE_EXPORT
#if !defined(HIDDEN_SYMBOL) && !defined(WINDOWS_PLATFORM)
#define ACE_EXPORT ACE_FORCE_EXPORT
#else
#define ACE_EXPORT
#endif
#endif

#ifndef CJ_FORCE_EXPORT
#ifndef WINDOWS_PLATFORM
#define CJ_FORCE_EXPORT ACE_FORCE_EXPORT
#else
#define CJ_FORCE_EXPORT ACE_EXPORT
#endif
#endif

#ifdef ACE_DEBUG

#ifdef NDEBUG
#define CANCEL_NDEBUG
#undef NDEBUG
#endif // NDEBUG

#include <cassert>

#ifdef CANCEL_NDEBUG
#define NDEBUG
#undef CANCEL_NDEBUG
#endif // CANCEL_NDEBUG

#define ACE_DCHECK(expr) assert(expr)
#else
#define ACE_DCHECK(expr) ((void)0)

#endif // ACE_DEBUG

#define ACE_LIKELY(x) __builtin_expect(!!(x), 1)
#define ACE_UNLIKELY(x) __builtin_expect(!!(x), 0)

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_MACROS_H
