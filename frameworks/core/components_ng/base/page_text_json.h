/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_PAGE_TEXT_JSON_H
#define FOUNDATION_ACE_PAGE_TEXT_JSON_H

#include <algorithm>
#include <charconv>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <string_view>

#include "securec.h"

namespace OHOS::Ace::NG {
// Checked JSON buffer. Escape the translation getter's UTF-8 bytes without
// interpreting or changing its text content; failed growth never publishes a snapshot.
class PageTextJson final {
public:
    ~PageTextJson() { std::free(data_); }
    PageTextJson() = default;
    PageTextJson(const PageTextJson&) = delete;
    PageTextJson& operator=(const PageTextJson&) = delete;

    const char* GetError() const { return error_; }

    bool Fail(const char* error)
    {
        error_ = error;
        return false;
    }

    bool Append(std::string_view value)
    {
        constexpr size_t limit = std::min<size_t>(UINT32_MAX, SIZE_MAX - 1);
        if (value.size() > limit - size_) {
            return Fail("Page text JSON exceeds the supported byte length.");
        }
        const size_t required = size_ + value.size() + 1;
        if (required > capacity_) {
            size_t capacity = std::max(required, capacity_ + std::min(capacity_, (limit + 1) - capacity_));
            auto* data = static_cast<char*>(std::realloc(data_, capacity));
            if (!data) {
                return Fail("Page text JSON allocation failed.");
            }
            data_ = data;
            capacity_ = capacity;
        }
        if (!value.empty() && memcpy_s(data_ + size_, capacity_ - size_, value.data(), value.size()) != EOK) {
            return Fail("Page text JSON copy failed.");
        }
        size_ += value.size();
        data_[size_] = '\0';
        return true;
    }

    template<typename T>
    bool Number(T value)
    {
        char buffer[64];
        auto result = std::to_chars(buffer, buffer + sizeof(buffer), value);
        if (result.ec != std::errc()) {
            return Fail("Page text number serialization failed.");
        }
        return Append({ buffer, static_cast<size_t>(result.ptr - buffer) });
    }

    bool String(std::string_view value)
    {
        if (!Append("\"")) {
            return false;
        }
        constexpr char hex[] = "0123456789abcdef";
        for (unsigned char ch : value) {
            if (ch < 0x20) {
                char escape[] = { '\\', 'u', '0', '0', hex[ch >> 4], hex[ch & 15] };
                if (!Append({ escape, sizeof(escape) })) {
                    return false;
                }
            } else {
                char byte = static_cast<char>(ch);
                if (((ch == '"' || ch == '\\') && !Append("\\")) || !Append({ &byte, 1 })) {
                    return false;
                }
            }
        }
        return Append("\"");
    }

    char* Release(uint32_t& size)
    {
        size = static_cast<uint32_t>(size_);
        auto* data = data_;
        data_ = nullptr;
        size_ = capacity_ = 0;
        return data;
    }

private:
    const char* error_ = "Page text serialization failed.";
    char* data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
};
} // namespace OHOS::Ace::NG
#endif
