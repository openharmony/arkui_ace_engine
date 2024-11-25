/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_UTF_HELPER_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_UTF_HELPER_H

#include <cstdint>
#include <memory>
#include <vector>
#include <string>

#include "base/utils/macros.h"

namespace OHOS::Ace::UtfUtils {
ACE_EXPORT extern const std::string DEFAULT_STR;
ACE_EXPORT extern const std::u16string DEFAULT_U16STR;
ACE_EXPORT extern const std::u32string DEFAULT_U32STR;

uint32_t DecodeUTF16(uint16_t const *utf16, size_t len, size_t *index);

size_t EncodeUTF8(uint32_t codepoint, uint8_t* utf8, size_t len, size_t index);

size_t Utf16ToUtf8Size(const uint16_t *utf16, uint32_t length);

size_t ConvertRegionUtf16ToUtf8(const uint16_t *utf16In, uint8_t *utf8Out, size_t utf16Len,
    size_t utf8Len, size_t start);

size_t DebuggerConvertRegionUtf16ToUtf8(const uint16_t *utf16In, uint8_t *utf8Out, size_t utf16Len, size_t utf8Len,
    size_t start);

uint32_t HandleAndDecodeInvalidUTF16(uint16_t const *utf16, size_t len, size_t *index);

size_t Utf8ToUtf16Size(const uint8_t *utf8, size_t utf8Len);

size_t ConvertRegionUtf8ToUtf16(const uint8_t *utf8In, uint16_t *utf16Out, size_t utf8Len, size_t utf16Len);

std::u16string ACE_FORCE_EXPORT Str8ToStr16(const std::string& str);

std::u16string ACE_FORCE_EXPORT Str8DebugToStr16(const std::string& str);

std::string ACE_FORCE_EXPORT Str16ToStr8(const std::u16string& str);

std::string ACE_FORCE_EXPORT Str16DebugToStr8(const std::u16string& str);

void HandleInvalidUTF16(uint16_t* utf16In, size_t utf16Len, size_t start);

}  // namespace OHOS::Ace::UtfUtils

#endif  // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_UTF_HELPER_H